#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <QMap>
#include <QString>
#include <QJsonObject>
#include <QVariantMap> // 用于站点条目

#include "encryptionhandler.h" // 加密处理器

// 站点密码条目结构体
struct SiteEntry {
    QString siteName; // 站点名称，也用作QMap中的键
    QString username; // 该站点的用户名
    QByteArray encryptedPassword; // AES加密后的实际站点密码 (IV已前置)

    // 用于存储关联的文件加密密钥（如果有）
    QString fileKeyIdentifier; // 文件密钥的标识符 (例如，原始文件名或UUID)
    QByteArray encryptedFileKey; // AES加密后的文件特定密钥 (IV已前置)

    /**
     * @brief 将SiteEntry对象转换为QJsonObject以便存储。
     * @return 包含此条目数据的QJsonObject。
     */
    QJsonObject toJson() const;

    /**
     * @brief 从QJsonObject创建SiteEntry对象。
     * @param obj 包含条目数据的QJsonObject。
     * @return 解析出的SiteEntry对象。
     */
    static SiteEntry fromJson(const QJsonObject& obj);
};


class PasswordManager {
private:
    QMap<QString, SiteEntry> m_entries;   // 存储所有站点密码条目的映射
    EncryptionHandler m_encryptionHandler; // 用于使用主密钥进行加密/解密
    QString m_vaultFilePath;               // 加密密码库文件的完整路径

    /**
     * @brief 从加密的密码库文件加载并解密所有条目。
     * @return 如果加载成功或文件不存在（视为空密码库），则返回 true。
     */
    bool loadVault();

    /**
     * @brief 将当前所有条目加密并保存到密码库文件。
     * @return 如果保存成功，则返回 true。
     */
    bool saveVault() const;

public:
    /**
     * @brief PasswordManager 构造函数。
     * @param masterKey 用于加密密码库的主密钥（从LoginManager获取）。
     * @param vaultFilePath 密码库文件的存储路径。
     */
    PasswordManager(const QByteArray& masterKey, const QString& vaultFilePath);
    ~PasswordManager(); // 析构函数

    /**
     * @brief 添加一个新的站点密码条目。
     * @param siteName 站点名称。
     * @param username 站点用户名。
     * @param password 站点明文密码。
     * @return 如果成功添加并保存，则返回 true。
     */
    bool addEntry(const QString& siteName, const QString& username, const QString& password);

    /**
     * @brief 更新一个已存在的站点密码条目。
     * @param siteName 要更新的站点名称。
     * @param newUsername 新的站点用户名。
     * @param newPassword 新的站点明文密码。
     * @return 如果成功更新并保存，则返回 true。
     */
    bool updateEntry(const QString& siteName, const QString& newUsername, const QString& newPassword);

    /**
     * @brief 删除一个站点密码条目。
     * @param siteName 要删除的站点名称。
     * @return 如果成功删除并保存，则返回 true。
     */
    bool removeEntry(const QString& siteName);

    /**
     * @brief 获取指定站点的解密后的密码。
     * @param siteName 站点名称。
     * @return QString 解密后的密码；如果条目不存在或解密失败，则返回空字符串。
     */
    QString getDecryptedPassword(const QString& siteName) const;

    /**
     * @brief 获取指定站点的详细信息（不包括密码）。
     * @param siteName 站点名称。
     * @return QVariantMap 包含站点名称和用户名的映射；如果条目不存在则为空。
     */
    QVariantMap getEntryDetails(const QString& siteName) const;

    /**
     * @brief 获取所有已存储站点的名称列表。
     * @return QList<QString> 包含所有站点名称的列表。
     */
    QList<QString> getAllSiteNames() const;

    // --- 文件密钥管理 ---
    /**
     * @brief 存储一个（已使用主密钥加密的）文件特定加密密钥。
     * 此密钥通常由 FileEncryptor 生成。
     * @param siteNameOrIdentifier 与此文件密钥关联的站点名称或唯一标识符。
     * @param fileKeyId 文件密钥本身的特定标识符（例如，原始文件名）。
     * @param plainFileKey 要存储的明文文件密钥（在内部会被加密）。
     * @return 如果成功存储并保存密码库，则返回 true。
     */
    bool storeEncryptedFileKey(const QString& siteNameOrIdentifier, const QString& fileKeyId, const QByteArray& plainFileKey);

    /**
     * @brief 获取指定标识符的解密后的文件特定加密密钥。
     * @param siteNameOrIdentifier 与文件密钥关联的站点名称或唯一标识符。
     * @param fileKeyId 文件密钥本身的特定标识符。
     * @return QByteArray 解密后的文件密钥；如果未找到或解密失败，则返回空。
     */
    QByteArray getDecryptedFileKey(const QString& siteNameOrIdentifier, const QString& fileKeyId) const;

    /**
     * @brief （在更改主密码时使用）使用新的主密钥重新加密所有管理的条目。
     * @param oldMasterKey 用于解密的旧主密钥。
     * @param newMasterKey 用于重新加密的新主密钥。
     * @return 如果所有数据成功重新加密并保存，则返回 true。
     */
    bool reEncryptAllData(const QByteArray& oldMasterKey, const QByteArray& newMasterKey);
};

#endif // PASSWORDMANAGER_H
