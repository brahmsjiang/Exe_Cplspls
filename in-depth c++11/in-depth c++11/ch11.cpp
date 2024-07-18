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

struct Base
{
	virtual void Func(){}
	virtual ~Base(){}
};
struct DerivedB : Base
{
	void Func() override { cout << "call func in DerivedB" << endl; }
};
struct DerivedC : Base
{
	void Func() override { cout << "call func in DerivedC" << endl; }
};
struct DerivedD : Base
{
	void Func() override { cout << "call func in DerivedD" << endl; }
};
class A
{
public:
	A(Base* interface) : m_interface(interface) {}
	void Func() { m_interface->Func(); }
	~A() {
		if (m_interface != nullptr) {
			delete m_interface;
			m_interface = nullptr;
		}
	}
private:
	Base* m_interface;
};
void TestOld0() {
	A* a = new A(new DerivedB());
	a->Func();
	delete a;
}
void TestOld1(int sel) {
	A* a = nullptr;
	if (sel == 0)
		a = new A(new DerivedB());
	else if (sel == 1)
		a = new A(new DerivedC());
	else if (sel == 2)
		a = new A(new DerivedD());
	a->Func();
	delete a;
}

struct Factory
{
	static Base* Create(const string& condition) {
		if (condition == "B")
			return new DerivedB();
		else if (condition == "C")
			return new DerivedC();
		else if (condition == "D")
			return new DerivedD();
		else
			return nullptr;
	}
};
void TestOld2() {
	string temp = "C";
	A* a = new A(Factory::Create(temp));
	a->Func();
	delete a;
}

int main(int argc, const char * argv[]) {
	TestOld0();
	cout << "/////////////////////" << endl;
	TestOld1(2);
	cout << "/////////////////////" << endl;
	TestOld2();
	cout << "/////////////////////" << endl;

	return 0;
}
