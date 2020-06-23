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
    int longestLen = 0, longestLenBackup = 0;
    //position[] means a letter's appearing index last time, -1 means never appear
    int* position = new int[26];
    for (int i = 0; i < 26; ++i)
        position[i] = -1;

    for (int i = 0; i < str.size(); ++i)
    {
        if (position[str[i] - 'a'] != -1)    //cur char duplicates
        {
            if (i - position[str[i] - 'a'] > longestLen)
            {
                ++longestLen;
            }
            else    //longestLen doesn't increase this time, consider a backup longestLen
            {

            }
        }
        else    //cur char doesn't duplicate
        {
            ++longestLen;
        }
        position[str[i] - 'a'] = i;
    }

    return longestLen;
}


int main(int argc, char* argv[])
{
    string forTest("arabcacfrea");
    int res = longestSubStrWithoutDup1(forTest);
    res = longestSubStrWithoutDup2(forTest);
    return 0;
}