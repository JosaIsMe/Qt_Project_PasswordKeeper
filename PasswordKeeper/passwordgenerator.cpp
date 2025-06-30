#include "passwordgenerator.h"
#include <QRandomGenerator> // Qt 安全随机数生成器
#include <QVector>          // 用于构建字符集并打乱
#include <algorithm>        // 用于 std::shuffle (Qt 6) 或自定义打乱逻辑
#include <QDebug>

PasswordGenerator::PasswordGenerator() {} // 构造函数实现（如果需要）

QString PasswordGenerator::generatePassword(int length,
                                            bool useUppercase,
                                            bool useLowercase,
                                            bool useDigits,
                                            bool useSymbols) {
    // 参数有效性检查
    if (length <= 0 || (!useUppercase && !useLowercase && !useDigits && !useSymbols)) {
        qWarning() << "PasswordGenerator: 无效的密码生成参数（长度过短或未选择字符类型）。";
        return QString(); // 返回空字符串表示无效
    }

    QString charset; // 用于构建可用字符集的字符串
    // 根据用户选择构建字符集
    if (useUppercase) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (useLowercase) charset += "abcdefghijklmnopqrstuvwxyz";
    if (useDigits)    charset += "0123456789";
    // 可以根据需要自定义符号集
    if (useSymbols)   charset += "!@#$%^&*()_+-=[]{};':\",./<>?";

    // 如果最终字符集为空（理论上不应发生，因为上面已检查），则返回空
    if (charset.isEmpty()) {
        qWarning() << "PasswordGenerator: 字符集为空，无法生成密码。";
        return QString();
    }

    QString password;       // 用于存储生成的密码
    password.reserve(length); // 预分配空间以提高效率

    // 确保密码中至少包含每种选定字符类型的一个字符（如果长度允许）
    // 这部分逻辑可以使密码看起来更“符合要求”，但如果处理不当会略微降低随机性。
    // 一个更简单的方法是完全随机选择，然后检查是否满足所有类型（如果需要严格满足）。
    // 当前实现：先强制包含，然后随机填充剩余部分，最后打乱。
    QVector<QChar> tempPasswordChars; // 使用 QVector<QChar> 以便打乱

    if (useUppercase) {
        tempPasswordChars.append(charset[QRandomGenerator::global()->bounded(charset.indexOf('A'), charset.indexOf('Z') + 1)]);
    }
    if (useLowercase && tempPasswordChars.size() < length) { // 确保不超过总长度
        tempPasswordChars.append(charset[QRandomGenerator::global()->bounded(charset.indexOf('a'), charset.indexOf('z') + 1)]);
    }
    if (useDigits && tempPasswordChars.size() < length) {
        tempPasswordChars.append(charset[QRandomGenerator::global()->bounded(charset.indexOf('0'), charset.indexOf('9') + 1)]);
    }
    if (useSymbols && tempPasswordChars.size() < length) {
        // 注意：符号集的索引起始位置需要硬编码或动态查找
        int symbolStartIndex = charset.indexOf('!');
        if (symbolStartIndex != -1) { // 确保符号集存在于 charset 中
            // 符号集的结束索引是 charset.length()
            tempPasswordChars.append(charset[QRandomGenerator::global()->bounded(symbolStartIndex, charset.length())]);
        }
    }

    // 随机填充密码的剩余部分
    for (int i = tempPasswordChars.size(); i < length; ++i) {
        int randomIndex = QRandomGenerator::global()->bounded(charset.length()); // 从整个字符集中随机选择
        tempPasswordChars.append(charset[randomIndex]);
    }

    // 打乱 tempPasswordChars 中的字符，以确保初始强制添加的字符位置是随机的
    // Qt 6 可以使用 std::shuffle 和 QRandomGenerator 作为随机数引擎
    // #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    //     std::shuffle(tempPasswordChars.begin(), tempPasswordChars.end(), *QRandomGenerator::global());
    // #else
    // 对于 Qt 5，一个简单的 Fisher-Yates shuffle 实现：
    for (int i = tempPasswordChars.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(i + 1); // 0 <= j <= i
        std::swap(tempPasswordChars[i], tempPasswordChars[j]); // 交换元素
    }
    // #endif

    // 将打乱后的字符数组转换回 QString
    for(const QChar& qc : tempPasswordChars) {
        password += qc;
    }

    return password;
}
