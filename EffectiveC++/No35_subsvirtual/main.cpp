#include <iostream>
#include "chara.h"

using namespace std;


int bosshealth(const character2& obj){
	return obj.getrawhealthval()+20;
};//func, such as main func cannot define func, except c++11 lambda



int main(int argc, char* argv[])
{
	character1* cp=new beggar1();
	cp->healthval();
	
	cp=new character1();
	cp->healthval();
	//////////////////////////////////////////////
	std::string name="gaoyuqiang";
	//badguy boss0;// default construct should not add boss0(), complier will regard it as a pointer initialization====>error: request for member '*' in '*', which is of non-class type '*'
	
	badguy boss0(bosshealth,200,name);
	
	cout<<"boss name: "<<boss0.getname()<<endl;
	cout<<"boss health val: "<<boss0.healthval()<<endl;


	test pp("ddd");
	pp.print();	
	return 0;
}
