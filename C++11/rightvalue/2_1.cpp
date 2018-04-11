#include <type_traits>
#include <typeinfo>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#include <memory>
#include <string>
#include <cstdlib>

template <class T>
std::string type_name()
{
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)>
		(
#ifndef __GNUC__
		 nullptr,
#else
		 abi::__cxa_demangle(typeid(TR).name(),nullptr,nullptr,nullptr),
#endif
		 std::free
		 );
}



int main(int argc,char* argv[],char* envp[])
{
	return 0;
}
