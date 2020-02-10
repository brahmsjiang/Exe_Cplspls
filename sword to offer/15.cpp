#include <iostream>

using namespace std;

int NumberOf1_1(int n)
{
    int num = 0;
    //当用数值表示真假时，0为假， 非0为真。因此，负数在IF语句中为真
    while (n)
    {
        if (n & 1)
            num++;
        n = n >> 1;
    }
    return num;
}

int NumberOf1_2(int n)
{
    int num = 0;
    int compar = 1;
    while (compar) {
        if (n & compar) {
            num++;
        }
        compar = compar << 1;
    }
    return num;
}

int NumberOf1_3(int n)
{
    int num = 0;
    while (n) {
        num++;
        n = (n - 1) & n;
    }
    return num;
}

int main(int argc, char* argv[])
{
    //cout << NumberOf1_1(-27) << endl; //dead loop, -27's highest digit is always 1 in binary
    cout << NumberOf1_2(-27) << endl;
    cout << NumberOf1_2(-1) << endl;
    cout << NumberOf1_2(0) << endl;
    cout << NumberOf1_2(27) << endl;

    cout << NumberOf1_3(-27) << endl;
    cout << NumberOf1_3(-1) << endl;
    cout << NumberOf1_3(0) << endl;
    cout << NumberOf1_3(27) << endl;
    return 0;
}