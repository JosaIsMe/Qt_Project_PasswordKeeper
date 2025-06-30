#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QString>
#include <QByteArray>
#include <QJsonObject> // 用于存储凭据的JSON对象

// 前向声明 PasswordManager 以避免循环包含，因为 LoginManager在更改密码时可能需要直接调用 PasswordManager 的方法。
class PasswordManager;

class LoginManager {
private:
    QString m_username;             // 当前用户名
    QByteArray m_storedSalt;        // 存储的盐值，用于哈希主密码
    QByteArray m_storedPasswordHash; // 存储的主密码哈希值 (哈希(主密码 + 盐))，用于验证

    QByteArray m_derivedMasterKey;  // 从主密码派生的实际加密密钥 (通过PBKDF2)

    QString m_credentialsFilePath;  // 用户凭据文件的完整路径

    /**
     * @brief 从文件加载用户凭据（盐和哈希）。
     * @return 如果成功加载凭据，则返回 true。
     */
    bool loadCredentials();

    /**
     * @brief 将当前用户凭据（盐和哈希）保存到文件。
     * @return 如果成功保存凭据，则返回 true。
     */
    bool saveCredentials() const;

    // PBKDF2 的迭代次数。越高越安全，但派生密钥所需时间越长
    // 建议根据目标平台的性能和当前安全标准进行调整
    static const int PBKDF2_ITERATIONS = 150000; // 增加了迭代次数以提高安全性

public:
    /**
     * @brief 构造 LoginManager 实例。
     * @param username 用户名，默认为 "defaultUser"。
     * @param appDataPath 应用程序数据存储路径的根目录，默认为当前目录 "."。
     * 凭据和密码库文件将存储在此路径下的特定子目录中。
     */
    LoginManager(const QString& username = "defaultUser", const QString& appDataPath = ".");
    ~LoginManager();

    /**
     * @brief 检查指定用户名的用户配置文件是否存在。
     * @return 如果用户存在（即已加载凭据），则返回 true。
     */
    bool doesUserExist() const;

    /**
     * @brief 创建一个新用户账户。
     * 会生成新的盐，哈希密码，派生主密钥，并保存凭据。
     * @param password 新用户的主密码。
     * @return 如果用户成功创建并保存凭据，则返回 true。
     */
    bool createUser(const QString& password);

    /**
     * @brief 验证用户密码并执行登录。
     * 如果密码正确，会派生主加密密钥供会话使用。
     * @param password 用户输入的主密码。
     * @return 如果登录成功，则返回 true。
     */
    bool login(const QString& password);

    /**
     * @brief 更改用户的主密码。
     * 这是一个复杂操作，涉及重新加密由 PasswordManager 管理的所有数据。
     * @param oldPassword 当前主密码，用于验证。
     * @param newPassword 要设置的新主密码。
     * @param passwordManager 对 PasswordManager 实例的引用，其数据需要重新加密。
     * @return 如果密码成功更改，凭据已更新，并且所有关联数据已重新加密，则返回 true。否则返回 false。
     * @warning 这是一个关键操作。失败可能导致数据无法访问。
     */
    bool changeMasterPassword(const QString& oldPassword, const QString& newPassword, PasswordManager& passwordManager);

    /**
     * @brief 获取派生出的主加密密钥。
     * 只有在成功登录或创建用户后，此密钥才有效。
     * @return QByteArray 包含主加密密钥。如果未登录或派生失败，则为空。
     */
    const QByteArray& getMasterKey() const;

    /**
     * @brief 检查用户当前是否已登录（即主密钥已成功派生）。
     * @return 如果用户已登录，则返回 true。
     */
    bool isLoggedIn() const;

    /**
     * @brief 获取当前用户名。
     * @return QString 用户名。
     */
    QString getUsername() const;

    /**
     * @brief 获取密码库文件的建议存储路径。
     * 此路径通常与用户凭据文件位于同一目录下。
     * @return QString 密码库文件的完整路径。
     */
    QString getVaultFilePath() const;
};

#endif // LOGINMANAGER_H
