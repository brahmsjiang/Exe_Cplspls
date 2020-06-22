#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <assert.h>

using namespace std;

int longestSubStrWithoutDup1(const string& str)
{
    int longestLen = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        for (int j = i; j < str.size(); ++j)
        {
            int subStrLen = j - i + 1;
            std::string subStr(str.substr(i, subStrLen));
            std::set<char> setchar(subStr.begin(), subStr.end());

            if (subStrLen == setchar.size() && subStrLen > longestLen)
            {
                cout << "cur subStr: " << subStr.c_str() << endl;
                longestLen = subStrLen;
            }
        }
    }
    return longestLen;
}


int longestSubStrWithoutDup2(const string& str)
{
    int longestLen = 0;

    return longestLen;
}


int main(int argc, char* argv[])
{
    string forTest("arabcacfrea");
    int res = longestSubStrWithoutDup1(forTest);
    res = longestSubStrWithoutDup2(forTest);
    return 0;
}