
#include <iostream>
#include <vector>
using namespace std;

int g_constructCount=0;
int g_copyConstructCount=0;
int g_destructCount=0;

struct A
{
	A(){
		cout<<"construct: "<<++g_constructCount<<endl;
	}
	A(const A& a){
		cout<<"copy construct: "<<++g_copyConstructCount<<endl;
	}
	~A(){
		cout<<"destruct: "<<++g_destructCount<<endl;
	}
	//static A GetA(){
	//	return A();
	//}
};

A GetA()
{
	return A();
}

template<typename T>
void f(T&& param)
{}

template<typename T>
void f00(const T&& param)
{}

template<typename T>
class Test{
public:
	Test(T t):var(t){}
	Test(Test&& param):var(param.var){
	}
	T var;
};

template<typename T>
void f0(Test<T>&& param)
{}

void f2(A&& param)
{}

template<typename T>
void f3(std::vector<T>&& param)
{}

void printval(int& i)
{
	cout<<"lvalue: "<<i<<endl;
}

void printval(int&& i)
{
	cout<<"rvalue: "<<i<<endl;
}

void forward(int&& i)
{
	printval(i);
}

int main(int argc,char* argv[],char* envp[])
{
	//GetA();
	//const A& a=GetA();
	//
	f(10);	//OK
	int tmp0=10;f(tmp0);	//OK
	f00(10);	//OK
	//f00(tmp0);	//NG
	cout<<"before mainfunc end."<<endl;

	Test<int> test0(10);
	Test<int> test1(Test<int>(11));	//OK
	//Test<int> test2(test0);	//NG

	f2(GetA());		//OK
	//A aa;f2(aa);	//NG
	//Test test1(test0);

	f3(vector<int>(20));	//OK
	vector<int> v0(20);
	//f3(v0);	//NG
	
	int i=0;
	printval(i);
	printval(1);
	forward(2);

	return 0;
}


