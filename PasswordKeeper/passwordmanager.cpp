#include "passwordmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>      // 用于目录操作
#include <QFileInfo> // 用于文件信息
#include <QDebug>

// --- SiteEntry 实现 (与之前相同) ---
QJsonObject SiteEntry::toJson() const {
    QJsonObject obj;
    obj["siteName"] = siteName;
    obj["username"] = username;
    obj["encPass"] = QString::fromLatin1(encryptedPassword.toBase64()); // 将 QByteArray Base64 编码为字符串
    if (!fileKeyIdentifier.isEmpty()) {
        obj["fileKeyId"] = fileKeyIdentifier;
        obj["encFileKey"] = QString::fromLatin1(encryptedFileKey.toBase64());
    }
    return obj;
}

SiteEntry SiteEntry::fromJson(const QJsonObject& obj) {
    SiteEntry entry;
    entry.siteName = obj["siteName"].toString();
    entry.username = obj["username"].toString();
    entry.encryptedPassword = QByteArray::fromBase64(obj["encPass"].toString().toLatin1()); // 从 Base64 字符串解码
    if (obj.contains("fileKeyId")) {
        entry.fileKeyIdentifier = obj["fileKeyId"].toString();
        entry.encryptedFileKey = QByteArray::fromBase64(obj["encFileKey"].toString().toLatin1());
    }
    return entry;
}

// --- PasswordManager 构造函数, loadVault, saveVault, addEntry 等 (与之前提供的一致) ---
PasswordManager::PasswordManager(const QByteArray& masterKey, const QString& vaultFilePath)
    : m_vaultFilePath(vaultFilePath) {
    m_encryptionHandler.setMasterKey(masterKey); // 设置用于加密/解密的主密钥
    if (!m_encryptionHandler.isKeySet()) {
        // 这是一个严重错误，应用程序可能不应继续。
        qCritical() << "PasswordManager: 主密钥未设置或无效。密码库将无法访问。";
    } else {
        loadVault(); // 加载现有的密码库（如果存在）
    }
}

PasswordManager::~PasswordManager() {
    // 可选：考虑在析构时保存未保存的更改，
    // 但通常显式保存更好。
    // saveVault();
}

bool PasswordManager::loadVault() {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 无法加载密码库，主密钥未设置。";
        return false;
    }

    QFile vaultFile(m_vaultFilePath);
    if (!vaultFile.exists()) {
        qInfo() << "PasswordManager: 密码库文件不存在，将创建新的：" << m_vaultFilePath;
        m_entries.clear(); // 确保如果文件不存在，条目列表是空的
        return true; // 没有密码库可加载，这对于新用户是正常的
    }

    if (!vaultFile.open(QIODevice::ReadOnly)) {
        qWarning() << "PasswordManager: 无法打开密码库文件进行读取：" << vaultFile.errorString();
        return false;
    }

    QByteArray encryptedData = vaultFile.readAll(); // 读取整个加密文件
    vaultFile.close();

    if (encryptedData.isEmpty()) { // 可能是之前错误或新创建的空文件
        qInfo() << "PasswordManager: 密码库文件为空。";
        m_entries.clear();
        return true;
    }

    QByteArray jsonData = m_encryptionHandler.decryptData(encryptedData); // 解密数据
    // 特别检查解密是否失败（例如，密钥错误或文件损坏）
    if (jsonData.isNull() && !encryptedData.isEmpty()) {
        qWarning() << "PasswordManager: 解密密码库数据失败。密钥错误或文件损坏。";
        return false;
    }
    // 解密后数据为空（可能是空密码库或解密问题）
    if (jsonData.isEmpty()) { // (jsonData.isNull() || jsonData.isEmpty())
        qWarning() << "PasswordManager: 解密后的密码库数据为空。假设是空的或新的密码库。";
        m_entries.clear();
        return true; // 或者如果这应该是一个错误，则返回 false
    }


    QJsonDocument doc = QJsonDocument::fromJson(jsonData); // 从解密后的JSON数据创建文档
    if (doc.isNull() || !doc.isArray()) { // 检查JSON是否有效且为数组格式
        qWarning() << "PasswordManager: 解密后的密码库数据中 JSON 格式无效（应为数组）。";
        return false;
    }

    m_entries.clear(); // 清空现有条目以加载新的
    QJsonArray entriesArray = doc.array(); // 获取JSON数组
    for (const QJsonValue& val : entriesArray) { // 遍历数组中的每个值
        if (val.isObject()) { // 如果值是一个JSON对象
            SiteEntry entry = SiteEntry::fromJson(val.toObject()); // 从对象创建SiteEntry
            if (!entry.siteName.isEmpty()) { // 确保站点名称非空
                m_entries.insert(entry.siteName, entry); // 将条目插入到map中
            }
        }
    }
    qInfo() << "PasswordManager: 密码库加载成功，包含" << m_entries.count() << "个条目。";
    return true;
}

bool PasswordManager::saveVault() const {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 无法保存密码库，主密钥未设置。";
        return false;
    }

    QJsonArray entriesArray; // 创建一个JSON数组来存储所有条目
    for (const SiteEntry& entry : m_entries.values()) { // 遍历map中的所有条目
        entriesArray.append(entry.toJson()); // 将每个条目转换为JSON对象并添加到数组
    }
    QJsonDocument doc(entriesArray); // 从数组创建JSON文档
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact); // 将JSON文档转换为紧凑的字节数组

    QByteArray encryptedData = m_encryptionHandler.encryptData(jsonData); // 加密JSON数据
    // 如果jsonData非空但encryptedData为空，表示加密失败
    if (encryptedData.isEmpty() && !jsonData.isEmpty()) {
        qWarning() << "PasswordManager: 加密密码库数据以供保存时失败。";
        return false;
    }
    // 如果jsonData为空（空密码库），encryptedData通常不为空（因为IV和填充）
    // 此处逻辑：如果jsonData为空，encryptedData也为空是可接受的（如果加密空数据返回空）
    // 但实际上，CryptoUtils::aesEncrypt 对空输入应该返回非空（IV+填充）。
    // 我们主要关心的是，如果jsonData非空，encryptedData不应为空。


    QFile vaultFile(m_vaultFilePath);
    // 在写入前确保目录存在（对首次保存很重要）
    QFileInfo vaultFileInfo(m_vaultFilePath);
    QDir dir = vaultFileInfo.dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) { // "." 表示创建路径中的所有父目录
            qWarning() << "PasswordManager: 无法为密码库文件创建目录：" << dir.path();
            return false;
        }
    }

    if (!vaultFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) { // 以写入、截断模式打开文件
        qWarning() << "PasswordManager: 无法打开密码库文件进行写入：" << vaultFile.errorString();
        return false;
    }
    qint64 bytesWritten = vaultFile.write(encryptedData); // 将加密数据写入文件
    if (bytesWritten != encryptedData.size()) {
        qWarning() << "PasswordManager: 未能将完整的密码库数据写入文件。写入了" << bytesWritten << "字节，总共" << encryptedData.size() << "字节。";
        vaultFile.close(); // 尝试关闭
        // 在这里更安全的做法是尝试删除部分写入的文件或恢复备份。
        // 目前，我们只报告错误。
        return false;
    }
    vaultFile.close();
    qInfo() << "PasswordManager: 密码库成功保存到" << m_vaultFilePath;
    return true;
}

bool PasswordManager::addEntry(const QString& siteName, const QString& username, const QString& password) {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法添加条目。";
        return false;
    }
    if (siteName.isEmpty()) {
        qWarning() << "PasswordManager: 站点名称不能为空。";
        return false;
    }
    if (m_entries.contains(siteName)) { // 检查站点名称是否已存在
        qWarning() << "PasswordManager: 站点名称已存在：" << siteName;
        return false;
    }

    SiteEntry entry;
    entry.siteName = siteName;
    entry.username = username;
    QByteArray plainPasswordBytes = password.toUtf8(); // 将密码转换为UTF-8字节数组
    entry.encryptedPassword = m_encryptionHandler.encryptData(plainPasswordBytes); // 加密密码

    // 如果密码非空但加密结果为空，则表示加密失败
    if (entry.encryptedPassword.isEmpty() && !plainPasswordBytes.isEmpty()){
        qWarning() << "PasswordManager: 为站点" << siteName << "加密密码失败。";
        return false; // 如果密码加密失败，则不添加条目
    }

    m_entries.insert(siteName, entry); // 将新条目插入到map
    return saveVault(); // 保存密码库
}

bool PasswordManager::updateEntry(const QString& siteName, const QString& newUsername, const QString& newPassword) {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法更新条目。";
        return false;
    }
    if (!m_entries.contains(siteName)) { // 检查条目是否存在
        qWarning() << "PasswordManager: 未找到要更新的站点名称：" << siteName;
        return false;
    }

    SiteEntry& entry = m_entries[siteName]; // 获取对现有条目的引用
    entry.username = newUsername;
    QByteArray plainPasswordBytes = newPassword.toUtf8();
    entry.encryptedPassword = m_encryptionHandler.encryptData(plainPasswordBytes); // 加密新密码

    if (entry.encryptedPassword.isEmpty() && !plainPasswordBytes.isEmpty()){
        qWarning() << "PasswordManager: 为站点更新" << siteName << "加密密码失败。";
        return false; // 不要保存可能已损坏的数据
    }

    return saveVault(); // 保存更改
}

bool PasswordManager::removeEntry(const QString& siteName) {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法删除条目。";
        return false;
    }
    if (m_entries.remove(siteName) > 0) { // QMap::remove 返回被删除的元素数量
        return saveVault(); // 如果成功删除，则保存密码库
    }
    qWarning() << "PasswordManager: 未找到要删除的站点名称：" << siteName;
    return false; // 条目未找到
}

QString PasswordManager::getDecryptedPassword(const QString& siteName) const {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法解密密码。";
        return QString(); // 返回空字符串或处理错误
    }
    if (!m_entries.contains(siteName)) {
        qWarning() << "PasswordManager: 未找到要解密的站点名称：" << siteName;
        return QString();
    }

    const SiteEntry& entry = m_entries.value(siteName); // 获取条目（const引用）
    QByteArray decryptedBytes = m_encryptionHandler.decryptData(entry.encryptedPassword); // 解密密码

    // 如果加密密码非空但解密结果为null，则表示解密失败
    if (decryptedBytes.isNull() && !entry.encryptedPassword.isEmpty()){
        qWarning() << "PasswordManager: 为站点" << siteName << "解密密码失败。密钥错误或数据损坏。";
        return QString(); // 解密失败
    }
    return QString::fromUtf8(decryptedBytes); // 将解密后的字节数组转换为UTF-8字符串
}

QVariantMap PasswordManager::getEntryDetails(const QString& siteName) const {
    QVariantMap details;
    if (m_entries.contains(siteName)) {
        const SiteEntry& entry = m_entries.value(siteName);
        details["siteName"] = entry.siteName;
        details["username"] = entry.username;
        // 出于安全原因，此处不应包含解密后的密码，仅供UI显示站点名和用户名
    }
    return details;
}

QList<QString> PasswordManager::getAllSiteNames() const {
    return m_entries.keys(); // 返回map中所有键（即站点名称）的列表
}

bool PasswordManager::storeEncryptedFileKey(const QString& siteNameOrIdentifier, const QString& fileKeyId, const QByteArray& plainFileKey) {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法存储文件密钥。";
        return false;
    }

    SiteEntry* entryPtr = nullptr; // 指向要操作的 SiteEntry
    if (m_entries.contains(siteNameOrIdentifier)) {
        entryPtr = &m_entries[siteNameOrIdentifier]; // 获取现有条目的引用
    } else {
        // 如果标识符不存在，则为其创建一个新条目。
        // 此条目可能只包含文件密钥，没有站点密码。
        SiteEntry newKeyEntry;
        newKeyEntry.siteName = siteNameOrIdentifier; // 使用该标识符作为新条目的主键
        // 插入新条目并获取其迭代器，然后通过迭代器获取值的引用
        auto it = m_entries.insert(siteNameOrIdentifier, newKeyEntry);
        entryPtr = &it.value(); // 获取新插入条目的引用
    }

    entryPtr->fileKeyIdentifier = fileKeyId; // 设置文件密钥的特定ID
    entryPtr->encryptedFileKey = m_encryptionHandler.encryptData(plainFileKey); // 加密文件密钥

    // 如果明文密钥非空但加密结果为空，则表示加密失败
    if (entryPtr->encryptedFileKey.isEmpty() && !plainFileKey.isEmpty()){
        qWarning() << "PasswordManager: 为" << fileKeyId << "加密文件密钥失败。";
        // 如果加密失败，我们可能不想保存，或者删除部分修改的条目。
        // 目前，返回 false 并且不保存。
        // 考虑删除刚刚为此密钥添加的新条目。
        return false;
    }
    return saveVault(); // 保存对密码库的更改
}

QByteArray PasswordManager::getDecryptedFileKey(const QString& siteNameOrIdentifier, const QString& fileKeyId) const {
    if (!m_encryptionHandler.isKeySet()) {
        qWarning() << "PasswordManager: 主密钥未设置。无法获取文件密钥。";
        return QByteArray();
    }
    if (!m_entries.contains(siteNameOrIdentifier)) {
        qWarning() << "PasswordManager: 用于文件密钥检索的标识符未找到：" << siteNameOrIdentifier;
        return QByteArray();
    }

    const SiteEntry& entry = m_entries.value(siteNameOrIdentifier); // 获取关联的条目
    // 确保请求的 fileKeyId 与存储的匹配（如果 SiteEntry 中使用了特定标识符）。
    // 如果传入的 fileKeyId 为空，可能意味着 siteNameOrIdentifier 直接映射到一个文件密钥（不常用）。
    // 为简单起见，假设如果 SiteEntry 中存在 fileKeyIdentifier，则它必须匹配。
    if ((entry.fileKeyIdentifier == fileKeyId || fileKeyId.isEmpty()) && !entry.encryptedFileKey.isEmpty()) {
        QByteArray decryptedKey = m_encryptionHandler.decryptData(entry.encryptedFileKey); // 解密文件密钥
        // 如果加密密钥非空但解密结果为null，则表示解密失败
        if (decryptedKey.isNull() && !entry.encryptedFileKey.isEmpty()) {
            qWarning() << "PasswordManager: 为" << fileKeyId << "在" << siteNameOrIdentifier << "下解密文件密钥失败。";
            return QByteArray();
        }
        return decryptedKey;
    }
    qWarning() << "PasswordManager: 文件密钥 ID" << fileKeyId << "未找到，或" << siteNameOrIdentifier << "没有对应的加密文件密钥。";
    return QByteArray();
}

// reEncryptAllData 方法的实现 (与之前“后续部分”的回复一致)
bool PasswordManager::reEncryptAllData(const QByteArray& oldMasterKey, const QByteArray& newMasterKey) {
    qInfo() << "PasswordManager: 开始重新加密所有数据。";

    EncryptionHandler oldEncHandler(oldMasterKey);
    EncryptionHandler newEncHandler(newMasterKey);

    if (!oldEncHandler.isKeySet()) {
        qCritical() << "PasswordManager::reEncryptAllData: 旧主密钥无效或未设置。";
        return false;
    }
    if (!newEncHandler.isKeySet()) {
        qCritical() << "PasswordManager::reEncryptAllData: 新主密钥无效或未设置。";
        return false;
    }

    for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
        SiteEntry& entry = it.value();

        if (!entry.encryptedPassword.isEmpty()) {
            QByteArray plainPassword = oldEncHandler.decryptData(entry.encryptedPassword);
            if (plainPassword.isNull() && !entry.encryptedPassword.isEmpty()) {
                qWarning() << "PasswordManager::reEncryptAllData: 使用旧密钥为站点" << entry.siteName << "解密密码失败。正在中止。";
                return false;
            }
            entry.encryptedPassword = newEncHandler.encryptData(plainPassword);
            if (entry.encryptedPassword.isEmpty() && !plainPassword.isEmpty()) {
                qWarning() << "PasswordManager::reEncryptAllData: 使用新密钥为站点" << entry.siteName << "重新加密密码失败。正在中止。";
                return false;
            }
        } else {
            entry.encryptedPassword = newEncHandler.encryptData(QByteArray());
        }

        if (!entry.encryptedFileKey.isEmpty()) {
            QByteArray plainFileKey = oldEncHandler.decryptData(entry.encryptedFileKey);
            if (plainFileKey.isNull() && !entry.encryptedFileKey.isEmpty()) {
                qWarning() << "PasswordManager::reEncryptAllData: 使用旧密钥为站点" << entry.siteName << "的文件密钥" << entry.fileKeyIdentifier << "解密失败。正在中止。";
                return false;
            }
            entry.encryptedFileKey = newEncHandler.encryptData(plainFileKey);
            if (entry.encryptedFileKey.isEmpty() && !plainFileKey.isEmpty()) {
                qWarning() << "PasswordManager::reEncryptAllData: 使用新密钥为站点" << entry.siteName << "的文件密钥" << entry.fileKeyIdentifier << "重新加密失败。正在中止。";
                return false;
            }
        } else if (!entry.fileKeyIdentifier.isEmpty()) {
            entry.encryptedFileKey = newEncHandler.encryptData(QByteArray());
        }
    }

    m_encryptionHandler.setMasterKey(newMasterKey);
    qInfo() << "PasswordManager: 内存中条目已重新加密。加密处理器已更新为新密钥。";

    if (!saveVault()) {
        qCritical() << "PasswordManager::reEncryptAllData: 关键错误 - 未能将重新加密的密码库保存到磁盘！内存数据已重新加密，但磁盘可能包含旧数据或已损坏。";
        return false;
    }

    qInfo() << "PasswordManager: 所有数据已成功重新加密并保存到磁盘。";
    return true;
}
