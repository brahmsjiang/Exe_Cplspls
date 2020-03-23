#include <iostream>

using namespace std;

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);

// A[.[B]][e|EC] or .B[e|EC]
// A整数(可带符号) B小数(无符号) C指数(可带符号)
bool isNumeric(const char* str)
{
    if (nullptr == str)
        return false;

    bool numeric = scanInteger(&str);
    //出现'.', 接下来是小数部分
    if (*str == '.')
    {
        ++str;
        //.123 or 233. or 233.123
        numeric = scanUnsignedInteger(&str) || numeric;
    }

    if (*str == 'e' || *str == 'E')
    {
        ++str;
        // .e1 or e1 is invalid
        // 12e or 12e+5.4 is also invalid
        numeric = numeric && scanInteger(&str);
    }
    return numeric && *str == '\0';
}

bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
        ++(*str);

    //当str中存在0~9数字时，返回true
    return *str > before;
}

bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-')
        ++(*str);
    return scanUnsignedInteger(str);
}

int main(int argc, char* argv[])
{
    cout << isNumeric("+1") << endl;
    cout << isNumeric("-0") << endl;
    cout << isNumeric("11.23") << endl;
    cout << isNumeric(".45") << endl;
    cout << isNumeric("8.67") << endl;
    cout << isNumeric("89") << endl;
    cout << isNumeric("021.2e+2") << endl;
    cout << isNumeric("210.2E-2") << endl;
    cout << isNumeric("") << endl;
    cout << isNumeric(nullptr) << endl;
    return 0;
}