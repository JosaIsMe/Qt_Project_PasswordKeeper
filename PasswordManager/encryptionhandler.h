#ifndef ENCRYPTIONHANDLER_H
#define ENCRYPTIONHANDLER_H

#include <QByteArray>
#include "cryptoutils.h" // 需要访问 AES_KEY_SIZE 等常量

class EncryptionHandler {
private:
    QByteArray m_masterKey; // 此处理器实例使用的加密密钥

public:
    /**
     * @brief 默认构造函数。密钥必须稍后通过 setMasterKey 设置
     */
    EncryptionHandler();

    /**
     * @brief 使用提供的主密钥构造加密处理器
     * @param masterKey 用于加密/解密的主密钥
     */
    EncryptionHandler(const QByteArray& masterKey);

    /**
     * @brief 设置此加密处理器使用的主密钥
     * @param masterKey 要设置的主密钥。必须符合 CryptoUtils::AES_KEY_SIZE
     * @return 如果密钥大小有效并成功设置，则返回 true；否则返回 false
     */
    bool setMasterKey(const QByteArray& masterKey);

    /**
     * @brief 检查主密钥是否已设置且有效
     * @return 如果主密钥已设置，则返回 true；否则返回 false
     */
    bool isKeySet() const;

    /**
     * @brief 使用已设置的主密钥加密数据
     * 内部会调用 CryptoUtils::aesEncrypt，它会生成IV并前置到密文中
     * @param plaintext 要加密的明文数据
     * @return IV + 密文；如果主密钥未设置或加密失败，则返回空 QByteArray
     */
    QByteArray encryptData(const QByteArray& plaintext) const;

    /**
     * @brief 使用已设置的主密钥解密数据（数据应为 IV + 密文格式）
     * 内部会调用 CryptoUtils::aesDecrypt
     * @param ivAndCiphertext 包含IV和密文的数据
     * @return 解密后的明文数据；如果主密钥未设置或解密失败，则返回空 QByteArray
     */
    QByteArray decryptData(const QByteArray& ivAndCiphertext) const;
};

#endif // ENCRYPTIONHANDLER_H
