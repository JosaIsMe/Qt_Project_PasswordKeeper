#include "cryptoutils.h"
#include <QRandomGenerator> // Qt 安全随机数生成器
#include <QDebug>           // 用于调试输出


extern "C" { // Tiny AES 是 C 库，所以使用 extern "C"
#include "aes.h" //
}

/**
 * @brief 生成指定长度的随机盐值
 * @param length 盐值的字节长度
 * @return QByteArray 包含随机字节的盐值
 */
QByteArray CryptoUtils::generateSalt(int length) {
    QByteArray salt(length, 0); // 初始化一个指定长度的 QByteArray，所有字节为 0

    quint8* dataPtr = reinterpret_cast<quint8*>(salt.data());
    int bytesFilled = 0;
    while (bytesFilled < length) {
        quint32 randomValue = QRandomGenerator::global()->generate(); // 生成一个 32 位随机数
        for (int i = 0; i < 4 && bytesFilled < length; ++i) {
            dataPtr[bytesFilled++] = static_cast<quint8>((randomValue >> (i * 8)) & 0xFF);
        }
    }

    return salt;
}

/**
 * @brief 为存储目的哈希密码（例如，主密码验证）
 * 使用 (密码 + 盐) 然后进行 SHA-512 哈希
 * @param password 要哈希的明文密码
 * @param salt 用于哈希的盐值
 * @return QByteArray 哈希后的密码摘要
 */
QByteArray CryptoUtils::hashPasswordForStorage(const QString& password, const QByteArray& salt) {
    QByteArray combined = password.toUtf8() + salt; // 将密码（UTF-8编码）和盐结合
    return QCryptographicHash::hash(combined, QCryptographicHash::Sha512); // 使用 SHA-512 哈希
}

/**
 * @brief 实现 PBKDF2-HMAC-SHA256 密钥派生函数
 * PBKDF2 (Password-Based Key Derivation Function 2) 用于从用户密码安全地派生出加密密钥
 * @param password 用户提供的密码
 * @param salt 盐值，增加破解难度
 * @param iterations 迭代次数，次数越多越安全但速度越慢
 * @param dkLen 期望派生出的密钥的字节长度
 * @return QByteArray 派生出的密钥；如果参数无效则返回空 QByteArray
 */
QByteArray CryptoUtils::pbkdf2HmacSha256(const QByteArray& password, const QByteArray& salt, int iterations, int dkLen) {
    if (iterations <= 0 || dkLen <= 0) {
        qWarning() << "PBKDF2: 无效的迭代次数或期望密钥长度。";
        return QByteArray();
    }

    QByteArray derivedKey;      // 用于存储最终派生的密钥
    derivedKey.reserve(dkLen);  // 预分配空间以提高效率
    // SHA256 哈希输出的长度（字节）
    int hLen = QCryptographicHash::hashLength(QCryptographicHash::Sha256); // 对于SHA256是32字节
    // 计算需要多少个哈希块来达到期望的密钥长度
    int numBlocks = (dkLen + hLen - 1) / hLen; // 向上取整

    // 为每个块进行计算
    for (int i = 1; i <= numBlocks; ++i) {
        QByteArray U; // 中间哈希值
        QByteArray blockSalt = salt; // 当前块使用的盐值
        // 将块索引 i (大端序4字节整数) 附加到盐的末尾
        blockSalt.append(static_cast<char>((i >> 24) & 0xFF));
        blockSalt.append(static_cast<char>((i >> 16) & 0xFF));
        blockSalt.append(static_cast<char>((i >> 8) & 0xFF));
        blockSalt.append(static_cast<char>(i & 0xFF));

        // U_1 = HMAC-SHA256(Password, Salt + INT_32_BE(i))
        U = QMessageAuthenticationCode::hash(blockSalt, password, QCryptographicHash::Sha256);
        QByteArray T_i = U; // 第 i 个哈希块 T_i 初始化为 U_1

        // 进行 (iterations - 1) 次迭代
        for (int j = 1; j < iterations; ++j) {
            // U_j = HMAC-SHA256(Password, U_{j-1})
            U = QMessageAuthenticationCode::hash(U, password, QCryptographicHash::Sha256);
            // T_i = T_i XOR U_j
            for (int k = 0; k < U.size(); ++k) {
                T_i[k] = T_i[k] ^ U[k];
            }
        }
        derivedKey.append(T_i); // 将计算得到的块附加到最终密钥
    }

    return derivedKey.left(dkLen); // 返回指定长度的密钥
}

/**
 * @brief 生成一个用于 AES CBC 模式的随机初始化向量 (IV)。
 * IV 的长度与 AES 块大小相同 (16字节)。
 * @return QByteArray 包含随机字节的 IV。
 */
QByteArray CryptoUtils::generateIV() {
    QByteArray iv(AES_BLOCK_SIZE, 0); // 初始化一个指定长度的 QByteArray，所有字节为 0

    quint8* dataPtr = reinterpret_cast<quint8*>(iv.data());
    int bytesFilled = 0;
    int length = AES_BLOCK_SIZE; // IV 的长度就是 AES_BLOCK_SIZE

    while (bytesFilled < length) {
        quint32 randomValue = QRandomGenerator::global()->generate(); // 生成一个 32 位随机数
        for (int i = 0; i < 4 && bytesFilled < length; ++i) {
            dataPtr[bytesFilled++] = static_cast<quint8>((randomValue >> (i * 8)) & 0xFF);
        }
    }
    return iv;
}

/**
 * @brief 对数据进行 PKCS#7 填充
 * 如果数据已经是块大小的整数倍，则添加一个完整的填充块
 * @param data 要填充的明文数据
 * @param blockSize AES的块大小（通常为16字节）
 * @return QByteArray 填充后的数据
 */
QByteArray CryptoUtils::pkcs7Pad(const QByteArray& data, int blockSize) {
    int paddingSize = blockSize - (data.size() % blockSize);
    // PKCS#7 标准规定，即使数据长度正好是块大小的倍数，也要添加一个完整的填充块。
    // 然而，很多实现（如果已经是整数倍就不再填充，或者只填充一个字节。
    // 为了与常见AES库行为一致并确保可解密性，如果已经是整数倍，我们添加一个完整的块。
    // 如果 paddingSize 是 0，表示 data.size() 是 blockSize 的倍数。
    // 根据严格的 PKCS#7，此时应该填充 blockSize 个值为 blockSize 的字节。
    // 很多实现中，如果 data.size() % blockSize == 0，也会添加一个值为blockSize的完整填充块。
    // 这里的实现是，如果余数是0，则paddingSize会是blockSize。
    // 例如，如果blockSize=16，data.size()=32，则32%16=0，paddingSize=16-0=16。
    // 如果data.size()=31，则31%16=15，paddingSize=16-15=1。
    // paddingSize 的值就是每个填充字节的值。
    QByteArray padding(paddingSize, static_cast<char>(paddingSize));
    return data + padding;
}

/**
 * @brief 从已填充的数据中移除 PKCS#7 填充
 * @param paddedData 包含 PKCS#7 填充的数据
 * @return QByteArray 去填充后的原始数据。如果填充无效，则返回空 QByteArray
 */
QByteArray CryptoUtils::pkcs7Unpad(const QByteArray& paddedData) {
    if (paddedData.isEmpty()) {
        qWarning() << "PKCS7 去填充：输入数据为空。";
        return QByteArray(); // 如果数据为空，则无法去填充
    }

    // 获取最后一个字节，指示填充长度
    int paddingSize = static_cast<unsigned char>(paddedData.at(paddedData.size() - 1));

    // 校验填充大小的有效性
    if (paddingSize == 0 || paddingSize > paddedData.size() || paddingSize > AES_BLOCK_SIZE) {
        qWarning() << "PKCS7 去填充：无效的填充大小：" << paddingSize;
        return QByteArray(); // 填充大小不合法
    }

    // 校验所有填充字节是否都等于 paddingSize
    for (int i = 0; i < paddingSize; ++i) {
        if (static_cast<unsigned char>(paddedData.at(paddedData.size() - 1 - i)) != paddingSize) {
            qWarning() << "PKCS7 去填充：无效的填充字节。";
            return QByteArray(); // 填充字节不一致
        }
    }

    // 移除填充并返回原始数据
    return paddedData.left(paddedData.size() - paddingSize);
}

/**
 * @brief 使用 AES-256 CBC 模式加密数据
 * IV（初始化向量）会被随机生成并前置到返回的密文中
 * @param plaintext 要加密的明文数据
 * @param key 用于加密的32字节（256位）密钥
 * @return QByteArray IV + 密文;如果密钥大小无效或加密失败，则返回空 QByteArray
 */
QByteArray CryptoUtils::aesEncrypt(const QByteArray& plaintext, const QByteArray& key) {
    if (key.size() != AES_KEY_SIZE) {
        qWarning() << "AES 加密：无效的密钥大小。期望" << AES_KEY_SIZE << "字节，得到" << key.size() << "字节。";
        return QByteArray(); // 密钥长度不正确
    }

    QByteArray iv = generateIV(); // 生成随机IV
    QByteArray paddedPlaintext = pkcs7Pad(plaintext, AES_BLOCK_SIZE); // 对明文进行PKCS#7填充

    // Tiny AES 的 CBC 模式函数会原地修改输入缓冲区。
    // 因此，我们需要一个可变的数据副本。
    QByteArray ciphertextBuffer = paddedPlaintext; // 创建一个可变副本用于加密

    AES_ctx ctx; // AES 上下文结构体
    // 初始化 AES 上下文，使用提供的密钥和IV
    AES_init_ctx_iv(&ctx, reinterpret_cast<const uint8_t*>(key.constData()), reinterpret_cast<const uint8_t*>(iv.constData()));
    // 执行 CBC 模式加密，结果直接写入 ciphertextBuffer
    AES_CBC_encrypt_buffer(&ctx, reinterpret_cast<uint8_t*>(ciphertextBuffer.data()), ciphertextBuffer.size());

    return iv + ciphertextBuffer; // 将 IV 前置到密文并返回
}

/**
 * @brief 使用 AES-256 CBC 模式解密数据
 * 假定 IV 已前置到输入的 ivAndCiphertext 中
 * @param ivAndCiphertext 包含 IV 和密文的数据
 * @param key 用于解密的32字节（256位）密钥
 * @return QByteArray 解密后的明文数据。如果密钥大小无效、数据太短无法包含IV、
 * 或解密/去填充失败，则返回空 QByteArray
 */
QByteArray CryptoUtils::aesDecrypt(const QByteArray& ivAndCiphertext, const QByteArray& key) {
    if (key.size() != AES_KEY_SIZE) {
        qWarning() << "AES 解密：无效的密钥大小。期望" << AES_KEY_SIZE << "字节，得到" << key.size() << "字节。";
        return QByteArray();
    }
    // 检查输入数据是否至少包含一个完整的IV
    if (ivAndCiphertext.size() < AES_BLOCK_SIZE) {
        qWarning() << "AES 解密：输入数据太短，无法包含IV。数据长度：" << ivAndCiphertext.size() << "，IV长度：" << AES_BLOCK_SIZE;
        return QByteArray();
    }

    // 从输入数据中分离 IV 和密文
    QByteArray iv = ivAndCiphertext.left(AES_BLOCK_SIZE);
    QByteArray ciphertext = ivAndCiphertext.mid(AES_BLOCK_SIZE); // IV之后的所有数据都是密文

    // 密文长度必须是块大小的整数倍
    if (ciphertext.size() % AES_BLOCK_SIZE != 0) {
        qWarning() << "AES 解密：密文大小不是块大小的整数倍。密文长度：" << ciphertext.size();
        // 对于CBC模式，如果密文不是块的整数倍，通常意味着数据已损坏或不完整。
        return QByteArray();
    }
    // 如果分离出IV后密文为空（例如，原始数据只有一个IV块长），这也是无效的
    if (ciphertext.isEmpty()) {
        qWarning() << "AES 解密：提取IV后密文为空。";
        return QByteArray();
    }

    // 同样，Tiny AES 的解密函数会原地修改缓冲区
    QByteArray decryptedBuffer = ciphertext; // 创建密文的可变副本

    AES_ctx ctx; // AES 上下文
    // 初始化 AES 上下文以进行解密
    AES_init_ctx_iv(&ctx, reinterpret_cast<const uint8_t*>(key.constData()), reinterpret_cast<const uint8_t*>(iv.constData()));
    // 执行 CBC 模式解密
    AES_CBC_decrypt_buffer(&ctx, reinterpret_cast<uint8_t*>(decryptedBuffer.data()), decryptedBuffer.size());

    // 对解密后的数据进行 PKCS#7 去填充
    QByteArray unpaddedData = pkcs7Unpad(decryptedBuffer);
    // 如果去填充失败（unpaddedData.isNull()），并且原始解密缓冲区非空，
    // 这通常意味着密钥错误或数据损坏，导致填充字节不正确。
    if (unpaddedData.isNull() && !decryptedBuffer.isEmpty()) {
        qWarning() << "AES 解密：PKCS7 去填充失败。可能是密钥错误或数据损坏。";
        // 对于安全性，如果填充不正确，通常意味着密钥错误或数据已损坏。
        // 不应返回部分解密的数据。返回空 QByteArray 表示失败。
        return QByteArray();
    }
    return unpaddedData; // 返回去填充后的明文数据
}
