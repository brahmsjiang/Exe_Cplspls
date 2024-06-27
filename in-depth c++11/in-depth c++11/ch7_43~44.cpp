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

#pragma pack(push) //�������״̬
#pragma pack(1)
long long a1 = 0;
#pragma pack(pop)//�ָ�����״̬

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

inline void* aligned_malloc(size_t size, size_t alignment)
{
	assert(!(alignment & (alignment - 1)));
	size_t offset = sizeof(void*) + (--alignment);
	cout << "sizeof(void*): " << sizeof(void*) << endl;

	char* reqBlockAddr = static_cast<char*>(malloc(offset + size));
	if (!reqBlockAddr) return nullptr;

	void* alignedAddr = reinterpret_cast<void*>(reinterpret_cast<size_t>(reqBlockAddr + offset) & (~alignment));
	cout << "alignedAddr: " << alignedAddr << endl;
	auto reqBlockAddrAddr = (void**)((size_t)alignedAddr - sizeof(void*));
	cout << "reqBlockAddrAddr: " << reqBlockAddrAddr << endl;

	*reqBlockAddrAddr = reqBlockAddr;
	cout << "reqBlockAddr: " << *reqBlockAddrAddr << endl;

	auto ori = static_cast<void**>(alignedAddr)[-1]; //ori == reqBlockAddr
	cout << "ori: " << ori << endl;

	return alignedAddr;
}

inline void aligned_free(void* p)
{
	free(static_cast<void**>(p)[-1]);
}

struct alignas(32) MyStruct_4
{
	char a;
	int b;
	short c;
	long long d;
	char e;
};

void* p1 = new MyStruct_4;
void* p2 = aligned_malloc(sizeof(MyStruct_4), 32);

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

	cout << "<<<<<" << endl;
	cout << typeid(std::max_align_t).name() << ":" << alignof(std::max_align_t) << endl;	//max_align_t is a type
	char buffer[] = "---------------------------";
	void* pt = buffer;
	size_t space = sizeof(buffer) - 1;
	std::align(alignof(int), sizeof(char), pt, space);


	return 0;
}
