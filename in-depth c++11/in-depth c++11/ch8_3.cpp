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
struct ConcreteVisitor : public Visitor
{
	void Visit(ConcreteElement1* element) {
		cout << "Visit ConcreteElement1" << endl;
	}
	void Visit(ConcreteElement2* element) {
		cout << "Visit ConcreteElement2" << endl;
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
	ConcreteVisitor v;
	std::unique_ptr<Element> emt1(new ConcreteElement1());
	std::unique_ptr<Element> emt2(new ConcreteElement2());
	emt1->Accept(v);
	emt2->Accept(v);
}



int main(int argc, const char * argv[]) {
	TestVisitor();

	return 0;
}
