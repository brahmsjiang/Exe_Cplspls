#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int getTransCount(int number)
{
    if (number < 0)
        return 0;
    
    string numberInStr = std::to_string(number);
    return getTransCount(numberInStr);
}

int getTransCount(const string& number)
{
    int length = number.length();
    int* counts = new int[length];
    int count = 0;

    for (int i = length - 1; i >= 0; --i)
    {

    }

}

int main(int argc, char* argv[])
{

    return 0;
}