#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>

using namespace std;

class class_c {
public:
	int max;
	int min;
	int middle;

	class_c() {}
	class_c(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	class_c(int my_max, int my_min) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	class_c(int my_max, int my_min, int my_middle) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};

class class_c1 {
public:
	int max;
	int min;
	int middle;

	class_c1() {}
	class_c1(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	class_c1(int my_max, int my_min) : class_c1(my_max) {
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	class_c1(int my_max, int my_min, int my_middle) : class_c1(my_max, my_min) {
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};

class class_a {
public:
	double m_double{1.0};
	string m_string;

	class_a() {}
	class_a(string str) : m_string{str} {}
	//class_a(string str, double db1) : class_a(str), m_double{db1} {}	//err
	class_a(string str, double db1) : class_a(str) { m_double = db1; }
};

struct Base {
	int x;
	double y;
	string s;
	
	Base(int i) : x(i),y(0.0) {}
	Base(int i, double j) : x(i),y(j) {}
	Base(int i, double j, const string& str) : x(i),y(j),s(str) {}
	void Fun() {cout<<"call in Base"<<endl;}
};

struct Derived: Base {};

struct Derived1: Base
{
	Derived1(int i) : Base(i) {}
	Derived1(int i, double j) : Base(i, j) {}
	Derived1(int i, double j, const string& str) : Base(i, j, str) {}
};

struct Derived2: Base
{
	using Base::Base;
	using Base::Fun;
	void Fun(int a) {cout<<"call in Derived2"<<endl;}
};

struct A
{
	virtual void foo() final;
	//void bar() final;	//only virtual func can be final
};

struct B final : A
{
	//void foo();	//final func can't be overrided
};

//struct C : B {};	//final class can't be overrided

struct AA
{
	virtual void func();
};

struct BB : AA
{
	void func() override {} //ensure same func signature and override
};



int main(int argc, const char * argv[]) {
	//Derived(1, 2.5, "ok");	//can't find appropriate construct func
	Derived1(1, 2.5, "ok");
	Derived2(1, 2.5, "ok");
	Derived2(1);
	Derived2 der2(1);
	der2.Fun();

	string str = "D:\A\B\test.text";
	cout << str << endl;
	string str1 = "D:\\A\\B\\test.text";
	cout << str1 << endl;
	string str2 = R"(D:\A\B\test.text)";
	cout << str2 << endl;
	string str3 = 
	R"(<HTML>
	<HEAD>
	</HEAD>
	</HTML>
	)";
	cout << str3 << endl;
	//string str4 = R"test(D:\A\B\test.text)";	//err
	//string str5 = R"test(D:\A\B\test.text)testa";	//err
	string str6 = R"test(D:\A\B\test.text)test";
	cout << str6 << endl;

	return 0;
}
