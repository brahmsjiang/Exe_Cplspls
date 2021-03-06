/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月18日 星期四 16时58分03秒
 ************************************************************************/

#include<iostream>
#include<typeinfo>
#include<vector>
#include<memory>	//sharedptr
#include "Base.h"

#define static_cast(TYPE,EXPR) ((TYPE)(EXPR))
#define const_cast(TYPE,EXPR) ((TYPE)(EXPR))
#define reinterpret_cast(TYPE,EXPR) ((TYPE)(EXPR))
#define dynamic_cast(TYPE,EXPR) ((TYPE)(EXPR))

using namespace std;


class father{
public:
	father()
		:i(0),j(0)
	{
		cout<<"father cons"<<endl;
	}
	father(const father&)
		:i(1),j(2)	//const var must be set at construct func
	{
		cout<<"father copycons"<<endl;
	}
	virtual void act(){
	}
	virtual ~father(){
		cout<<"father des"<<endl;
	}
	void seti(int var) const{
		//i=var;	//err, but const_cast can remove func's const attribute
		const_cast<int&>(i)=var;
	}
	const int i;
	int j;
};

class child:public father{
public:
	child(){
		cout<<"child cons"<<endl;
	}
	virtual void act(){
	}
	virtual ~child(){
		cout<<"child des"<<endl;
	}
};

class grandson:public child{
public:
	grandson(){
		cout<<"grandson cons"<<endl;
	}
	virtual void act(){
	}
	void hitgrandfather(){
		cout<<"hit grand father"<<endl;
	}
	virtual ~grandson(){
		cout<<"grandson des"<<endl;
	}
};

class window{
public:
	virtual void clear(){	//dynamic_cast require virtual func==>its a polymorphic class
		cout<<"clear window."<<endl;
	}
	virtual void blink(){}	//add virtual,avoid dynamic_cast
};
class spwindow:public window{
public:
	void blink(){
		cout<<"spwindow, blink!"<<endl;
	}
};

class widget{
public:
	explicit widget(int i):size(i){

	}
	int size;
};

void dosomething(const widget& w){
	cout<<"widget size: "<<w.size<<endl;
}

void statictest()
{
	father fa;
	child ch;
	if(auto ttpp = static_cast<grandson*>(&fa)){
			cout<<"shit! ";ttpp->hitgrandfather();	//downcast
	}
	else{
		cout<<"static_cast pointer null"<<endl;
	}
	cout<<"shit!! ";static_cast<grandson&>(ch).hitgrandfather();
	grandson gss;
	static_cast<father&>(gss).seti(22);	//upcast
	cout<<"shit!!! i: "<<gss.i<<endl;

	int pppp=9;
	void* nonptr=&pppp;
	//cout<<"*nonptr: "<<*nonptr<<endl;	//err,  ‘void*’ is not a pointer-to-object type
	cout<<*static_cast<int*>(nonptr)<<endl;
	//*nonptr=11;	//err, nonptr's type is still void*
	void* non=0;
	int* tmmpp = static_cast<int*>(non);	//void* to others
	//*tmmpp=10;	//core dump, pointer 0 cannot be set val, it must be point at others before
	tmmpp = &pppp;
	cout<<(*tmmpp = 10)<<endl;
	int* opop=0;
	//*opop=10;	//core dump, is the same
	//
	int n = static_cast<int>(3.14); 
	std::cout << "n = " << n << '\n';
	std::vector<int> v = static_cast<std::vector<int>>(10);
	std::cout << "v.size() = " << v.size() << '\n';

	Derived dd;
	dd.setnum(2,3);
	cout<<"dd i: "<<dd.i<<"	dd j: "<<dd.j<<endl;

	const child cs;	
	static_cast<father>(cs);	//static_cast will call copycons func
}

int dosomething(){cout<<"do some thing"<<endl;}

void reinterpret_test()
{
	int dosomething();
	typedef void (*funcptr)();
	funcptr funcptrary[10];
	funcptrary[0]=reinterpret_cast<funcptr>(&dosomething);	//dosomething is also right
	funcptrary[1]=(funcptr)dosomething;	//dosomething is also right
	//funcptrary[0]=dosomething;	//err
	funcptrary[0]();	//call func must use ()
	funcptrary[1]();
}

void dynamic_test()
{
	{
	typedef std::vector<std::shared_ptr<window>> VPW;
	VPW winptrs;
	//insert
	for(int i=0;i<4;i++){
		std::shared_ptr<window> ptr1(new spwindow());
		winptrs.push_back(ptr1);
	}
	//display
	for(VPW::iterator iter = winptrs.begin();iter!=winptrs.end();++iter){
		//window * pw=iter->get();
		if(spwindow* psw = dynamic_cast<spwindow*>((iter)->get())){
			psw->blink();
		}
	}
	}
	cout<<"dynamic_test==========================="<<endl;
	{
	typedef std::vector<std::shared_ptr<spwindow>> VSPW;
	VSPW winptrs;
	for(int i=0;i<3;i++){
		std::shared_ptr<spwindow> ptr1(new spwindow());
		winptrs.push_back(ptr1);
	}
	for(VSPW::iterator iter = winptrs.begin();iter!=winptrs.end();++iter){
		(*iter)->blink();
	}
	}
	cout<<"dynamic_test==========================="<<endl;
	{
		int gs=4;
		const_cast<int&>(gs)=5;	//ok
		static_cast<int&>(gs)=6;	//ok
		//static_cast<const int&>(gs)=7;	//err,const var cannot be set
		father fa;
		child ch;
		try{
			auto ttpp = dynamic_cast<grandson&>(fa);
			ttpp.hitgrandfather();
		}
		catch(std::bad_cast& tt){
			cout<<"dynamic_cast bad"<<endl;
		}
		if(auto ttpp = dynamic_cast<grandson*>(&ch)){
			ttpp->hitgrandfather();
		}
		else{
			cout<<"dynamic_cast pointer null"<<endl;
		}
		
	}
	
}



void const_test()
{
	const int const_i = 66;	//const only conver quote or pointer
	const int& ref_const_i = const_i;
	const_cast<int&>(ref_const_i) = 100;
	cout<<"const i: "<<const_i<<"	ref_const_i: "<<ref_const_i<<endl;

	int i = 66;
	const int& ref_i = i;
	const_cast<int&>(ref_i) = 100;
	cout<<"i: "<<i<<"	ref_i: "<<ref_i<<endl;

	int input;	//const cannot be optimize by compiler
	cout<<"please input a integer:";
	cin>>input;
	const int ii = input;
	int &ref_ii = const_cast<int&>(ii);
	ref_ii++;
	cout<<"ii: "<<ii<<"	ref_ii: "<<ref_ii<<endl;

	const int iii= 77;	//const can be optimize by compiler
	int &ref_iii= const_cast<int&>(iii);
	ref_iii++;
	cout<<"iii: "<<iii<<"	ref_iii: "<<ref_iii<<endl;
	
	const int j = 77; //Modify const object through a non-const access path results in undefined behavior.
	int jj = const_cast<int&>(j)=78;// undefined behavior!
	cout<<"j: "<<j<<"	jj: "<<jj<<endl;

	class A{
	public:
		A():i(0){}
		int i;	
	};
	const A a;
	int ref_ai = const_cast<int&>(a.i)=8;
	cout<<"a.i: "<<a.i<<"	ref_ai: "<<ref_ai<<endl;

	
	
}

int main()
{
	//reinterpret_test();
	const_test();
	//dynamic_test();

	cout<<"==========================="<<endl;	
	dosomething(widget(5));
	dosomething(static_cast<widget>(25));
	//dosomething(25);	//err,explicit

	cout<<"==========================="<<endl;	
	//statictest();	
	cout<<"==========================="<<endl;	
#if 0
	father* bptr = new grandson();
	cout<<"typeof bptr is: "<<typeid(bptr).name()<<endl;
	cout<<"typeof *bptr is: "<<typeid(*bptr).name()<<endl;
	bptr = new child();
	cout<<"typeof *bptr is: "<<typeid(*bptr).name()<<endl;
#endif
		
	return 0;
}
