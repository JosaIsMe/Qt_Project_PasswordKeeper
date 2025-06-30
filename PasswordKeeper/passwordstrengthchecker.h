#ifndef PASSWORDSTRENGTHCHECKER_H
#define PASSWORDSTRENGTHCHECKER_H

#include <QString>
#include <QRegularExpression>

class PasswordStrengthChecker
{
public:
    enum StrengthLevel {
        Weak,       // 弱密码
        Medium,     // 中等强度
        Strong      // 强密码
    };

    PasswordStrengthChecker();
    StrengthLevel evaluateStrength(const QString& password) const;

private:
    bool hasLowerCase(const QString& password) const;
    bool hasUpperCase(const QString& password) const;
    bool hasDigit(const QString& password) const;
    bool hasSpecialChar(const QString& password) const;
    bool isCommonPassword(const QString& password) const;
};

#endif // PASSWORDSTRENGTHCHECKER_H
