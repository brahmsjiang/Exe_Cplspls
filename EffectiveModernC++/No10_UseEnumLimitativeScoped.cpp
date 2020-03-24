#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

class solution {
public:
	using mapNumIdx = map<size_t, pair<string::iterator, string::iterator>>;
	void mapInsert(const string::iterator& start, const string::iterator& end) {
		if (map.end() == map.find(endIdx + 1 - startIdx)) {
			map[endIdx + 1 - startIdx] = make_pair(startIdx, endIdx);
		}
	}
	string longestPalindrome(string str) {
		if (str.empty())
			return string("");

		startIdx = endIdx = str.begin();

		while (endIdx < str.end())
		{
			if (startIdx > str.begin() && (endIdx + 1) < str.end() && *(startIdx - 1) == *(endIdx + 1)) {
				mapInsert(--startIdx, ++endIdx);
			}
			else if ((endIdx + 1) < str.end() && *startIdx == *(endIdx + 1)) {
				mapInsert(startIdx, ++endIdx);
			}
			else if (startIdx == endIdx) {
				mapInsert(startIdx, endIdx);
				startIdx = ++endIdx;
			}
			else {
				startIdx = ++endIdx;
			}
		}

		return string(map.rbegin()->second.first, map.rbegin()->second.second + 1);
	}
private:
	mapNumIdx map;
	string::iterator startIdx;
	string::iterator endIdx;
};

int main(int argc, char* argv[])
{
	solution sol;
	string bbdfxacfcecfcae("bbdfxacfcecfcae");
	string bananas("bananas");

	cout << sol.longestPalindrome(bananas) << endl;
	return 0;
}