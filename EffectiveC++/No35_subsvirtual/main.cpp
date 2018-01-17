#include <iostream>
#include "chara.h"

using namespace std;


int glhealth(const character2& obj){
	return obj.getrawhealthval()*1.2;
};//func, such as main func cannot define func, except c++11 lambda

int sglhealth(const character2& obj){
	return obj.getrawhealthval()*1.5;
};//func, such as main func cannot define func, except c++11 lambda

int recoverlasthealth(const character2& obj){
	return sglhealth(obj)+20;

};//func, such as main func cannot define func, except c++11 lambda

///////////////////////////////////////////////////////////////////
short plhealth0(const character3& obj){
	return obj.getrawhealthval()*1.8;
}

struct plhealth1{
	int operator() (const character3& obj){
		return obj.getrawhealthval()*1.9;
	}
};

class gamelevel{
public:
	float plhealth2(const character3& obj){
		return obj.getrawhealthval()*1.91;
	}
};

int bindfunc(int p1,int p2, int p3){
	cout<<"P1: "<<p1<<endl;
	cout<<"P2: "<<p2<<endl;
	cout<<"P3: "<<p3<<endl;
}

class A{
public:
	A(int xval=2, int yval=3)
		:x(xval),y(yval)
	{
	}
	void printXY(){
		//cout<<x<<endl<<y<<endl;	//also can use member val directly
		cout<<this->x<<endl<<this->y<<endl;
	}
private:
	int x,y;
};

int main(int argc, char* argv[])
{
	character1* cp=new beggar1();
	cp->healthval();
	
	cp=new character1();
	cp->healthval();

	beggar1 xxxx;
	xxxx.healthval();
	//////////////////////////////////////////////
	//badguy boss0;// default construct should not add boss0(), complier will regard it as a pointer initialization====>error: request for member '*' in '*', which is of non-class type '*'
	std::string name="yugaoqiang";
	badguy boss0(glhealth,100,name);
	cout<<"name: "<<boss0.getname()<<endl;
	cout<<"health val: "<<boss0.healthval()<<endl;

	badguy boss1(sglhealth,100,"jiazhao");
	cout<<"name: "<<boss1.getname()<<endl;
	cout<<"health val: "<<boss1.healthval()<<endl;
	
	boss1.sethealthfunc(recoverlasthealth);
	cout<<"name: "<<boss1.getname()<<endl;
	cout<<"health val: "<<boss1.healthval()<<endl;
	///////////////////////////////////////////////
	evilbadguy killer0(plhealth0,1000,"gangchen");
	cout<<"name: "<<killer0.getname()<<endl;
	cout<<"health val: "<<killer0.healthval()<<endl;
	
	evilbadguy killer1(plhealth1(),1000,"jiabintang");//functor must use ad functor()
	cout<<"name: "<<killer1.getname()<<endl;
	cout<<"health val: "<<killer1.healthval()<<endl;
	cout<<"functor call: "<<plhealth1()(killer1)<<endl;//funcrot with para mustbe called as"functor()(xxxx)"
	
	gamelevel curlevel;
	auto func=std::bind(&gamelevel::plhealth2,&curlevel,placeholders::_1);//std::bind parameter==>&class::func,obj,bandpar,placeholder
	evilbadguy killer2(func,1000,"myself");
	cout<<"name: "<<killer2.getname()<<endl;
	for(long i=99999999*4;i>=0;i--){
	}
	cout<<"health val: "<<killer2.healthval()<<endl<<endl;
	/////////////////////////////////////////////	
	auto func1=std::bind(bindfunc,1,2,3);
	func1();
	auto func2=std::bind(&bindfunc,placeholders::_2,100,placeholders::_1);	//for normalfunc,both &normalfunc and normalfunc is allowed
	func2(200,300);
	////////////////////////////////////////////
	healthcal* funcptr=new badguy_healthcal();
	character4* objptr=new char4_guy0(funcptr,10,"cplspls");
	cout<<"name: "<<objptr->getname()<<endl;
	cout<<"health val: "<<objptr->healthval()<<endl;

	A aa;
	aa.printXY();
	return 0;

}






