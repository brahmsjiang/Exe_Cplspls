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
struct ConcreteElement3;	//add

struct Visitor
{
	virtual ~Visitor() {}
	virtual void Visit(ConcreteElement1* element) = 0;
	virtual void Visit(ConcreteElement2* element) = 0;
	virtual void Visit(ConcreteElement3* element) = 0;	//add
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
	void Visit(ConcreteElement3* element) {	//add
		cout << "ConcreteVisitor1 visit ConcreteElement3" << endl;
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
	void Visit(ConcreteElement3* element) {	//add
		cout << "ConcreteVisitor2 visit ConcreteElement3" << endl;
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
struct ConcreteElement3 : public Element	//add
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
	std::unique_ptr<Element> emt3(new ConcreteElement3());	//add
	emt1->Accept(v1);
	emt2->Accept(v1);
	emt3->Accept(v1);	//add
	emt1->Accept(v2);
	emt2->Accept(v2);
	emt3->Accept(v2);	//add
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
struct stC;	//add
struct Base
{
	typedef Visitor1<stA, stB, stC> MyVisitor;	//modify
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
struct stC: Base	//add
{
	string val;
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
	void Visit(const stC& c) {	//add
		cout << "from stC: " << c.val << endl;
	}
};

void TestVisitor1() {
	PrintVisitor vis;
	stA a; a.val = 8.97;
	stB b; b.val = 8;
	stC c; c.val = "strc";	//add
	Base* base = &a; base->Accept(vis);
	base = &b; base->Accept(vis);
	base = &c; base->Accept(vis);	//add
}

int main(int argc, const char * argv[]) {
	TestVisitor();
	cout << "///////////////////" << endl;
	TestVisitor1();
	return 0;
}
