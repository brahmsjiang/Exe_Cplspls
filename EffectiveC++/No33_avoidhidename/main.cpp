/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月12日 星期五 09时52分02秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Base{
private:
	int x;
public:
	virtual void mf1()=0;
	virtual void mf1(int){
		cout<<"Base::mf1(int)"<<endl;
	}
	virtual void mf1(int,int){
		cout<<"Base::mf1(int,int)"<<endl;
	}
	virtual void mf2(){
		cout<<"Base::mf2()"<<endl;
	}
	void mf3(){
		cout<<"Base::mf3()"<<endl;
	}
	void mf3(double){
		cout<<"Base::mf3(double)"<<endl;
	}
};

void Base::mf1(){
	cout<<"Base::mf1()"<<endl;
}

class Derived0:public Base{
public:
	virtual void mf1(){
		cout<<"Derived0::mf1()"<<endl;
	}
	void mf3(){
		cout<<"Derived0::mf3()"<<endl;
	}
	void mf4(){
		cout<<"Derived0::mf4()"<<endl;
	}

};

class Derived1:public Base{
public:
	using Base::mf1;
	using Base::mf3;
	virtual void mf1(){
		cout<<"Derived1::mf1()"<<endl;
	}
	void mf3(){
		cout<<"Derived1::mf3()"<<endl;
	}
	void mf4(){
		cout<<"Derived1::mf4()"<<endl;
	}

};

class Derived2:public Base{
public:
	virtual void mf1(){
		Base::mf1();
	}
	virtual void mf1(int x){
		Base::mf1(x);
	}
	void mf3(){
		Base::mf3();
	}
	//int mf3(){	//mf3()'s signature is the same so it cannot be overloaded
	//	cout<<"Derived1::mf3()"<<endl;
	//	return 0;
	//}	
	void mf4(){
		cout<<"Derived2::mf4()"<<endl;
	}

};

int main()
{
	int x=1;
	Derived0 dv0;
	dv0.mf1();
	//dv0.mf1(x);	//err, base::mf1(int) is hided by derived0::mf1()
	dv0.mf2();
	dv0.mf3();
	//dv0.mf3(x);	//err,base::mf3(double) is hided by derived0::mf3()
	dv0.mf4();
	cout<<"======================="<<endl;	
	Derived1 dv1;
	dv1.mf1();
	dv1.mf1(x);
	dv1.mf2();
	dv1.mf3();
	dv1.mf3(x);
	dv1.mf4();
	cout<<"======================"<<endl;	
	Derived2 dv2;
	dv2.mf1();
	dv2.mf1(x);
	//dv2.mf1(x,x);	//err, base::mf1(int,int) is hided by others
	dv2.mf3();
	//dv2.mf3(x);	//err, base::mf3(double) is hided by derived2::mf3()
	
	return 0;
}
