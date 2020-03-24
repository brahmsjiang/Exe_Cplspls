#include <iostream>

using namespace std;

bool scanUnsignedInteger(const char** str);
bool scanInteger(const char** str);

// A[.[B]][e|EC] or .B[e|EC]
// A整数(可带符号) B小数(无符号) C指数(可带符号)
bool isNumeric(const char* str)
{
    if (str == nullptr)
        return false;

    bool numeric = scanInteger(&str);//这里要改动char*的值，必须传入char**
    if (*str == '.')
    {
        str++;//这里str++,对isNumeric用户而言不会改str的值。但经scanUnsignedInteger调用后,str的值被改变了；因为后续判断需要移动str指针的值
        numeric = scanUnsignedInteger(&str) || numeric;
    }
    if (*str == 'e' || *str == 'E')//'e|E'前面可以不带符号
    {
        str++;
        numeric = scanInteger(&str) && numeric;
    }
    return (*str == '\0') && numeric;//必须字符串到末尾,否则表示中间有非法字符
}

bool scanUnsignedInteger(const char** str)
{
    const char* before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
        ++(*str);
    return *str > before;
}

bool scanInteger(const char** str)
{
    if (**str == '+' || **str == '-')//这里的正负号可有可无,所以scanUnsignedInteger不放在if语句内
        ++(*str);
    return scanUnsignedInteger(str);
}

int main(int argc, char* argv[])
{
#if 0
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
#endif    
    cout << isNumeric("1 ") << endl;
    return 0;
}