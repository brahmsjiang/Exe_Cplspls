#include <iostream>
#include <memory>	//allocator
#include <map>
#include <string>
#include <list>

using namespace std;
using UPtrMapSS = unique_ptr<map<string, string>>;

class Widget1;
class Wine;
//template forward declaration
template<typename T>
class Widget2;
template<typename T>
class Widget3;
template<typename T>
class MyAllocList3;

typedef void(*FP)(int, const string&);
using FP = void(*)(int, const string&);

template<typename T>
using MyAllocList1 = list<T, allocator<T>>;

//template<typename T>	//typedef template - invalid
//typedef list<T, allocator<T>> type;
template<typename T>
struct MyAllocList2
{
	typedef list<T, allocator<T>> type;
};

class Widget1
{};

template<typename T>
class Widget2
{
	typename MyAllocList2<T>::type lw;//its type contained depends on template parameter, must add 'typename'
};

template<typename T>
class Widget3
{
	MyAllocList1<T> lw1;//MyAllocList1 is already recognized as a type by compiler, no need to add 'typename'
};

//template specialization
template<typename T>
class MyAllocList3
{
};

class Wine{};
template<>
class MyAllocList3<Wine>
{
public:
	enum class WineType
	{White, Red, Rose};

	WineType type;
};


int main(int argc, char* argv[])
{
	MyAllocList1<Widget1> lw1;
	MyAllocList2<Widget1>::type lw2;

	Widget3<int> wd;

	return 0;
}