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
//alignas(int) long long a1 = 0; //alignas can't be less than default val

#pragma pack(push) //±£´æ¶ÔÆë×´Ì¬
#pragma pack(1)
long long a1 = 0;
#pragma pack(pop)//»Ö¸´¶ÔÆë×´Ì¬

alignas(int) char c = 0;

#define XX 1
struct alignas(XX)MyStruct_1 {};

template <size_t YY = 1>
struct alignas(YY)MyStruct_2 {};

static const unsigned ZZ = 1;//compile phase value
struct alignas(ZZ)MyStruct_3 {};


struct MyStruct {
	char a;
	int b;
	double c;
};

struct A {
	int avg;
	A(int a, int b): avg((a+b)/2) {}
};

//templaet<size_t len, size_ align>
//struct aligned_storage;
typedef std::aligned_storage<sizeof(A), alignof(A)>::type Aligned_A;

int main(int argc, const char * argv[]) {
	MyStruct_1 struct1;
	MyStruct_2<4> struct2;
	//MyStruct_2<5> struct2;	//err, alignment must be power of two
	MyStruct_3 struct3;

	//cout << alignof(struct1) << endl; //compile err
	cout << alignof(MyStruct_1) << endl;
	cout << alignof(MyStruct_2<4>) << endl;
	cout << alignof(MyStruct_3) << endl;
	cout << "<<<<<" << endl;

	int alignsize = alignment_of<MyStruct>::value;//compile phase integral_constant
	int sz = alignof(MyStruct);
	cout << alignsize << endl;
	cout << sz << endl;

	Aligned_A a, b;
	new (&a) A(10, 20);
	b = a;
	cout << reinterpret_cast<A&>(b).avg << endl;

	return 0;
}
