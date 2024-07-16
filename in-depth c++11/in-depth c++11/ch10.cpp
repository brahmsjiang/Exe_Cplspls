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
#include <thread>

using namespace std;

class IHello
{
public:
	IHello() {};
	~IHello() {};
	virtual void Output(const string& str) {}
};

class Hello : public IHello
{
public:
	void Output(const string& str) override {
		cout << str << endl;
	}
};

class HelloProxy : public IHello
{
public:
	HelloProxy(IHello* p) : m_ptr(p) {}
	~HelloProxy() {
		delete m_ptr;
		m_ptr = nullptr;
	}
	void Output(const string& str) final {
		cout << "Before real Output" << endl;
		m_ptr->Output(str);
		cout << "After real Output" << endl;
	}
private:
	IHello* m_ptr;
};

void TestProxy() {
	std::shared_ptr<IHello> hello = std::make_shared<HelloProxy>(new Hello());
	hello->Output("It is a test");
}
///////////////////////////////////////
class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};
///////////////////////////////////////
#define HAS_MEMBER(member)\
template<typename T, typename... Args>\
struct has_member_##member\
{\
private:\
	template<typename U> static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type());\
	template<typename U> static std::false_type Check(...);\
public:\
	enum { value = std::is_same<decltype(Check<T>(0)), std::true_type>::value };\
};

HAS_MEMBER(After)
HAS_MEMBER(Before)

template<typename Func, typename... Args>
struct Aspect : NonCopyable
{
public:
	Aspect(Func&& f) : m_func(std::forward<Func>(f)) {}
	template<typename T>
	typename std::enable_if<has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}
	template<typename T>
	typename std::enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
	{
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
	}
	template<typename T>
	typename std::enable_if<!has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
	{
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}
	template<typename Head, typename... Tail>
	void Invoke(Args&&... args, Head&& headAspect, Tail&&... tailAspect)
	{
		headAspect.Before(std::forward<Args>(args)...);
		Invoke(std::forward<Args>(args)..., std::forward<Tail>(tailAspect)...);
		headAspect.After(std::forward<Args>(args)...);
	}
private:
	Func m_func;
};
template<typename T> using identity_t = T;

template<typename... AP, typename... Args, typename Func>
void Invoke(Func&& f, Args&&... args)
{
	Aspect<Func, Args...> asp(std::forward<Func>(f));
	asp.Invoke(std::forward<Args>(args)..., identity_t<AP>()...);
}

struct AA {
	void Before(int i) {
		cout << "Before from AA" << i << endl;
	}
	void After(int i) {
		cout << "After from AA" << i << endl;
	}
};
struct BB {
	void Before(int i) {
		cout << "Before from BB" << i << endl;
	}
	void After(int i) {
		cout << "After from BB" << i << endl;
	}
};
struct CC {
	void Before() {
		cout << "Before from CC" << endl;
	}
	void After() {
		cout << "After from CC" << endl;
	}
};
struct DD {
	void Before() {
		cout << "Before from DD" << endl;
	}
	void After() {
		cout << "After from DD" << endl;
	}
};
void GT() {
	cout << "real GT function" << endl;
}
void HT(int a) {
	cout << "real HT function" << endl;
}
void TestAop()
{
	auto f = std::bind(&HT, std::placeholders::_1);
	Invoke<AA, BB>(std::function<void(int)>(std::bind(&HT, std::placeholders::_1)), 1);
	Invoke<AA, BB>(f, 1);

	Invoke<CC, DD>(&GT);
	Invoke<AA, BB>(&HT, 1);

	Invoke<AA, BB>([](int i){}, 1);
	Invoke<CC, DD>([]{});
}

/*
struct TimeElapsedAspect
{
	void Before(int i) {
		m_lastTime = 
	}
private:
	double m_lastTime;
	Timer m_t;
}
*/

template<typename T>
struct tstCompil
{
	static std::true_type tstCompileRetFunc();
};

template<typename T, typename... Args>
struct has_member_Foo
{
public:
	static std::false_type Check(int);
public:
	enum { value = std::is_same<decltype(Check(0)), std::true_type>::value };
};

int main(int argc, const char * argv[]) {
	cout << decltype(has_member_Foo<int>::Check(0))::value << endl;
	//cout << "tstCompileRetFunc:" << tstCompil<int>::tstCompileRetFunc() << endl;
	cout << "/////////////////////" << endl;
	TestProxy();
	cout << "/////////////////////" << endl;
	TestAop();
	cout << "/////////////////////" << endl;

	return 0;
}
