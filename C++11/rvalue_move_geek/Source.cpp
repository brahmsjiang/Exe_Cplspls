#include "smart_ptr.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class shape
{
public:
	virtual void func() {
		cout << "shape::cout" << endl;
	}
};
class circle : public shape
{
public:
	void func() {
		cout << "circle::cout" << endl;
	}
};

int main(int argc, char* argv[])
{
	//lvalue could be get addr
	auto x = 2;
	auto add1 = &(++x);
	auto add2 = &(x = 1);
	auto add3 = &(cout << ' ');
	auto add4 = &("helloworld");
	
	//lvalue could be bind to T& or const T&
	const auto constval = 1;
	const int& ref1 = constval;
	//int& ref2 = constval;//err
	int& ref3 = x;
	const int& ref4 = x;
	
	//pure rvalue can't be get addr
	//such as expression's return isn't ref 
	//auto add5 = &(x++);
	//auto add6 = &(x+1);
	auto add7 = &(make_shared<int>(42));//?can be addr
	//auto add8 = &true;

	//int& a = 1;//err
	const int& a = 1;//rvalue can only bind to const T&
	int&& a1 = 1;
	const int&& a2 = 1;
	volatile int&& a3 = 1;

	smart_ptr<shape> ptr1{ new circle() };
	smart_ptr<shape> ptr4 = ptr1;
	smart_ptr<shape> ptr2 = std::move(ptr1);
	smart_ptr<shape> ptr3 = static_cast<smart_ptr<shape>&&>(ptr1);
	smart_ptr<shape> ptr5 = ptr1;
	if (ptr1.get())
	{
		ptr1->func();
	}
}

