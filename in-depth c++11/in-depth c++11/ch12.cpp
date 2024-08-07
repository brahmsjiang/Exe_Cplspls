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
struct function_traits : function_traits<decltype(&Callable::operator())> {};//Callable::operator() is not a func call, just a mem-func

////////////
template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(const Function& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(lambda);
	//Function<==>Ret(Args...),Ret(Args...) standsfor all funcs
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_funcion(Function&& lambda) {
	return static_cast<function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));//perfect forward
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda) {
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}
////////////
class MessageBus: NonCopyable
{
public:
	//register msg
	template<typename F>
	void Attach(F&& f, const string& strTopic = "") {
		auto func = to_funcion(std::forward<F>(f));
		Add(strTopic, std::move(func));
	}
	//send msg
	template<typename R>
	void SendReq(const string& strTopic = "") {
		using function_type = std::function<R()>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		//ret val: pair(the range you wanted)
		//auto range = map.equal_range(1);
		//for (auto it = range.first; it != range.second; ++it)
		//    std::cout << it->first << ' ' << it->second << '\n';
		// it->first --> key, it->second --> value
		for (Iterator it = range.first; it != range.second; ++it) {
			auto f = it->second.AnyCast<function_type>();
			f();
		}
	}
	template<typename R, typename... Args>
	void SendReq(Args&&... args, const string& strTopic = "") {
		using function_type = std::function<R(Args...)>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		for (Iterator it = range.first; it != range.second; ++it) {
			auto f = it->second.AnyCast<function_type>();
			f(std::forward<Args>(args)...);
		}
	}
	//unregister msg
	template<typename R, typename... Args>
	void Remove(const string& strTopic = "") {
		using function_type = std::function<R(Args...)>;
		string strMsgType = strTopic + typeid(function_type).name();
		auto range = m_map.equal_range(strMsgType);
		m_map.erase(range.first, range.second);
	}
private:
	template<typename F>
	void Add(const string& strTopic, F&& f) {
		string strMsgType = strTopic + typeid(F).name();
		m_map.emplace(std::move(strMsgType), std::forward<F>(f));
	}
private:
	std::multimap<string, Any> m_map;
	using Iterator = std::multimap<string, Any>::iterator;
};
//End standard code

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
		mf = [=]{return (*obj.*f)();};
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

/////////
MessageBus g_bus;
const string Topic = "Drive";
const string CallBackTopic = "DriveOk";
struct Subject
{	
	Subject() {
		g_bus.Attach([this]{DriveOk();}, CallBackTopic);
	}
	void SendReq(const string& topic) {
		g_bus.SendReq<void, int>(50, topic);
	}
	void DriveOk() {
		cout << "drive ok" << endl;
	}
};
struct Car
{
	Car() {
		g_bus.Attach([this](int speed){Drive(speed);}, Topic);
	}
	void Drive(int speed) {
		cout << "Car drive " << speed << endl;
		g_bus.SendReq<void>(CallBackTopic);
	}
};
struct Bus
{
	Bus() {
		g_bus.Attach([this](int speed){Drive(speed);});
	}
	void Drive(int speed) {
		cout << "Bus drive " << speed << endl;
		g_bus.SendReq<void>(CallBackTopic);
	}
};
struct Trunk
{
	Trunk() {
		g_bus.Attach([this](int speed){Drive(speed);});
	}
	void Drive(int speed) {
		cout << "Trunk drive " << speed << endl;
		g_bus.SendReq<void>(CallBackTopic);
	}
};
void TestBus() {
	Subject subject;
	Car car;
	Bus bus;
	Trunk trunk;
	subject.SendReq(Topic);
	cout << "--------" << endl;
	subject.SendReq("");
	cout << "--------" << endl;
	g_bus.Remove<void, int>(Topic);
	subject.SendReq(Topic);
	cout << "--------" << endl;
	subject.SendReq("");
}

void testMsgBus() {
	MessageBus bus;
	bus.Attach([](int a){cout << "no reference " << a << endl;});
	bus.Attach([](int&& a){cout << "rvalue reference " << a << endl;});
	bus.Attach([](const int& a){cout << "const lvalue reference " << a << endl;});
	bus.Attach([](int a){cout << "no reference has return value " << a << endl; return a;}, "a");

	int i = 2;
	bus.SendReq<void, int>(2);
	bus.SendReq<int, int>(2, "a");
	bus.SendReq<void, int&>(i);
	bus.SendReq<void, const int&>(2);
	bus.SendReq<void, int&&>(2);

	bus.Remove<void, int>();
	bus.Remove<int, int>("a");
	bus.Remove<void, int&>();
	bus.Remove<void, const int&>();
	bus.Remove<void, int&&>();

	bus.SendReq<void, int>(2);
	bus.SendReq<int, int>(2, "a");
	bus.SendReq<void, int&>(i);
	bus.SendReq<void, const int&>(2);
	bus.SendReq<void, int&&>(2);
}
/////////

int main(int argc, const char * argv[]) {
	testLambdaByRef();
	cout << "/////////////////////" << endl;
	testUsing();
	cout << "/////////////////////" << endl;
	test0();
	cout << "/////////////////////" << endl;
	testMsgBus();
	cout << "/////////////////////" << endl;
	TestBus();

	return 0;
}


/*
void Show(int i) {
	Console.WriteLine("Show {0}", i);
}
void ShowCode(int code) {
	Console.WriteLine("ShowCode {0}", code);
}
public delegate void ShowHandler(int param);	//declear delegate
public event ShowHandler ShowEvent;				//declear event
ShowEvent += Show;								//register func
ShowEvent += ShowCode;							//register func
ShowEvent(2);									//broadcast

public delegate void ShowMsgHandler(int param);	//declear delegate
public event ShowMsgHandler ShowMsgEvent;		//declear event
*/