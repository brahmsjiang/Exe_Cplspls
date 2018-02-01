/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月29日 星期一 21时52分47秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<typeinfo>

using namespace std;


template<typename T> class Widget;
template<class T>class Widget;

template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2) {
		typename C::const_iterator iter(container.begin());	//nested dependent name  
		++iter;
		int val = *iter;	//non-independent
		cout<<val<<endl;

		//C::const_iterator* x;	//error, need typename, default isnt a typename regarded by compiler 
	}
}

template<typename C>
void func0(const C& container, typename C::const_iterator iter)	//1st para cannot add typename, 2st para must add typename
{
	if(container.size() >= 2){
		iter = container.begin();
		++iter;
		int val = *iter;
		cout<<val<<endl;
	}
}

template<typename T>
class Base
{
public:
	class Nested{
	public:
		Nested(int var=0)
			:x(var){}
		void printNes(){
			cout<<"Base<"<<typeid(T).name()<<"> Nested x: "<<x<<endl;
		}
		int x;
	};
	void printBase(){
		cout<<"printBase"<<endl;
	}
	
};

template<typename T>
class Derived:public Base<T>::Nested{ 	//base class list, forbid typename
public:
	typedef typename Base<T>::Nested BTN;
	explicit Derived(int x)
		//:Base<T>::Nested(x)	//member init list, forbid typename
		:BTN(x)
	{
		//typename Base<T>::Nested temp;
		BTN temp(77);
		temp.printNes();
	}
};

int main()
{
	vector<int> vi0(10,5);
	print2nd(vi0);

	vector<int> vi1(5,4);
	vector<int>::iterator iter1=vi1.begin();
	//vector<int>::iterator iter1;
	func0(vi1,iter1);

	Derived<list<char>> der0(10);
	//der0.printBase();	//err,class Derived isnt inheritted from Base, but from Nested
	der0.printNes();	//so it can call bases Nested func

	Base<int>::Nested nes0(20);
	nes0.printNes();
	Base<std::string>::Nested nes1(30);
	nes1.printNes();
	Base<vector<char>>::Nested nes2(40);
	nes2.printNes();
	return 0;
}





