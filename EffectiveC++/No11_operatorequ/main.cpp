#include <iostream>
#include <string>
#include "string.h"	//memset,memcpy
#include "stdio.h"
using namespace std;

class Widget{
public:
	Widget(std::string str="")
		:name(str)
	{

	}
	//void operator=(const Widget& wig)
	//{
	//	name=wig.name;
	//}
	Widget& operator=(const Widget& wig)
	{
		name=wig.name;
		return *this;
	}
	void printname()
	{
		cout<<name<<endl;
	}
private:
	std::string name;
};


class TestClass
{
public:
	TestClass(char* ptr)
	{
		pname=ptr;
	}
	void print()
	{
		if(pname)
			printf("%s\n",pname);
		else
			cout<<"pname is NULL!\n";
	}
#if 0
	TestClass& operator=(const TestClass& tc)
	{
		delete pname;pname=NULL;
		if(tc.pname==NULL)
			cout<<"tc.pname is NULL!"<<endl;
		int size=sizeof(*tc.pname);
		pname=new char(sizeof(size));
		memset(pname,' ',size);
		memcpy(pname,tc.pname,size);
		return *this;
	}
#endif
#if 0
	TestClass& operator=(const TestClass& tc)
	{
		if(this==&tc) return *this;
		delete pname;pname=NULL;
		if(tc.pname==NULL)
			cout<<"tc.pname is NULL!"<<endl;
		int size=sizeof(*tc.pname);
		pname=new char(sizeof(size));
		memset(pname,' ',size);
		memcpy(pname,tc.pname,size);
		return *this;
	}
#endif
//#if 0
	TestClass& operator=(const TestClass& tc)
	{
		char* ptmp=pname;
		int size=sizeof(*tc.pname);
		pname=new char(sizeof(size));
		memset(pname,' ',size);
		memcpy(pname,tc.pname,size);
		delete ptmp;
		return *this;
	}
//#endif
private:
	char* pname;
};



int main()
{
	Widget wig1("jack");
	wig1.printname();
	Widget wig2(wig1);
	wig2.printname();

	Widget wig4,wig3;	
	wig3.printname();
	wig4.printname();
	//continous assigiment
	wig4=wig3=wig1;
	wig3.printname();
	wig4.printname();
	////////////////////////////////
	char* pstr1=new char(10);
	memset(pstr1,' ',10);
	memcpy(pstr1,"MIKE",sizeof("MIKE"));
	TestClass tc1(pstr1);
	tc1.print();
	tc1=tc1;
	tc1.print();
	return 0;
}






