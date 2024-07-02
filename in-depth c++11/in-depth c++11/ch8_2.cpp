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

class Subject;
class ConcreteSubject;

class Observer {
public:
	virtual ~Observer() {};
	virtual void Update() = 0;
protected:
	Observer() {};
};
class Subject {
public:
	virtual ~Subject() {};
	virtual void Attach(Observer* o) {
		_observers.push_back(o);
	}
	virtual void Detach(Observer* o) {
		_observers.remove(o);
	}
	virtual void Notify() {
		for (auto i = _observers.begin(); i != _observers.end(); i++) {
			if (*i != nullptr) {
				(*i)->Update();
			}
			
		}
	}
protected:
	Subject() {};
private:
	std::list<Observer*> _observers;//observers list
};
//////////////////
class ConcreteSubject : public Subject {
public:
	ConcreteSubject() {}
	~ConcreteSubject() {}
	int getVal() {
		return val;
	}
private:
	int val = 2;
};
class ConcreteObserver : public Observer {
public:
	ConcreteObserver() {};
	~ConcreteObserver() {};
	void setConcreteSubject(ConcreteSubject* subject) {pSubject = subject;}
	void Update() {
		if (pSubject != nullptr)
			cout << "val is: " << pSubject->getVal() << endl;
	}
private:
	ConcreteSubject* pSubject;
};
////////////////////////////////////
class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

template<typename Func>		//Func<===>observer, parameters of Func<===>data changed
class Events: NonCopyable	//Events<===>subject
{
public:
	Events() {}
	~Events() {}
	int Connect(Func&& f) {
		return Assign(f);
	}
	int Connect(const Func& f) {
		return Assign(f);
	}
	void Disconnect(int key) {
		m_connections.erase(key);
	}
	template<typename...Args>
	void Notify(Args&&... args) {
		for (auto& it : m_connections) {
			cout << "traverse, cur k: " << it.first << endl;
			it.second(std::forward<Args>(args)...);
		}
	}
	void Size() {
		cout << "size: " << m_connections.size() << endl;
	}
private:
	template<typename F>
	int Assign(F&& f) {
		int k = m_observerId++;
		m_connections.emplace(k, std::forward<F>(f));
		cout << "assign, new k: " << k << endl;
		return k;
	}
private:
	int m_observerId = 0;
	std::map<int, Func> m_connections;
};

struct stA
{
	int a, b;
	void print() {cout << a << "," << b << endl;}
	void print(int a, int b) {cout << a << "," << b << endl;}
};
void print(int a, int b) {cout << a << "," << b << endl;}


int main(int argc, const char * argv[]) {
	ConcreteSubject subject;
	ConcreteObserver observer1; observer1.setConcreteSubject(&subject);
	ConcreteObserver observer2; observer2.setConcreteSubject(&subject);
	ConcreteObserver observer3; observer3.setConcreteSubject(&subject);
	subject.Attach(&observer1);
	subject.Attach(&observer2);
	subject.Attach(&observer3);
	subject.Notify();
	cout << "/////////////////////////" << endl;
	Events<std::function<void(int, int)>> myevent;

	auto key = myevent.Connect(print);

	stA t;
	auto lambdakey = myevent.Connect([&t](int a, int b){t.a=a; t.b=b; t.print();});

	std::function<void(int, int)> f = std::bind((void(stA::*)(int,int))&stA::print, &t, std::placeholders::_1, std::placeholders::_2);
	auto bindkey = myevent.Connect(f);

	int a = 1,b = 2;
	myevent.Notify(a, b);

	myevent.Size();
	myevent.Disconnect(key);
	myevent.Disconnect(lambdakey);
	myevent.Disconnect(bindkey);
	myevent.Size();

	return 0;
}
