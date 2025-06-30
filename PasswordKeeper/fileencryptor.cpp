#include "fileencryptor.h"
#include "cryptoutils.h"    // 用于 AES 操作和密钥/IV生成
#include "passwordmanager.h" // 用于存储/检索文件密钥
#include <QFile>
#include <QFileInfo>        // 用于获取文件名等信息
#include <QDataStream>      // 如果需要更复杂的文件I/O（当前未使用，直接读写字节）
#include <QDebug>

FileEncryptor::FileEncryptor(PasswordManager& passwordManager)
    : m_passwordManager(passwordManager) {} // 初始化对 PasswordManager 的引用

bool FileEncryptor::encryptFile(const QString& inputFilePath, const QString& outputFilePath, const QString& fileIdentifierForStorage) {
    QFile inputFile(inputFilePath); // 打开源文件
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << "FileEncryptor-OpenFailed: 无法打开输入文件：" << inputFilePath << inputFile.errorString();
        return false;
    }
    QByteArray plaintext = inputFile.readAll(); // 读取所有文件内容
    inputFile.close();

    if (plaintext.isEmpty()) {
        qWarning() << "FileEncryptor-BlankFile: 输入文件为空，无需加密。" << inputFilePath;
        // 根据需求决定是否应创建空的输出文件或返回错误
        QFile outputFile(outputFilePath); // 如果空文件是期望行为，则创建它
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            outputFile.close();
            // 将空文件的“密钥”（如果需要）存储起来可能没有意义，
            // 但如果UI流程依赖于一个密钥条目，则可能需要特殊处理。
            // 为简单起见，这里我们认为加密一个空文件成功（输出也是空文件）。
            // 也可以选择存储一个标记密钥或不存储。
            // 如果要存储一个“空文件”的标记，可以生成一个随机密钥并存储它。
            // QByteArray emptyFileKey = CryptoUtils::generateSalt(CryptoUtils::AES_KEY_SIZE);
            // m_passwordManager.storeEncryptedFileKey(fileIdentifierForStorage, QFileInfo(inputFilePath).fileName(), emptyFileKey);
            return true;
        }
        return false; // 无法创建输出文件
    }

    // 1. 为此文件生成一个唯一的、随机的文件特定加密密钥
    //    CryptoUtils::generateSalt 可以用于生成随机字节作为密钥
    QByteArray fileKey = CryptoUtils::generateSalt(CryptoUtils::AES_KEY_SIZE);

    // 2. 使用此 fileKey 加密文件内容 (plaintext)
    //    CryptoUtils::aesEncrypt 会生成IV并将其前置到密文中
    QByteArray ivAndCiphertext = CryptoUtils::aesEncrypt(plaintext, fileKey);
    if (ivAndCiphertext.isEmpty() && !plaintext.isEmpty()) { // 检查加密是否失败
        qWarning() << "FileEncryptor-AES Failed: 文件内容 AES 加密失败。文件：" << inputFilePath;
        return false;
    }

    // 3. 将此文件密钥 (fileKey) 使用主密钥加密后，存储到 PasswordManager 中
    //    我们使用原始输入文件的文件名作为 PasswordManager 中 fileKeyId 的一部分，以便区分
    //    fileIdentifierForStorage 是用户提供的更高级别的标识符。
    //    5.31 00:00注记：原方法有问题，现去除了原有的filename标识符。
    if (!m_passwordManager.storeEncryptedFileKey(fileIdentifierForStorage, fileIdentifierForStorage, fileKey)) {
        qWarning() << "FileEncryptor-Save Failed: 无法将加密后的文件密钥存储到 PasswordManager。文件：" << inputFilePath;
        return false;
    }

    // 4. 将 IV + 密文写入输出文件
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) { // 以写入、截断模式打开
        qWarning() << "FileEncryptor-Write Failed: 无法打开输出文件进行写入：" << outputFilePath << outputFile.errorString();
        // 如果写入失败，可能需要回滚已存储的密钥（更复杂）
        return false;
    }
    qint64 bytesWritten = outputFile.write(ivAndCiphertext);
    outputFile.close();

    if (bytesWritten != ivAndCiphertext.size()) {
        qWarning() << "FileEncryptor: 未能将完整的加密数据写入输出文件。" << outputFilePath;
        // 可以考虑删除部分写入的文件
        return false;
    }

    qInfo() << "FileEncryptor: 文件 " << inputFilePath << " 已成功加密到 " << outputFilePath;
    return true;
}

bool FileEncryptor::decryptFile(const QString& encryptedFilePath, const QString& outputFilePath, const QString& fileIdentifierForStorage) {
    QFile encryptedFile(encryptedFilePath); // 打开加密文件
    if (!encryptedFile.open(QIODevice::ReadOnly)) {
        qWarning() << "FileEncryptor: 无法打开加密文件：" << encryptedFilePath << encryptedFile.errorString();
        return false;
    }
    QByteArray ivAndCiphertext = encryptedFile.readAll(); // 读取所有加密内容
    encryptedFile.close();

    if (ivAndCiphertext.isEmpty()) {
        qWarning() << "FileEncryptor: 加密文件为空，无需解密。" << encryptedFilePath;
        // 创建空的输出文件（如果这是期望的行为）
        QFile outputFile(outputFilePath);
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            outputFile.close();
            return true;
        }
        return false;
    }

    // 确保数据至少包含一个IV
    if (ivAndCiphertext.size() < CryptoUtils::AES_BLOCK_SIZE) {
        qWarning() << "FileEncryptor: 加密文件太小，无法包含IV。" << encryptedFilePath;
        return false;
    }

    // 1. 从 PasswordManager 检索并解密文件特定的加密密钥
    //    使用原始（加密前）的文件名（或现在是加密文件名，取决于UI如何提供）作为 fileKeyId。
    //    这里假设 QFileInfo(encryptedFilePath).fileName() 是存储时使用的 fileKeyId。
    //    5.31 0:05注记 去除了原来的文件名称标识符
    QByteArray fileKey = m_passwordManager.getDecryptedFileKey(fileIdentifierForStorage, fileIdentifierForStorage);
    if (fileKey.isEmpty()) {
        qWarning() << "FileEncryptor: 无法从 PasswordManager 检索或解密文件密钥。标识符：" << fileIdentifierForStorage << ", 文件名：" << QFileInfo(encryptedFilePath).fileName();
        return false;
    }

    // 2. 使用获取到的 fileKey 解密文件内容 (ivAndCiphertext)
    //    CryptoUtils::aesDecrypt 期望IV已前置到密文中
    QByteArray plaintext = CryptoUtils::aesDecrypt(ivAndCiphertext, fileKey);
    // 如果解密失败（例如，密钥错误或数据损坏），plaintext 将为 null
    if (plaintext.isNull() && !ivAndCiphertext.isEmpty()) { // 检查解密是否真的失败
        qWarning() << "FileEncryptor: 文件内容 AES 解密失败。文件：" << encryptedFilePath << "。可能是密钥错误或数据损坏。";
        return false;
    }

    // 3. 将解密后的明文写入输出文件
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "FileEncryptor: 无法打开输出文件进行写入：" << outputFilePath << outputFile.errorString();
        return false;
    }
    qint64 bytesWritten = outputFile.write(plaintext);
    outputFile.close();

    if (bytesWritten != plaintext.size()) {
        qWarning() << "FileEncryptor: 未能将完整的解密数据写入输出文件。" << outputFilePath;
        return false;
    }

    qInfo() << "FileEncryptor: 文件 " << encryptedFilePath << " 已成功解密到 " << outputFilePath;
    return true;
}
