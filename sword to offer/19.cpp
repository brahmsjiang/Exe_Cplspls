#include <iostream>
#include <string>

using namespace std;

bool matchCore(const char* str, const char* pattern)
{
	if (*pattern == '\0' && *str == '\0')
		return true;
    // str is longer than pattern, mismatch absolutely
    // however there' need to match when pattern's longer than str, for case: c[a]*\0 <=> ca[\0], '[]' means current char 
	if (*pattern == '\0' && *str != '\0')
		return false;

	if (*(pattern + 1) == '*') {
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))  // '.*' can't match '\0'
			// move on the next state, both consume cur_char and 'a*', for case 'a*' matches cur_char once: aa <=> a*a or ab <=> a*b
			return matchCore(str + 1, pattern + 2)
			// stay on the current state, only consume cur_char, for case 'a*' matches a set of repeated cur_char: aaaab <=> a*b
			|| matchCore(str + 1, pattern)
			// only consume 'a*', for case 'a*' matches nothing: c <=> a*c
			|| matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);
	}
	if (*pattern == *str || (*pattern == '.' && *str != '\0'))
		return matchCore(str + 1, pattern + 1);

	return false;
}

bool match(string str, string pattern)
{
	if (str.empty() || str.empty())
		return false;
	return matchCore(str.c_str(), pattern.c_str());
}


int main(int argc, char* argv[])
{
#if 0
	cout << match("", "") << endl;// true
	cout << match("", ".*") << endl;// true
	cout << match("", ".") << endl;// false
	cout << match("", "c*") << endl;// true
	cout << match("a", ".*") << endl;// true
	cout << match("a", "a.") << endl;// false
	cout << match("a", "") << endl;// false
	cout << match("a", ".") << endl;// true
	cout << match("a", "ab*") << endl;// true
	cout << match("a", "ab*a") << endl;// false
	cout << match("aa", "aa") << endl;// true
	cout << match("aa", "a*") << endl;// true
	cout << match("aa", ".*") << endl;// true
	cout << match("aa", ".") << endl;// false
	cout << match("ab", ".*") << endl;// true
	cout << match("ab", ".*") << endl;// true
	cout << match("aaa", "aa*") << endl;// true
	cout << match("aaa", "aa.a") << endl;// false
	cout << match("aaa", "a.a") << endl;// true
	cout << match("aaa", ".a") << endl;// false
	cout << match("aaa", "a*a") << endl;// true
	cout << match("aaa", "ab*a") << endl;// false
	cout << match("aaa", "ab*ac*a") << endl;// true
	cout << match("aaa", ".*") << endl;// true
#endif
    cout << match("aab", "c*a*b") << endl;// true
    cout << match("aaca", "ab*a*c*a") << endl;// true
    cout << match("aaba", "ab*a*c*a") << endl;// false
    cout << match("bbbba", ".*a*a") << endl;// true
    cout << match("bcbbabab", ".*a*a") << endl;// false

	return 0;
}