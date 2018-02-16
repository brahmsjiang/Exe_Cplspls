
#include<iostream>
#include<string>
using namespace std;

class arrobj
{
public:
	arrobj(int num=7):_num(num){
		cout<<"arrobj cons,_num="<<_num<<endl;
	}
	~arrobj(){
		_num = 0;
		cout<<"arrobj des,_num="<<_num<<endl;
	}
private:
	int _num;

};

class A
{
public:
	A(arrobj* tmp):ptr(tmp){}
	A(unsigned int num):ptr(new arrobj[num]){}	
	~A(){
		delete [] ptr;
	}
private:
	arrobj* ptr;

};

int main()
{
	arrobj* arrobj_ptr=new arrobj;
	delete arrobj_ptr;
	///////////////////////////////////////////////////////
	
	//arrobj* arrobjs_ptr0=new [] arrobj;	//error form
	arrobj* arrobjs_ptr0=new arrobj[4];
	//delete arrobjs_ptr0[];	//error form
	delete [] arrobjs_ptr0;
	cout<<"//////////////////////////////////////"<<endl;	
	//arrobj * tmp0 = new arrobj;
	//A a0(tmp0);	//dump
	cout<<"//////////////////////////////////////"<<endl;	
	A a1(3);

	typedef std::string Address[4];
	std::string* pal=new Address;
	//delete pal;	//err
	delete [] pal;	//ok
	
	return 0;

}



