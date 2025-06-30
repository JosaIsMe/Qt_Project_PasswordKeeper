#ifndef FILEENCRYPTOR_H
#define FILEENCRYPTOR_H

#include <QString>
#include <QByteArray>

class PasswordManager; // 前向声明，因为 FileEncryptor 需要与 PasswordManager 交互

class FileEncryptor {
private:
    PasswordManager& m_passwordManager; // 引用 PasswordManager 以存储/检索文件特定的加密密钥

public:
    /**
     * @brief FileEncryptor 构造函数。
     * @param passwordManager 对 PasswordManager 实例的引用，用于安全地存储和检索文件密钥。
     */
    FileEncryptor(PasswordManager& passwordManager);

    /**
     * @brief 加密一个文件。
     * 此方法会：
     * 1. 为文件生成一个新的、唯一的文件加密密钥。
     * 2. 使用此文件密钥加密文件内容。
     * 3. 将此文件密钥（使用主密钥加密后）通过 PasswordManager 存储，
     * 关联一个提供的 fileIdentifierForStorage。
     * @param inputFilePath 要加密的源文件路径。
     * @param outputFilePath 加密后文件的保存路径。
     * @param fileIdentifierForStorage 用于在 PasswordManager 中存储此文件加密密钥的标识符
     * （例如，可以与某个站点条目关联，或是一个独立的描述性名称）。
     * @return 如果文件成功加密并且其密钥已存储，则返回 true。
     */
    bool encryptFile(const QString& inputFilePath, const QString& outputFilePath, const QString& fileIdentifierForStorage);

    /**
     * @brief 解密一个文件。
     * 此方法会：
     * 1. 从 PasswordManager 检索与 fileIdentifierForStorage 关联的文件加密密钥（并用主密钥解密它）。
     * 2. 使用获取到的文件密钥解密文件内容。
     * @param encryptedFilePath 要解密的加密文件路径。
     * @param outputFilePath 解密后文件的保存路径。
     * @param fileIdentifierForStorage 用于从 PasswordManager 检索此文件加密密钥的标识符。
     * @return 如果文件成功解密，则返回 true。
     */
    bool decryptFile(const QString& encryptedFilePath, const QString& outputFilePath, const QString& fileIdentifierForStorage);
};

#endif // FILEENCRYPTOR_H
