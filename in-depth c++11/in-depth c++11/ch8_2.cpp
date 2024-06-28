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

class Observer {
public:
	virtual ~Observer();
	virtual void Update(Subject* theChangedSubject) = 0;
protected:
	Observer();
};
class ConcreteObserver : public Observer {
	void Update(Subject* theChangedSubject) {

	}
};

class Subject {
public:
	virtual ~Subject();
	virtual void Attach(Observer* o) {
		_observers->push_back(o);
	}
	virtual void Detach(Observer* o) {
		_observers->remove(o);
	}
	virtual void Notify() {
		for (auto i = _observers->begin(); i != _observers->end(); i++) {
			i->Update(this);
		}
	}
protected:
	Subject();
private:
	std::list<Observer*> *_observers;//observers list
};
class ConcreteSubject : public Subject {
private:
	int val = 0;
};



int main(int argc, const char * argv[]) {
	string str = "bb";


	return 0;
}
