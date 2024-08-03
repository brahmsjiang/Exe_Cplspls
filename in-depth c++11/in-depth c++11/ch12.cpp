#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <list>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <map>
#include <unordered_map>
#include <thread>
#include <typeinfo>
#include <typeindex>
#include "../../Utilties/Any.hpp"
#include "../../Utilties/NonCopyable.hpp"

using namespace std;

template <typename T>
struct function_traits;

////normal func
template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
public:
	enum { arity = sizeof...(Args) };
	using function_type = Ret(Args...);
	using return_type = Ret;
	using stl_function_type = std::function<function_type>;
	using pointer = Ret(*)(Args...);

	template<size_t I>
	struct args {	//to access the type of the Ith element in a tuple.
		static_assert(I < arity, "index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
	};
};

////func ptr
template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};

////std::function
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};

/*
  __VA_ARGS__: variadic macro
  __VA_ARGS__ refers back again to the variable arguments in the macro itself
  #define DEBUG(...)  printString (__VA_ARGS__)
  DEBUG("foo", "bar", "baz"); would be replaced with printString ("foo", "bar", "baz")
*/

////member func
#define FUNCTION_TRAITS(...) \
template <typename Ret, typename ClsType, typename... Args> \
struct function_traits<Ret(ClsType::*)(Args...) __VA_ARGS__> : function_traits<Ret(Args...)> {};
FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

////func obj
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};
//////////////
template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(const Function& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(Function&& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));//perfect forward
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda) {
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}
//////////////

template <typename Ret, typename... Args>
struct templete_using
{
	using signature = Ret(Args...);
	static int staticFunc() { return 1; }
	int operator()() { return 1; }
	int normFunc() { return 1; }
	int value = 3;
};

/////////
struct clsWithFunc
{
	void func() {cout << "clsWithFunc::func" << endl;}
};
struct lambdaSaver
{
	std::function<void()> mf;
	void wrap(void(clsWithFunc::*f)(), clsWithFunc* obj) {
		mf = [obj1=obj, f1=f]{return (*obj1.*f1)();};
	}
	void wrap1(void(clsWithFunc::*f)(), clsWithFunc* obj) {
		mf = [&]{return (*obj.*f)();};
	}
	void execute() {
		return mf();
	}
};
void voidFunc() {cout << "voidFunc" << endl;}
void testLambdaByRef() {
	lambdaSaver obj1;
	clsWithFunc funcObj;
	//obj1.wrap(&clsWithFunc::func, &funcObj);
	//obj1.execute();
	obj1.wrap(&clsWithFunc::func, &funcObj);
	obj1.execute();
}
/////////

void testUsing() {
	using namespace std;
	using specificTemplete = templete_using<void, int, string>;
	using funcWithSig = function<specificTemplete::signature>;
	funcWithSig obj = [](int num, string str){ cout << str << to_string(num) << endl; };
	obj(1, "shit");
	using anotherSig = void(int, string);
	function<anotherSig> obj2 = [](int num, string str){ cout << str << to_string(num) << endl; };
	obj(2, "fuck");
	decltype(specificTemplete::staticFunc()) whoami0;
	decltype(declval<specificTemplete>().normFunc()) whoami1;
	decltype(&specificTemplete::normFunc) whoami2; cout << typeid(whoami2).name() << endl;
	decltype(declval<specificTemplete>().operator()()) whoami4; cout << typeid(whoami4).name() << endl;
	decltype(&specificTemplete::operator()) whoami3; cout << typeid(whoami3).name() << endl;
	cout << &specificTemplete::value << endl;
	cout << specificTemplete::staticFunc << endl;
}

void test0() {
	auto f = to_funcion([](int i){return i;});
	std::function<int(int)> f1 = [](int i){return i;};
	if (std::is_same<decltype(f), decltype(f1)>::value)
		cout << "same" << endl;
	auto pp = to_function_pointer([](int i){return i;});
	cout << pp(12) << endl; // (*pp)(12) is the same
}

int main(int argc, const char * argv[]) {
	testLambdaByRef();
	cout << "/////////////////////" << endl;
	testUsing();
	cout << "/////////////////////" << endl;
	test0();
	cout << "/////////////////////" << endl;

	cout << "/////////////////////" << endl;

	return 0;
}
