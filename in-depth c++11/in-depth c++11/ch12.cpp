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
	template<size_t I>
	struct args {
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

////member func
#define FUNCTION_TRAITS(...) \
template <typename RetType, typename ClsType, typename... Args> \
struct function_traits<RetType(ClsType::*)(Args...) __VA_ARGS__> : function_traits<RetType(Args...)> {};

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

////func obj
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(const Function& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(Function&& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda) {
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}

void test0() {
	auto f = to_funcion([](int i){return i;});
	std::function<int(int)> f1 = [](int i){return i;};
	if (std::is_same<decltype(f), decltype(f1)>::value)
		cout << "same" << endl;
}

int main(int argc, const char * argv[]) {
	test0();
	cout << "/////////////////////" << endl;
	cout << "/////////////////////" << endl;
	cout << "/////////////////////" << endl;

	cout << "/////////////////////" << endl;

	return 0;
}
