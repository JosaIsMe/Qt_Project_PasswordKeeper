#include "PasswordStrengthChecker.h"
#include <QSet>

PasswordStrengthChecker::PasswordStrengthChecker() {}

PasswordStrengthChecker::StrengthLevel PasswordStrengthChecker::evaluateStrength(const QString& password) const
{
    // 空密码直接判定为弱
    if (password.isEmpty()) {
        return Weak;
    }

    // 检查是否常见弱密码
    if (isCommonPassword(password)) {
        return Weak;
    }

    // 计算密码长度得分
    int length = password.length();
    int lengthScore = 0;

    if (length < 6) {
        lengthScore = 0;
    } else if (length < 8) {
        lengthScore = 1;
    } else if (length < 12) {
        lengthScore = 2;
    } else {
        lengthScore = 3;
    }

    // 计算字符种类得分
    int diversityScore = 0;
    if (hasLowerCase(password)) diversityScore++;
    if (hasUpperCase(password)) diversityScore++;
    if (hasDigit(password)) diversityScore++;
    if (hasSpecialChar(password)) diversityScore++;

    // 综合评分
    int totalScore = lengthScore + diversityScore;

    // 判定强度等级
    if (totalScore < 3) {
        return Weak;
    } else if (totalScore < 5) {
        return Medium;
    } else {
        return Strong;
    }
}

bool PasswordStrengthChecker::hasLowerCase(const QString& password) const
{
    return password.contains(QRegularExpression("[a-z]"));
}

bool PasswordStrengthChecker::hasUpperCase(const QString& password) const
{
    return password.contains(QRegularExpression("[A-Z]"));
}

bool PasswordStrengthChecker::hasDigit(const QString& password) const
{
    return password.contains(QRegularExpression("[0-9]"));
}

bool PasswordStrengthChecker::hasSpecialChar(const QString& password) const
{
    return password.contains(QRegularExpression("[^a-zA-Z0-9]"));
}

bool PasswordStrengthChecker::isCommonPassword(const QString& password) const
{
    // 常见弱密码
    static const QSet<QString> commonPasswords = {
        "password", "123456", "qwerty", "abc123", "letmein",
        "admin", "welcome", "monkey", "password1", "12345678",
        "123123", "114514", "111111", "sunshine", "iloveyou",
        "admin123", "mypassword", "ABCDEF", "abcdef", "itsme"
    };

    return commonPasswords.contains(password.toLower());
}
