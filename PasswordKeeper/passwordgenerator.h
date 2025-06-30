#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>

class PasswordGenerator {
public:
    /**
     * @brief PasswordGenerator 构造函数（如果需要实例化，但静态方法通常足够）。
     */
    PasswordGenerator();

    /**
     * @brief 生成一个随机密码。
     * @param length 密码的期望长度。
     * @param useUppercase 是否包含大写字母 (A-Z)。
     * @param useLowercase 是否包含小写字母 (a-z)。
     * @param useDigits 是否包含数字 (0-9)。
     * @param useSymbols 是否包含特殊符号 (例如 !@#$%^&* 等)。
     * @return QString 生成的随机密码；如果参数无效（例如长度为0或未选择字符集），则返回空字符串。
     */
    static QString generatePassword(int length,
                                    bool useUppercase,
                                    bool useLowercase,
                                    bool useDigits,
                                    bool useSymbols);
};

#endif // PASSWORDGENERATOR_H
