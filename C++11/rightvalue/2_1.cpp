#include <type_traits>
#include <typeinfo>
#include <string>
#include <iostream>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#include <memory>
#include <string>
#include <cstdlib>

using namespace std;

template <class T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own
		(
#ifndef __GNUC__
		 nullptr,
#else
		 abi::__cxa_demangle(typeid(TR).name(),nullptr,nullptr,nullptr),
#endif
		 std::free	//void free( void* ptr );
		 );
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if(std::is_const<TR>::value)
		r += "const";
	if(std::is_volatile<TR>::value)
		r += "volatile";
	if(std::is_lvalue_reference<T>::value)
		r += "&";
	else if(std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}

template<typename T>
void Func(T&& t)
{
	cout<<type_name<T>()<<endl;
}

template<typename T>
void Func1(T t)
{
	cout<<type_name<T>()<<endl;
}

void TestReference()
{
	string str="test";
	const string str1="test";
	Func(str);
	Func(std::move(str));
	cout<<"=============="<<endl;
	Func1(str1);
}

int main(int argc,char* argv[],char* envp[])
{
	char* chartmp="sddf";
	std::string tmp=chartmp;
	std::string tmp1="ddddd";
	cout<<tmp<<endl;
	cout<<tmp1<<endl;
	TestReference();
	return 0;
}





