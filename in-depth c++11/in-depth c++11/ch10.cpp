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
		cout << "Invoke(Args&&... args, T&& aspect), Before & After" << endl;
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}
	template<typename T>
	typename std::enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
	{
		cout << "Invoke(Args&&... args, T&& aspect), Before" << endl;
		aspect.Before(std::forward<Args>(args)...);
		m_func(std::forward<Args>(args)...);
	}
	template<typename T>
	typename std::enable_if<!has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
	{
		cout << "Invoke(Args&&... args, T&& aspect), After" << endl;
		m_func(std::forward<Args>(args)...);
		aspect.After(std::forward<Args>(args)...);
	}
	template<typename Head, typename... Tail>
	void Invoke(Args&&... args, Head&& headAspect, Tail&&... tailAspect)
	{
		cout << "Invoke(Args&&... args, Head&& headAspect, Tail&&... tailAspect)" << endl;
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
	asp.Invoke(std::forward<Args>(args)..., AP()...); //identity_t<AP>()...
}

struct AA {
	void Before(int i) {
		cout << "Before from AA," << i << endl;
	}
	void After(int i) {
		cout << "After from AA," << i << endl;
	}
};
struct BB {
	void Before(int i) {
		cout << "Before from BB," << i << endl;
	}
	void After(int i) {
		cout << "After from BB," << i << endl;
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
	cout << "**............1st 1st" << endl;
	Invoke<AA, BB>(f, 1);
	cout << "**............1st 2nd" << endl;
	Invoke<CC, DD>(&GT);
	cout << "**............2nd 1st" << endl;
	Invoke<AA, BB>(&HT, 1);
	cout << "**............2nd 2nd" << endl;
	Invoke<AA, BB>([](int i){}, 1);
	cout << "**............3rd 1st" << endl;
	Invoke<CC, DD>([]{});
	cout << "**............3rd 2nd" << endl;
}

HAS_MEMBER(Foo)

struct TimeElapsedAspect
{
	void Before(int i) {
		lastTime = std::chrono::steady_clock::now();
	}
	void After(int i) {
		std::chrono::steady_clock::time_point nowTime = std::chrono::steady_clock::now();
		cout << "time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(nowTime - lastTime).count() << "[us]" << endl;
		lastTime = nowTime;
	}
private:
	std::chrono::steady_clock::time_point lastTime;
};
struct LoggingAspect
{
	void Before(int i) {
		cout << "entering..." << std::endl;
	}
	void After(int i) {
		cout << "leaving..." << std::endl;
	}
};
void Foo(int a) {
	cout << "real HT function: " << a << endl;
}
void TestLoggingAop()
{
	Invoke<LoggingAspect, TimeElapsedAspect>(&Foo, 1);
	cout << "**................." << endl;
	Invoke<TimeElapsedAspect, LoggingAspect>(&Foo, 1);
}

template<typename T>
struct tstCompil
{
	static std::true_type tstCompileRetFunc();
};

int main(int argc, const char * argv[]) {
	cout << decltype(tstCompil<int>::tstCompileRetFunc())::value << endl;
	cout << "/////////////////////" << endl;
	TestProxy();
	cout << "/////////////////////" << endl;
	TestAop();
	cout << "/////////////////////" << endl;
	TestLoggingAop();

	return 0;
}
