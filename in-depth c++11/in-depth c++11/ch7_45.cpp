#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include <numeric>

using namespace std;

int main(int argc, const char * argv[]) {
	vector<int> v = {1,3,5,7,9};
	auto isOdd = [](int i){return i % 2 != 0;};
	auto isEven = [](int i){return i % 2 == 0;};
	bool isallOdd = std::all_of(v.begin(), v.end(), isOdd);
	if (isallOdd)
		cout << "all is odd" << endl;
	
	bool isNoneEven = std::none_of(v.begin(), v.end(), isEven);
	if (isNoneEven)
		cout << "none is even" << endl;

	vector<int> v1 = {1,3,5,7,8,9};
	bool anyof = std::any_of(v1.begin(), v1.end(), isEven);
	if (anyof)
		cout << "at least one is even" << endl;

	vector<int> v2 = {1,3,5,7,9,4};
	auto firstEven = std::find_if(v2.begin(), v2.end(), isEven);
	if (firstEven != v2.end())
		cout << "the first even is " << * firstEven << endl;

	auto isNotEven = [](int i){return i % 2 != 0;};
	auto firstOdd = std::find_if(v2.begin(), v2.end(), isNotEven);
	if (firstOdd != v2.end())
		cout << "the first odd is " << *firstOdd << endl;
	
	auto odd = std::find_if_not(v.begin(), v.end(), isEven);
	if (odd != v2.end())
		cout << "the first odd is " << *odd << endl;

	vector<int> v22(v2.size());
	//vector<int> v23{v2.size()};	//err, non-constant-expression cannot be narrowed from type 'size_type' (aka 'unsigned long') to 'int' in initializer list
	auto it = std::copy_if(v2.begin(), v2.end(), v22.begin(), [](int i){return i%2!=0;});	//it ptr the last element after the last element of the resulting sequence.

	cout << "val:" <<  (*(--it)) << endl;
	cout << "distance:" << std::distance(v22.begin(), it) << endl;
	v22.resize(std::distance(v22.begin(), it));
	for (auto i : v22) {
		cout << i << " ";
	}
	cout << endl;

	vector<int> v3(4);
	std::iota(v3.begin(), v3.end(), 1);
	for (int n : v3) {
		cout << n << " ";
	}
	cout << endl;

	std::array<int, 4> array1;
	std::iota(array1.begin(), array1.end(), 1);
	for (int n : array1) {
		cout << n << " ";
	}
	cout << endl;

	vector<int> v4 = {1,2,5,7,9,4};
	auto res4 = minmax_element(v4.begin(), v4.end());
	cout << *res4.first << " " << *res4.second << endl;

	auto pos = is_sorted_until(v4.begin(), v4.end());
	for (auto it = v4.begin(); it != pos; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	bool is_sort = is_sorted(v4.begin(), v4.end());
	cout << is_sort << endl;

	return 0;
}
