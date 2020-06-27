#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
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
	int curLen = 0;
	int maxLen = 0;

	int* position = new int[26];
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < str.length(); i++)
	{
		int prevIdx = position[str[i] - 'a'];
		if (prevIdx < 0 || i - prevIdx > curLen)
			++curLen;
		else
		{
			// duplication occurs
			if (curLen > maxLen)
				maxLen = curLen;
			// ara, if idx == 3, update curLen = 2, means new substr is "ra"
			curLen = i - prevIdx;
		}
		position[str[i] - 'a'] = i;
	}
	if (curLen > maxLen)
		maxLen = curLen;

	delete[] position;
	return maxLen;
}


int main(int argc, char* argv[])
{
    string forTest("arabcacfrea");
    //int res = longestSubStrWithoutDup1(forTest);
    int res2 = longestSubStrWithoutDup2(forTest);
    return 0;
}