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

using namespace std;

class father{
public:
	father()
		:i(0),j(1)
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
	virtual ~grandson(){
		cout<<"grandson des"<<endl;
	}
};

class window{
public:
	virtual void clear(){	//dynamic_cast require virtual func==>its a polymorphic class
		cout<<"clear window."<<endl;
	}
};
class spwindow:public window{
public:
	void blink(){
		cout<<"spwindow, blink!"<<endl;
	}
};

int main()
{
	//const father bs;
	//const_cast<father&>(bs);	//pointer, reference, or a pointer-to-data-member type
	
	{
	const child cs;
	//cs.i=6;	//err, readonly var cannot be set
	//cs.j=6;	//err, const obj cannot be varified
	const_cast<child&>(cs).j=6;
	cout<<"i: "<<cs.i<<"	j: "<<cs.j<<endl;
	const_cast<child*>(&cs)->seti(7);	//const_cast is used between pointer or reference
	cout<<"i: "<<cs.i<<endl;
	const_cast<child&>(cs).seti(8);	//const_cast wont call copycons func
	cout<<"i: "<<cs.i<<endl;
	}
	cout<<"==========================="<<endl;	
	typedef std::vector<std::shared_ptr<window>> VPW;
	VPW winptrs;
	VPW
	
	for(VPW::iterator iter = winptrs.begin();iter!=winptrs.end();++iter){
		//window * pw=iter->get();
		if(spwindow* psw = dynamic_cast<spwindow*>((iter)->get())){
			psw->blink();
		}
	}



	cout<<"==========================="<<endl;	

	const child cs;	
	static_cast<father>(cs);	//static_cast will call copycons func
#if 0
	father* bptr = new grandson();
	cout<<"typeof bptr is: "<<typeid(bptr).name()<<endl;
	cout<<"typeof *bptr is: "<<typeid(*bptr).name()<<endl;
	bptr = new child();
	cout<<"typeof *bptr is: "<<typeid(*bptr).name()<<endl;
#endif
		
	return 0;
}
