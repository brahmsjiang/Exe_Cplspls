
#include<iostream>
#include<new> 
#include<string>
#include<cstdlib>
#include<cstddef>

using namespace std;

class Widget;

class NewHandlerHolder
{
public:
	NewHandlerHolder(std::new_handler hn):handler(hn){}
	~NewHandlerHolder(){
		std::set_new_handler(handler);
	}
private:
	std::new_handler handler;
	NewHandlerHolder(const NewHandlerHolder&);
	NewHandlerHolder& operator=(const NewHandlerHolder&);
};

template<typename T>
class NewHandlerSupport{
public:
	NewHandlerSupport(){
		cout<<"cons NewHandlerSupport"<<endl;
	}
	static std::new_handler set_new_handler(std::new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);
private:
	static std::new_handler currentHandler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler=currentHandler;
	currentHandler=p;
	return oldHandler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder h(std::set_new_handler(currentHandler));
	return ::operator new(size);
}

class Widget:public NewHandlerSupport<Widget>
{
public:
	Widget(std::string str="default")
		:NewHandlerSupport<Widget>()
		,sname(str){
		cout<<"cons Widget"<<endl;
	}
	~Widget(){
		cout<<"des Widget"<<endl;
	}
	void widgetname(){
		cout<<"name is: "<<sname<<endl;
	}
private:
	std::string sname;
	long lnum[1000000000L];
};

class Widget1
{
public:
	Widget1(std::string str="default")
		:sname(str){
		cout<<"cons Widget1"<<endl;
	}
	~Widget1(){
		cout<<"des Widget1"<<endl;
	}
	void widgetname(){
		cout<<"name is: "<<sname<<endl;
	}
private:
	std::string sname;
	long lnum[1000000000L];
};


void outofMem()
{
	std::cerr<<"unable to satisfy request for memory\n";
	std::abort;
}

template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler=0;

int main()
{
	Widget1* ptwg=new (std::nothrow) Widget1;
	if(ptwg==0) cout<<"ptwg==0"<<endl;
	else	cout<<"ptwg!=0"<<endl;

	return 0;
}







