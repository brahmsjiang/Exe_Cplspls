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
///////////////////////////////////////
#define HAS_MEMBER(member)\
typename<typename T, typename... Args>\
struct has_member_##member\
{\
private:\
	template<typename U>\
	static auto Check(int) -> decltype(std::declval<U>().member(std::declval<Args>()...), std::true_type());\
	template<typename U>\
	static std::false_type Check(int);\
public:\
	enum { value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;\
};
HAS_MEMBER(Foo)
HAS_MEMBER(Before)
HAS_MEMBER(After)




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
	std::function<void(int)> f = std::bind(&HT, std::placeholders::_1);

}


int main(int argc, const char * argv[]) {
	TestProxy();
	cout << "/////////////////////" << endl;

	return 0;
}
