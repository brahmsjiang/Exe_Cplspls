#include <iostream>
#include <string>
#include "string.h"	//memset,memcpy
#include "stdio.h"
using namespace std;

char* crtstr(char* par);

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
	TestClass(const TestClass& tc)
	{
		pname=crtstr(tc.pname);	//deep copy
	}
	~TestClass()
	{
		cout<<"call ~TestClass"<<endl;
		if(pname!=NULL){	//if shallow copy will cause pname became wild pointer,if pname point a heap obj.
			//then if use swap method, the stack memory will delete by two obj at the end of program. so deep copy is OK. 
			cout<<"delete pname"<<endl;
			delete pname;	
			pname=NULL;
		}
	}
	void print()
	{
		if(pname)
			cout<<pname<<endl;
		else
			cout<<"pname is NULL!\n";
	}
#if 0
	TestClass& operator=(const TestClass& tc)
	{
		delete pname;pname=NULL;
		if(tc.pname==NULL){
			cout<<"tc.pname is NULL!"<<endl;
		}else
			pname=crtstr(tc.pname);
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
		pname=crtstr(tc.pname);
		return *this;
	}
#endif
//#if 0
	TestClass& operator=(const TestClass& tc)
	{
		//printf("==>%d, %s\n",sizeof(*pname),pname);//output 1,MIKE==>char* result is char,not whole string. so result is 1
		char* ptmp=pname;
		//pname=new char[] will refresh tc.pname,if tc and this is the same object. Must use a tmp var
		pname=crtstr(tc.pname);	
		delete ptmp;
		return *this;
	}
//#endif
#if 0
	TestClass& operator=(const TestClass& tc)
	{
		TestClass tmpobj(tc);
		char* tmpptr=tmpobj.pname;
		tmpobj.pname=pname;
		pname=tmpptr;
		return *this;
	}
#endif
private:
	char* pname;
};

char* crtstr(char* par)
{
	unsigned size=strlen(par);//strlen()不计算\0
	char* tmpptr=new char[size];
	memset(tmpptr,' ',size);//memset(tmpptr,'',10) is forbidden
	memcpy(tmpptr,par,size);
	par[size]='\0';
	return tmpptr;
	
}

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
	cout<<"print again"<<endl;
	tc1.print();
	return 0;
}






