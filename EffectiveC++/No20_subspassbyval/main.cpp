
#include <iostream>
using namespace std;

class A
{
public:
	A(){
		cout<<"A::A()"<<endl;
	}
	virtual ~A(){
		cout<<"A::~A()"<<endl;
	}
	A(const A&){
		cout<<"A::A(const A&)"<<endl;
	}
	A& operator=(const A&){
		cout<<"A::operator=(const A&)"<<endl;
		return *this;
	}
	virtual void print(){
		cout<<"A::print"<<endl;
	}
};

class AA:public A
{
public:
	AA():A(){
		cout<<"AA::AA()"<<endl;
	}
	~AA(){
		cout<<"AA:~AA()"<<endl;
	}
	AA(const AA& aa):A(aa){	//no12, baseclass copycons should be called when define derived class copycons
		cout<<"AA::AA(const AA&)"<<endl;
	}
	AA& operator=(const AA&){
		cout<<"AA::operator=(const AA&)"<<endl;
		return *this;
	}
	virtual void print(){
		cout<<"AA::print"<<endl;
	}
};

void callAA(AA& a)
{
	cout<<"at callAA=========="<<endl;
}

void callA(A& a)
{
	cout<<"at callA=========="<<endl;
	a.print();
}

AA retAA(){
	AA aa0;
	return aa0;
}	

int main()
{
//	AA aa;
	//cout<<"before callAA=========="<<endl;
	//callAA(aa);
	//cout<<"after callAA=========="<<endl;
	//cout<<"before callA=========="<<endl;
//	callA(aa);
	//cout<<"after callA=========="<<endl;

	cout<<"before return=========="<<endl;
	//A aaa;		
	
	retAA().print();
	return 0;
}












