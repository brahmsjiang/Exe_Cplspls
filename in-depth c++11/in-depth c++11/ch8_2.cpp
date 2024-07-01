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
		else
			cout << "mSubject is nullptr" << endl;
	}
private:
	ConcreteSubject* pSubject;
};
///////

int main(int argc, const char * argv[]) {
	ConcreteSubject subject;
	ConcreteObserver observer1; observer1.setConcreteSubject(&subject);
	ConcreteObserver observer2; observer2.setConcreteSubject(&subject);
	ConcreteObserver observer3; observer3.setConcreteSubject(&subject);
	subject.Attach(&observer1);
	subject.Attach(&observer2);
	subject.Attach(&observer3);
	subject.Notify();

	return 0;
}
