#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <QByteArray>
#include <QString>
#include <QCryptographicHash>     // Qt 哈希功能
#include <QMessageAuthenticationCode>


struct AES_ctx;

class CryptoUtils {
public:
    //哈希与密钥派生
    /**
     * @brief 生成指定长度的随机盐值
     * @param length 盐值的字节长度，默认为16字节
     * @return 生成的随机盐值
     */
    static QByteArray generateSalt(int length = 16);

    /**
     * @brief 为存储目的哈希密码
     * 使用 SHA-512 算法
     * @param password 要哈希的明文密码
     * @param salt 用于哈希的盐值
     * @return 哈希后的密码摘要
     */
    static QByteArray hashPasswordForStorage(const QString& password, const QByteArray& salt);

    /**
     * @brief 实现 PBKDF2-HMAC-SHA256 密钥派生函数
     * @param password 从中派生密钥的密码
     * @param salt 盐值
     * @param iterations 迭代次数
     * @param dkLen 期望派生密钥的字节长度
     * @return 派生出的密钥；如果参数无效则返回空 QByteArray
     */
    static QByteArray pbkdf2HmacSha256(const QByteArray& password, const QByteArray& salt, int iterations, int dkLen);

    // AES 加密/解密

    static const int AES_KEY_SIZE = 32;   // AES-256 密钥长度 (字节)
    static const int AES_BLOCK_SIZE = 16; // AES 数据块长度 (字节)

    /**
     * @brief 使用 AES-256 CBC 模式加密数据
     * @param plaintext 要加密的明文数据
     * @param key 用于加密的32字节密钥
     * @return IV + 密文；如果密钥大小无效或加密失败则返回空 QByteArray
     */
    static QByteArray aesEncrypt(const QByteArray& plaintext, const QByteArray& key);

    /**
     * @brief 使用 AES-256 CBC 模式解密数据
     * 假定 IV 已前置到密文中
     * @param ivAndCiphertext 包含 IV 和密文的数据
     * @param key 用于解密的32字节密钥
     * @return 解密后的明文数据；如果密钥大小无效、数据太短或解密/去填充失败则返回空 QByteArray
     */
    static QByteArray aesDecrypt(const QByteArray& ivAndCiphertext, const QByteArray& key);

    /**
     * @brief 生成一个随机的 AES 初始化向量 (IV)
     * @return 16字节的随机IV
     */
    static QByteArray generateIV();

private:
    // PKCS#7 填充方案
    /**
     * @brief 对数据进行 PKCS#7 填充，使其长度成为块大小的整数倍
     * @param data 要填充的数据
     * @param blockSize AES的块大小
     * @return 填充后的数据。
     */
    static QByteArray pkcs7Pad(const QByteArray& data, int blockSize);

    /**
     * @brief 从已填充的数据中移除 PKCS#7 填充
     * @param paddedData 已填充的数据。
     * @return 去填充后的原始数据；如果填充无效则返回空 QByteArray
     */
    static QByteArray pkcs7Unpad(const QByteArray& paddedData);
};

#endif // CRYPTOUTILS_H
