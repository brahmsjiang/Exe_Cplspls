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

struct ConcreteElement1;
struct ConcreteElement2;

struct Visitor
{
	virtual ~Visitor() {}
	virtual void Visit(ConcreteElement1* element) = 0;
	virtual void Visit(ConcreteElement2* element) = 0;
};
struct Element
{
	virtual ~Element() {}
	virtual void Accept(Visitor& visitor) = 0;
};
//////////////////
struct ConcreteVisitor1 : public Visitor
{
	void Visit(ConcreteElement1* element) {
		cout << "ConcreteVisitor1 visit ConcreteElement1" << endl;
	}
	void Visit(ConcreteElement2* element) {
		cout << "ConcreteVisitor1 visit ConcreteElement2" << endl;
	}
};
struct ConcreteVisitor2 : public Visitor
{
	void Visit(ConcreteElement1* element) {
		cout << "ConcreteVisitor2 visit ConcreteElement1" << endl;
	}
	void Visit(ConcreteElement2* element) {
		cout << "ConcreteVisitor2 visit ConcreteElement2" << endl;
	}
};
struct ConcreteElement1 : public Element
{
	void Accept(Visitor& visitor) {
		visitor.Visit(this);
	}
};
struct ConcreteElement2 : public Element
{
	void Accept(Visitor& visitor) {
		visitor.Visit(this);
	}
};

void TestVisitor() {
	ConcreteVisitor1 v1;
	ConcreteVisitor2 v2;
	std::unique_ptr<Element> emt1(new ConcreteElement1());
	std::unique_ptr<Element> emt2(new ConcreteElement2());
	emt1->Accept(v1);
	emt2->Accept(v1);
	emt1->Accept(v2);
	emt2->Accept(v2);
}
////////////////////////////////////
template<typename... Types>
struct Visitor1;
template<typename T, typename... Types>
struct Visitor1<T, Types...> : Visitor1<Types...>
{
	using Visitor1<Types...>::Visit;
	virtual void Visit(const T&) = 0;
};
template<typename T>
struct Visitor1<T>
{
	virtual void Visit(const T&) = 0;
};
//////////////////
struct stA;
struct stB;
struct Base
{
	typedef Visitor1<stA, stB> MyVisitor;
	virtual void Accept(MyVisitor&) = 0;
};
struct stA: Base
{
	double val;
	void Accept(Base::MyVisitor& v) {
		v.Visit(*this);
	}
};
struct stB: Base
{
	int val;
	void Accept(Base::MyVisitor& v) {
		v.Visit(*this);
	}
};
struct PrintVisitor: Base::MyVisitor
{
	void Visit(const stA& a) {
		cout << "from stA: " << a.val << endl;
	}
	void Visit(const stB& b) {
		cout << "from stB: " << b.val << endl;
	}
};

void TestVisitor1() {
	PrintVisitor vis;
	stA a;
	a.val = 8.97;
	stB b;
	b.val = 8;
	Base* base = &a;
	base->Accept(vis);
	base = &b;
	base->Accept(vis);
}

int main(int argc, const char * argv[]) {
	TestVisitor();
	cout << "///////////////////" << endl;
	TestVisitor1();
	return 0;
}
