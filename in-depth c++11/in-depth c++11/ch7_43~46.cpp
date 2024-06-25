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

using namespace std;


alignas(32) long long a = 0;
//alignas(1) long long a1 = 0;	//alignas can't be less than default val

#define XX 1
struct alignas(XX)MyStruct_1 {};

template <size_t YY = 1>
struct alignas(YY)MyStruct_2 {};

static const unsigned ZZ = 1;//compile phase value
struct alignas(ZZ)MyStruct_3 {};


int main(int argc, const char * argv[]) {
	MyStruct_1 struct1;
	MyStruct_2<4> struct2;
	//MyStruct_2<5> struct2;	//err, alignment must be power of two
	MyStruct_3 struct3;

	return 0;
}
