#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int layer = 0;
void printTab(int layer)
{
    for (size_t i = 0; i < layer; i++)
        printf("    ");
}

int getTransCount(const string& number)
{
    ++layer;
    printTab(layer);

    cout << "==>cur number:" << number << endl;

    if (number.empty())
    {
        printTab(layer);
        cout << "count: 1" << endl;
        --layer;
        return 1;
    }

    int count = 0;
    char curNumberstr[3];
    memset(curNumberstr, 0, sizeof(curNumberstr) / sizeof(char));

    //last char
    string numbertmp = number;
    numbertmp.pop_back();
    printTab(layer);
    cout << "before getTransCount, use cur char1" << endl;
    count = getTransCount(numbertmp);

    //second last two char
    if (number.size() >= 2)
    {
        strcat(curNumberstr, number.substr(number.size() - 2, 2).c_str());
        if (10 <= atoi(curNumberstr) && atoi(curNumberstr) <= 25)
        {
            numbertmp.pop_back();
            printTab(layer);
            cout << "before getTransCount, use cur char2" << endl;
            count += getTransCount(numbertmp);
        }
    }
   
    printTab(layer);
    cout << "count: " << count << endl;

    --layer;
    return count;
}

int getTransCount(int number)
{
    if (number < 0)
        return 0;

    string numberInStr = std::to_string(number);
    return getTransCount(numberInStr);
}

int main(int argc, char* argv[])
{
    cout << getTransCount(0) << endl;
    cout << getTransCount(10) << endl;
    cout << getTransCount(125) << endl;
    cout << getTransCount(126) << endl;
    cout << getTransCount(426) << endl;
    cout << getTransCount(100) << endl;
    cout << getTransCount(101) << endl;
    cout << getTransCount(12258) << endl;
    cout << getTransCount(-100) << endl;
    return 0;
}