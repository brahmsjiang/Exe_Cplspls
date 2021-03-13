#include "smart_ptr.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <utility> //std::move

using namespace std;

class shape
{
public:
    virtual ~shape() {}
	virtual void func() {
		cout << "shape::cout" << endl;
	}
};

class circle : public shape
{
public:
    circle() { cout << "circle()" << endl; }
    ~circle() { cout << "~circle()" << endl; }
	void func() {
		cout << "circle::cout" << endl;
	}
};

class triangle : public shape
{
public:
    triangle() { cout << "triangle()" << endl; }
    ~triangle() { cout << "~triangle()" << endl; }
    void func() {
        cout << "triangle::cout" << endl;
    }
};

class result
{
public:
    result() { cout << "result()" << endl; }
    ~result() { cout << "~result()" << endl; }
    void func() {
        cout << "result::cout" << endl;
    }
};

result process_shape(const shape& shape1, const shape& shape2)
{
    cout << "process_shape()" << endl;
    return result();
}

class base
{
public:
    ~base()
    {
        cout << "~base()\n";
    }
	void func()
	{
		cout << "base::func()\n";
	}
};

class child : public base
{
public:
    ~child()
    {
        cout << "~child()\n";
    }
	void func()
	{
		cout << "child::func()\n";
	}
};

class base1
{
public:
    virtual ~base1()
    {
        cout << "~base1()\n";
    }
	virtual void func()
	{
		cout << "base1::func()\n";
	}
};

class child1 : public base1
{
public:
    ~child1()
    {
        cout << "~child1()\n";
    }
	virtual void func()
	{
		cout << "child1::func()\n";
	}
};

class Obj
{
public:
	Obj() { cout << "Obj()" << endl; }
	Obj(const Obj&) { cout << "Obj(const Obj&)" << endl; }
	Obj(Obj&&) { cout << "Obj(Obj&&)" << endl; }
	void func() { cout << "func()" << endl; }
};

Obj simple()
{
	Obj obj;//has NRVO
	return obj;
}

Obj& simple1()
{
	Obj obj;//has NRVO
	return obj;
}

Obj simple_with_move()
{
	Obj obj;
	return std::move(obj);//forbidden NRVO
}

Obj complicated(int n)
{
	Obj obj1;
	Obj obj2;
	if (n % 2 == 0)//has branch, no NRVO
	{
		return obj1;
	}
	else {
		return obj2;
	}
}

void foo(const shape&)
{
	cout << "foo(const shape&)" << endl;
}

void foo(const shape&&)
{
	cout << "foo(const shape&&)" << endl;
}

#if 0
void bar(const shape& s)
{
	cout << "bar(const shape&)" << endl;
	foo(s);
}

void bar(shape&& s)
{
	cout << "bar(const shape&&), use move?" << endl;
	//foo(s);
	foo(std::move(s));
}
#endif


template <typename T>
void bar(T&& s)
{
	foo(std::forward<T>(s));
}

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
	smart_ptr<shape> ptr2 = std::move(ptr1);//std::move convert a lvalue ref to rvalue ref(content consist)
	smart_ptr<shape> ptr3 = static_cast<smart_ptr<shape>&&>(ptr1);
	smart_ptr<shape> ptr5 = ptr1;
	if (ptr1.get())
	{
		ptr1->func();
	}

    auto ptrshape = new circle();
    shape& ref5 = *ptrshape;
    delete ptrshape, ptrshape = nullptr;
    //ref5.func();//crash

    {
        cout << "=====>" << endl;
        result&& r = process_shape(circle(), triangle());
        cout << "<=====" << endl;
    }
    {
        cout << "=====>" << endl;
        result&& r = std::move(process_shape(circle(), triangle()));
        cout << "<=====" << endl;
        //r.func();//undefined action, result was destructed actually
    }
    cout << "==========================" << endl;
    {
        cout << "1=====>" << endl;
        base& b1 = child();//T& bind with child won't cause memory leak
        
        cout << "1<=====" << endl;
    }
    {
        cout << "11=====>" << endl;
        shared_ptr<base> b11 = make_shared<child>();//smartptr won't cause memory leak, evenif no virtual destruct
        cout << "11<=====" << endl;
    }
    {
        cout << "12=====>" << endl;
        base* b12 = new child;//cause memory leak
        delete b12;
        cout << "12<=====" << endl;
    }
    {
        cout << "2=====>" << endl;
        base1& b1 = child1();
		b1.func();
        cout << "2<=====" << endl;
    }

	cout << "*** 1 ***" << endl;
	auto obj1 = simple();
	cout << "*** 11 ***" << endl;
	auto obj11 = simple1();
	obj11.func();
	cout << "*** 2 ***" << endl;
	auto obj2 = simple_with_move();
	cout << "*** 3 ***" << endl;
	auto obj3 = complicated(42);

	cout << "1-------------------" << endl;
	bar(circle());
	cout << "2-------------------" << endl;
	circle temp;
	bar(temp);
	bar(circle());
}

