#include "encryptionhandler.h"
#include <QDebug> // 用于调试输出
#include "cryptoutils.h"

EncryptionHandler::EncryptionHandler() {
    // 默认构造函数，密钥此时为空，需要后续设置
}

EncryptionHandler::EncryptionHandler(const QByteArray& masterKey) {
    setMasterKey(masterKey); // 尝试设置传入的主密钥
}

/**
 * @brief 设置此加密处理器实例要使用的主密钥
 * @param masterKey 要设置的32字节 AES-256 密钥
 * @return 如果密钥大小正确并且成功设置，则返回 true。否则，清除内部密钥并返回 false
 */
bool EncryptionHandler::setMasterKey(const QByteArray& masterKey) {
    if (masterKey.size() == CryptoUtils::AES_KEY_SIZE) {
        m_masterKey = masterKey; // 存储密钥
        return true;
    }
    qWarning() << "EncryptionHandler: 提供的密钥大小无效。期望" << CryptoUtils::AES_KEY_SIZE << "字节，得到" << masterKey.size() << "字节。";
    m_masterKey.clear(); // 清除无效密钥
    return false;
}

/**
 * @brief 检查主密钥是否已设置
 * @return 如果 m_masterKey 非空，则返回 true
 */
bool EncryptionHandler::isKeySet() const {
    return !m_masterKey.isEmpty();
}

/**
 * @brief 使用存储的主密钥加密提供的明文数据
 * @param plaintext 要加密的明文
 * @return QByteArray 包含IV和密文的数据。如果主密钥未设置或加密失败，则返回空 QByteArray
 */
QByteArray EncryptionHandler::encryptData(const QByteArray& plaintext) const {
    if (!isKeySet()) {
        qWarning() << "EncryptionHandler: 主密钥未设置，无法执行加密操作。";
        return QByteArray();
    }
    return CryptoUtils::aesEncrypt(plaintext, m_masterKey);
}

/**
 * @brief 使用存储的主密钥解密提供的（IV+密文）数据
 * @param ivAndCiphertext 包含IV和密文的数据
 * @return QByteArray 解密后的明文数据。如果主密钥未设置或解密失败，则返回空 QByteArray
 */
QByteArray EncryptionHandler::decryptData(const QByteArray& ivAndCiphertext) const {
    if (!isKeySet()) {
        qWarning() << "EncryptionHandler: 主密钥未设置，无法执行解密操作。";
        return QByteArray();
    }
    return CryptoUtils::aesDecrypt(ivAndCiphertext, m_masterKey);
}
