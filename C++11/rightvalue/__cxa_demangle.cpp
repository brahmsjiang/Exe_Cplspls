#include <iostream>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif

using namespace std;

class Foo{};

int main()
{
//	class Foo{};
	cout<<typeid(Foo*[10]).name()<<endl;

	char* name=abi::__cxa_demangle(typeid(Foo*[10]).name(),nullptr,nullptr,nullptr);
	cout<<name<<endl;
	free(name);

	return 0;
}
