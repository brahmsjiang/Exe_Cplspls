
#include<iostream>
#include<new>
#include<cstdlib>	//abort

using namespace std;

/*
 * namespace std{
 *	typedef void (*new_handler)();
 *	new_handler set_new_handler(new_handler p) throw();
 * }
 */

void outofMem()
{
	std::cerr<<"unalbe to satisfy request for memory\n";
	std::abort();
}

class NewHandlerHolder
{
public:
	explicit NewHandlerHolder(std::new_handler nh):handler(nh){cout<<"cons NewHandlerHolder"<<endl;}
	~NewHandlerHolder(){cout<<"des NewHandlerHolder"<<endl;std::set_new_handler(handler);}
private:
	std::new_handler handler;
	NewHandlerHolder(const NewHandlerHolder&);	//prevent copy
	NewHandlerHolder& operator=(const NewHandlerHolder&);	//prevent copy
};


class Widget
{
public:
	Widget(long ele=10000L):widgetele(ele){}
	static std::new_handler set_new_handler(std::new_handler p) throw();	//for widget
	static void* operator new(std::size_t size) throw(std::bad_alloc);		//for widget
private:
	static std::new_handler currentHandler;
	long widgetele;
};

std::new_handler Widget::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}
void* Widget::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder hd(std::set_new_handler(currentHandler));
	return ::operator new(size);
}

std::new_handler Widget::currentHandler=0;
////////////////////////////////////////////////////////
int main()
{
	//std::set_new_handler(outofMem);
	//int* pbig=new int[1000000000L];
	
	Widget::set_new_handler(outofMem);
	while(1)
		Widget* pw1 = new Widget;

	std::string* ps=new std::string;

	Widget::set_new_handler(0);
	Widget* pw2 = new Widget;


	return 0;
}








