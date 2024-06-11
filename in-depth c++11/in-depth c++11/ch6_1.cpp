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

using namespace std;


template <typename T>
class testInner
{};

template <typename T, typename U>
class testTemp
{};


int main(int argc, const char * argv[]) {
	
	std::chrono::milliseconds ms{3};
	std::chrono::microseconds us = ms;
	cout << "3 ms has: " << ms.count() << " ticks\n" << "3000 us has: " << us.count() << " ticks\n";

	testTemp<int, char> temp1;
	testTemp<int, float> temp2;
	//temp1 = temp2;	//compile err




	return 0;
}
