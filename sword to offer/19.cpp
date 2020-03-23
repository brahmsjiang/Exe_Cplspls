#include <iostream>

using namespace std;

bool matchCore(char* str, char* pattern)
{
	if (*pattern == '\0' && *str == '\0')
		return true;

	if (*pattern == '\0' && *str != '\0')
		return false;

	if (*(pattern + 1) == '*') {
		if (*pattern == *str && *str != '0')
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

bool match(char* str, char* pattern)
{
	if (nullptr == str || nullptr == pattern)
		return false;
	return matchCore(str, pattern);
}


int main(int argc, char* argv[])
{
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
	cout << match("aaa", "a*a") << endl;// true!!!!!!!!!!
	cout << match("aaaaa", "a*a") << endl;// true!!!!!!!!!!
	cout << match("aaa", "ab*a") << endl;// false
	cout << match("aaa", "ab*ac*a") << endl;// true
	cout << match("aaa", "ab*a*c*a") << endl;// true
#if 0

	Test("Test25", "aaa", ".*", true);
	Test("Test26", "aab", "c*a*b", true);
	Test("Test27", "aaca", "ab*a*c*a", true);
	Test("Test28", "aaba", "ab*a*c*a", false);
	Test("Test29", "bbbba", ".*a*a", true);
	Test("Test30", "bcbbabab", ".*a*a", false);
#endif
	return 0;
}