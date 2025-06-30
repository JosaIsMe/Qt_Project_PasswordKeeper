#include "loginmanager.h"
#include "cryptoutils.h"    // 用于加密操作
#include "passwordmanager.h" // 在 changeMasterPassword 中需要
#include <QFile>
#include <QJsonDocument>
#include <QDir>             // 用于目录操作
#include <QStandardPaths>   // 用于获取标准应用数据位置
#include <QFileInfo>        // 用于文件路径操作
#include <QDebug>

// 用户凭据文件的后缀名
const QString CREDENTIALS_FILE_SUFFIX = "_profile.json";

LoginManager::LoginManager(const QString& username, const QString& appDataPath)
    : m_username(username) {
    QString dataDirToUse = appDataPath;
    // 如果 appDataPath 是默认的 "."，尝试使用更标准的应用程序数据位置
    if (dataDirToUse == ".") {
        dataDirToUse = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        if (dataDirToUse.isEmpty()) { // 如果标准路径获取失败，则回退到当前目录
            dataDirToUse = ".";
            qWarning() << "LoginManager: 无法确定 AppLocalDataLocation，使用当前目录：" << QDir::currentPath();
        }
    }
    // 为此应用程序创建一个特定的子目录
    dataDirToUse += "/PasswordManagerApp"; // 使用更清晰的子目录名

    QDir dir(dataDirToUse);
    if (!dir.exists()) { // 如果目录不存在，则创建它
        if (!dir.mkpath(".")) { // "." 表示创建路径中的所有父目录
            qWarning() << "LoginManager: 无法创建应用程序数据目录：" << dataDirToUse;
            // 此处可以处理错误，例如禁用文件操作或使用备用路径
        }
    }
    // 使用 QDir::filePath 来构造平台无关的完整文件路径
    m_credentialsFilePath = dir.filePath(m_username + CREDENTIALS_FILE_SUFFIX);
    qInfo() << "LoginManager: 凭据文件路径设置为：" << m_credentialsFilePath;

    loadCredentials(); // 尝试加载现有凭据
}

LoginManager::~LoginManager() {
    // 可选：如果策略要求，可以在销毁时安全地清除内存中的敏感数据
    // m_derivedMasterKey.fill(0x00); // 用零填充密钥数据
}

/**
 * @brief 从磁盘加载用户的凭据（盐和密码哈希）。
 * @return 如果成功加载，返回 true；如果文件不存在、无法打开或内容无效，返回 false。
 */
bool LoginManager::loadCredentials() {
    QFile credFile(m_credentialsFilePath);
    if (!credFile.exists()) {
        // 如果文件不存在，这对于新用户是正常的。
        // qInfo() << "LoginManager: 凭据文件未找到 (新用户?)：" << m_credentialsFilePath;
        m_storedSalt.clear();
        m_storedPasswordHash.clear();
        return false; // 表示未加载凭据
    }
    if (!credFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "LoginManager: 凭据文件存在但无法打开：" << m_credentialsFilePath << credFile.errorString();
        return false;
    }

    QByteArray fileData = credFile.readAll(); // 读取文件所有内容
    credFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData); // 从JSON数据创建文档
    if (doc.isNull() || !doc.isObject()) { // 检查JSON是否有效且为对象
        qWarning() << "LoginManager: 凭据文件中的JSON无效：" << m_credentialsFilePath;
        return false;
    }

    QJsonObject jsonObj = doc.object(); // 获取JSON对象
    // 检查是否存在 'salt_b64' 和 'hash_b64' 键 (使用更清晰的键名)
    if (jsonObj.contains("salt_b64") && jsonObj.contains("hash_b64")) {
        m_storedSalt = QByteArray::fromBase64(jsonObj["salt_b64"].toString().toLatin1());
        m_storedPasswordHash = QByteArray::fromBase64(jsonObj["hash_b64"].toString().toLatin1());
        // 确保Base64解码后盐和哈希非空
        if (m_storedSalt.isEmpty() || m_storedPasswordHash.isEmpty()) {
            qWarning() << "LoginManager: 从凭据文件Base64解码后，盐或哈希为空。";
            m_storedSalt.clear(); // 视为无效凭据
            m_storedPasswordHash.clear();
            return false;
        }
        // qInfo() << "LoginManager: 用户" << m_username << "的凭据加载成功。";
        return true;
    }
    qWarning() << "LoginManager: 凭据文件中缺少 'salt_b64' 或 'hash_b64'。";
    return false;
}

/**
 * @brief 将当前用户的凭据（盐和密码哈希）保存到磁盘。
 * @return 如果成功保存，返回 true；否则返回 false。
 */
bool LoginManager::saveCredentials() const {
    // 不保存无效状态
    if (m_storedSalt.isEmpty() || m_storedPasswordHash.isEmpty()) {
        qWarning() << "LoginManager: 尝试保存空的盐或哈希。正在中止保存。";
        return false;
    }

    QFile credFile(m_credentialsFilePath);
    // 写入前确保目录存在
    QFileInfo credFileInfo(m_credentialsFilePath);
    QDir dirPath = credFileInfo.dir();
    if (!dirPath.exists()){
        if(!dirPath.mkpath(".")){ // 创建路径中的所有父目录
            qWarning() << "LoginManager: 无法为凭据文件创建目录：" << dirPath.path();
            return false;
        }
    }

    // 以写入、文本、截断模式打开文件
    if (!credFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "LoginManager: 无法打开凭据文件进行写入：" << m_credentialsFilePath << credFile.errorString();
        return false;
    }

    QJsonObject jsonObj; // 创建JSON对象
    // 将盐和哈希以Base64编码的字符串形式存储
    jsonObj["salt_b64"] = QString::fromLatin1(m_storedSalt.toBase64());
    jsonObj["hash_b64"] = QString::fromLatin1(m_storedPasswordHash.toBase64());

    QJsonDocument doc(jsonObj); // 从对象创建JSON文档
    // 将JSON文档写入文件（使用缩进格式以便阅读）
    qint64 bytesWritten = credFile.write(doc.toJson(QJsonDocument::Indented));
    credFile.close();

    if (bytesWritten < 1) { // 或与 doc.toJson().size() 比较
        qWarning() << "LoginManager: 未能将数据写入凭据文件，或写入了0字节。";
        return false;
    }
    qInfo() << "LoginManager: 用户" << m_username << "的凭据保存成功。";
    return true;
}

/**
 * @brief 检查用户配置文件是否存在（即凭据是否已加载且有效）。
 * @return 如果用户存在，返回 true。
 */
bool LoginManager::doesUserExist() const {
    // 如果盐和哈希已加载且非空，则用户存在。
    // 或者更直接地，凭据文件存在且能正确解析。
    // 为简单起见，依赖于 m_storedSalt 和 m_storedPasswordHash 是否已填充。
    return !m_storedSalt.isEmpty() && !m_storedPasswordHash.isEmpty();
}

/**
 * @brief 创建一个新用户账户。
 * @param password 新用户的主密码。
 * @return 如果用户成功创建，返回 true。
 */
bool LoginManager::createUser(const QString& password) {
    if (doesUserExist()) {
        qWarning() << "LoginManager: 无法创建用户，用户" << m_username << "的配置文件已存在。";
        return false;
    }
    if (password.isEmpty()) {
        qWarning() << "LoginManager: 新用户的密码不能为空。";
        return false;
    }

    m_storedSalt = CryptoUtils::generateSalt(); // 生成新的盐
    m_storedPasswordHash = CryptoUtils::hashPasswordForStorage(password, m_storedSalt); // 哈希密码

    // 为会话派生主密钥
    m_derivedMasterKey = CryptoUtils::pbkdf2HmacSha256(password.toUtf8(), m_storedSalt, PBKDF2_ITERATIONS, CryptoUtils::AES_KEY_SIZE);

    if (m_derivedMasterKey.isEmpty()) {
        qCritical() << "LoginManager: 关键错误 - 用户" << m_username << "创建期间派生主密钥失败。";
        // 如果密钥派生失败，清除敏感信息，不要保存。
        m_storedSalt.clear();
        m_storedPasswordHash.clear();
        return false;
    }

    if (!saveCredentials()) { // 保存新凭据
        qCritical() << "LoginManager: 关键错误 - 用户" << m_username << "创建后保存凭据失败。";
        // 保存失败，清除敏感信息。
        m_storedSalt.clear();
        m_storedPasswordHash.clear();
        m_derivedMasterKey.clear();
        return false;
    }
    qInfo() << "LoginManager: 用户" << m_username << "创建成功。";
    return true;
}

/**
 * @brief 验证用户密码并执行登录。
 * @param password 用户输入的主密码。
 * @return 如果登录成功，返回 true。
 */
bool LoginManager::login(const QString& password) {
    if (!doesUserExist()) {
        qWarning() << "LoginManager: 尝试登录不存在的用户配置文件：" << m_username;
        return false;
    }
    if (password.isEmpty()){
        qWarning() << "LoginManager: 用户" << m_username << "尝试使用空密码登录。";
        return false;
    }

    QByteArray currentHash = CryptoUtils::hashPasswordForStorage(password, m_storedSalt); // 计算输入密码的哈希

    // 重要提示：为了防止时序攻击 (timing attacks)，哈希比较应该使用恒定时间比较函数。
    // QCryptographicHash::compare 不是恒定时间的。QByteArray::operator== 也不是。
    // 对于本地应用程序，风险较低，但这是良好的安全实践。
    // Qt 没有直接提供这样的函数。一个简单的循环实现（非严格恒定时间，但比直接比较好）：
    bool hashesMatch = (currentHash.size() == m_storedPasswordHash.size());
    if (hashesMatch) {
        // 严格的恒定时间比较应该不依赖于提前退出的 break。
        // 为了简单演示，这里是一个基本的比较，但请注意其局限性。
        // 更安全的做法是使用专门的库函数或仔细构造的比较。
        volatile int diff = 0; // volatile 防止优化器移除比较
        for (int i = 0; i < currentHash.size(); ++i) {
            diff |= (currentHash.at(i) ^ m_storedPasswordHash.at(i));
        }
        hashesMatch = (diff == 0);
    }
    // 如果大小不同，它们肯定不匹配。上面的比较已隐式处理。

    if (hashesMatch) {
        // 密码正确，派生主加密密钥
        m_derivedMasterKey = CryptoUtils::pbkdf2HmacSha256(password.toUtf8(), m_storedSalt, PBKDF2_ITERATIONS, CryptoUtils::AES_KEY_SIZE);
        if (m_derivedMasterKey.isEmpty()) {
            qCritical() << "LoginManager: 关键错误 - 用户" << m_username << "登录期间派生主密钥失败，即使密码哈希匹配。";
            return false; // 如果发生这种情况，可能是安全风险或重大错误。
        }
        qInfo() << "LoginManager: 用户" << m_username << "登录成功。";
        return true;
    }

    qWarning() << "LoginManager: 用户" << m_username << "登录失败 - 密码错误。";
    m_derivedMasterKey.clear(); // 清除任何先前（可能无效的）密钥
    return false;
}

/**
 * @brief 获取派生出的主加密密钥。
 * @return QByteArray 主加密密钥。
 */
const QByteArray& LoginManager::getMasterKey() const {
    return m_derivedMasterKey;
}

/**
 * @brief 检查用户当前是否已登录。
 * @return 如果 m_derivedMasterKey 非空，则返回 true。
 */
bool LoginManager::isLoggedIn() const {
    return !m_derivedMasterKey.isEmpty();
}

/**
 * @brief 获取当前用户名。
 * @return QString 用户名。
 */
QString LoginManager::getUsername() const {
    return m_username;
}

/**
 * @brief 获取密码库文件的建议存储路径。
 * @return QString 密码库文件的完整路径。
 */
QString LoginManager::getVaultFilePath() const {
    QFileInfo credFileInfo(m_credentialsFilePath);
    // 确保密码库与凭据文件在同一目录。
    return credFileInfo.absolutePath() + "/" + m_username + "_vault.json.enc";
}

/**
 * @brief 更改用户的主密码。
 * @param oldPassword 当前主密码。
 * @param newPassword 新的主密码。
 * @param passwordManager 对 PasswordManager 实例的引用，其数据需要重新加密。
 * @return 如果成功，返回 true。
 */
bool LoginManager::changeMasterPassword(const QString& oldPassword, const QString& newPassword, PasswordManager& passwordManager) {
    qInfo() << "LoginManager: 用户" << m_username << "尝试更改主密码。";

    // 1. 验证旧密码。
    //    我们需要旧的 derivedMasterKey 来进行重新加密。
    //    如果用户已登录，m_derivedMasterKey 就是旧密钥。
    if (!isLoggedIn()) {
        qWarning() << "LoginManager::changeMasterPassword: 用户必须先登录才能更改密码。";
        // 或者，在此处执行登录检查：
        // if (!this->login(oldPassword)) { ... }
        // 为简单起见，假设用户已登录。
        return false;
    }
    // 额外检查：根据存储的哈希验证旧密码，不仅仅依赖于之前的登录状态
    QByteArray oldPasswordVerificationHash = CryptoUtils::hashPasswordForStorage(oldPassword, m_storedSalt);
    // 使用之前讨论的恒定时间比较方法
    bool oldPasswordMatches = (oldPasswordVerificationHash.size() == m_storedPasswordHash.size());
    if (oldPasswordMatches) {
        volatile int diff = 0;
        for (int i = 0; i < oldPasswordVerificationHash.size(); ++i) {
            diff |= (oldPasswordVerificationHash.at(i) ^ m_storedPasswordHash.at(i));
        }
        oldPasswordMatches = (diff == 0);
    }

    if (!oldPasswordMatches) {
        qWarning() << "LoginManager::changeMasterPassword: 旧密码验证失败。";
        return false;
    }
    // 当前的 m_derivedMasterKey 是“旧主密钥”，因为使用 oldPassword 登录成功了。
    QByteArray oldMasterKey = m_derivedMasterKey;


    // 2. 验证新密码（例如，非空，符合复杂度要求等）
    if (newPassword.isEmpty()) {
        qWarning() << "LoginManager::changeMasterPassword: 新密码不能为空。";
        return false;
    }
    if (newPassword == oldPassword) {
        qWarning() << "LoginManager::changeMasterPassword: 新密码不能与旧密码相同。";
        return false; // 或根据策略允许
    }

    // 3. 生成新的盐，并从新密码派生新的主密钥。
    QByteArray newSalt = CryptoUtils::generateSalt();
    QByteArray newPasswordHashForStorage = CryptoUtils::hashPasswordForStorage(newPassword, newSalt);
    QByteArray newMasterEncryptionKey = CryptoUtils::pbkdf2HmacSha256(newPassword.toUtf8(), newSalt, PBKDF2_ITERATIONS, CryptoUtils::AES_KEY_SIZE);

    if (newMasterEncryptionKey.isEmpty()) {
        qCritical() << "LoginManager::changeMasterPassword: 关键错误 - 从新密码派生新主密钥失败。";
        return false; // 不要继续。
    }

    // 4. 指示 PasswordManager 重新加密其所有数据。
    //    这是最关键且可能耗时最长的操作。
    qInfo() << "LoginManager: 调用 PasswordManager 重新加密密码库数据...";
    if (!passwordManager.reEncryptAllData(oldMasterKey, newMasterEncryptionKey)) {
        qCritical() << "LoginManager::changeMasterPassword: 关键错误 - PasswordManager 未能重新加密其数据密码库。";
        qCritical() << "LoginManager: 用户的凭据尚未更新。密码库可能处于不一致状态，或者仍使用旧密钥加密。";
        // 此时，PasswordManager 的 m_encryptionHandler 可能已更新为新密钥，
        // 但 saveVault 可能失败了。或者 reEncryptAllData 更早中止了。
        // 最安全的做法是不更改 LoginManager 的凭据。
        // 应通知用户操作失败，并且其旧密码仍然有效。
        // 复杂的应用程序可能会尝试将 PasswordManager 恢复到调用 reEncryptAllData 之前的状态。
        return false;
    }
    qInfo() << "LoginManager: PasswordManager 成功重新加密密码库数据。";

    // 5. 如果重新加密成功，则更新 LoginManager 的凭据和活动密钥。
    m_storedSalt = newSalt;
    m_storedPasswordHash = newPasswordHashForStorage;
    m_derivedMasterKey = newMasterEncryptionKey; // 更新当前会话的活动密钥

    // 6. 将新凭据（新盐、新哈希）保存到磁盘。
    if (!saveCredentials()) {
        qCritical() << "LoginManager::changeMasterPassword: 关键错误 - 成功重新加密数据，但未能保存新的登录凭据！";
        qCritical() << "LoginManager: 应用程序现在处于不一致状态。密码库使用新密钥加密，但登录将使用旧凭据。";
        // 这是一个非常糟糕的状态。用户可能会被锁定。
        // 尝试恢复 PasswordManager 的重新加密会很复杂。
        // 可能需要手动恢复或从备份中恢复。
        // 目前，通知并返回 false。
        // 一种策略：尝试将 m_derivedMasterKey 设置回 oldMasterKey，以允许当前会话可能再次使用旧密钥保存 PM？有风险。
        return false;
    }

    qInfo() << "LoginManager: 用户" << m_username << "的主密码已成功更改。新凭据已保存。";
    return true;
}
