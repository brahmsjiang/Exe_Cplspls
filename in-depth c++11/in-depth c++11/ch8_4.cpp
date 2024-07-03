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

using namespace std;

class Command {
public:
	virtual void Execute() = 0;
};

template<class Receiver>
class SimpleCommand : public Command {
public:
	typedef void(Receiver::* Action)();
	SimpleCommand(Receiver* r, Action a) : _receiver(r), _action(a) {}
	virtual void Execute() {
		(_receiver->*_action)();
	}
private:
	Action _action;
	Receiver* _receiver;
};
///////
class MyClass {
public:
	void Action() {cout << "MyClass::Action" << endl;}	
};
void dummy() {
	MyClass* receiver = new MyClass;
	Command* aCommand = new SimpleCommand<MyClass>(receiver, &MyClass::Action);
	aCommand->Execute();
}
/////////////////////
template<typename R=void>
struct CommCommand {
private:
	std::function<R()> m_f;
public:
	template<class F, class... Args, class = typename enable_if<!is_member_function_pointer<F>::value>::type>
	void Wrap(F&& f, Args&&... args) {
		m_f = [&]{ return f(args...); };
	}
	template<class R, class C, class... DArgs, class P, class... Args>
	void Wrap(R(C::*f)(DArgs...) const, P&& p, Args&&... args) {
		m_f = [&, f]{ return (*p.*f)(args...); };
	}
	template<class R, class C, class... DArgs, class P, class... Args>
	void Wrap(R(C::*f)(DArgs...), P&& p, Args&&... args) {
		m_f = [&, f]{ return (*p.*f)(args...); };
	}
	R Execute() {
		return m_f();
	}
};

struct stA {
	int m_a;
	int operator()(){return m_a;}
	int operator()(int n){return m_a + n;}
	int triple0(){return m_a * 3;}
	int triple(int a){return m_a * 3 + a;}
	int triple1() const {return m_a * 3;}
	const int triple2(int a) const {return m_a * 3 + a;}
	void triple3() {cout << "" << endl;}
};

int add_one(int n) {
	return n + 1;
}
void TestWrap() {
	CommCommand<int> cmd;
	cmd.Wrap(add_one, 0);
	cmd.Wrap([](int n) {return n + 1; }, 1);
	stA bloop;
	cmd.Wrap(bloop);
	cmd.Wrap(bloop, 4);
	stA t = { 10 };
	int x = 3;
	cmd.Wrap(&stA::triple0, &t);
	cmd.Wrap(&stA::triple, &t, x);
	cmd.Wrap(&stA::triple, &t, 3);
	cmd.Wrap(&stA::triple2, &t, 3);
	auto r = cmd.Execute();
	CommCommand<> cmd1;
	cmd1.Wrap(&stA::triple3, &t);
	cmd1.Execute();
}


int main(int argc, const char * argv[]) {

	dummy();
	cout << "/////////////////////" << endl;
	TestWrap();

	return 0;
}
