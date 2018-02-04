/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 17时26分08秒
 ************************************************************************/

#include<iostream>
#include<vector>

namespace widgetstuff{


template<typename T>
class widgetimpl
{
public:
	typedef std::vector<T> TD;
	widgetimpl(int vara=0, const TD& varv=TD())
		:a(vara),v(varv){}
	void printimpl()
	{
		using std::cout;
		using std::endl;
		cout<<"a: "<<a<<"	v: ";
		for(typename TD::iterator it=v.begin();it!=v.end();++it)	//need 'typename' before *** because *** is a dependent scope, add 'typename'
		{
			cout<<*it<<" ";
		}
		cout<<endl;
	}
private:
	int a;
	TD v;

};

template<typename T>
class widget
{
public:
	widget(widgetimpl<T>* pt=new widgetimpl<T>())
		:pimpl(pt)
	{
	}
	widget(const widget& rhs)
		:pimpl(rhs.pimpl)
	{
	}
	widget& operator=(const widget& rhs)
	{
		pimpl=rhs.pimpl;
		*(pimpl)=*(rhs.pimpl);
		return *this;
	}
#if 0
	void swap(widget& other)
	{
		using std::cout;
		using std::endl;
		cout<<"swaping..."<<endl;
		std::swap(pimpl, other.pimpl);
	}
#endif
	void printimpl()
	{
		if(pimpl)	pimpl->printimpl();
	}
	~widget()
	{
		pimpl=NULL;
	}
private:
	widgetimpl<T>* pimpl;

};


#if 0
namespace std{
template<typename T>
void swap<widget<T>>(widget<T>& a, widget<T>& b)	
//err,partially specialize only can be on class template not on function template
void swap(widget<T>& a, widget<T>& b)	//a overload version simply
{a.swap(b);}

}

template<typename T>
void swap(widget<T>& a,widget<T>& b)
{
	a.swap(b);
}
#endif
}

template<typename T>
void dosomething(T& obj1, T& obj2)
{
//	using std::swap;
	swap(obj1, obj2);
}

int main()
{
	using namespace widgetstuff;
	widgetimpl<std::string> wi0(666,std::vector<std::string>(6,"fuck"));	
	widget<std::string> wg0(&wi0);
	
	widgetimpl<std::string> wi1(777,std::vector<std::string>(4,"GG"));	
	widget<std::string> wg1(&wi1);
	
	std::cout<<"wg0 ";wg0.printimpl();	
	std::cout<<"wg1 ";wg1.printimpl();
	
	//swap(wg1,wg0);
	dosomething(wg1,wg0);
	std::cout<<"wg0 ";wg0.printimpl();	
	std::cout<<"wg1 ";wg1.printimpl();
	
	std::cout<<"================="<<std::endl;


	return 0;
}




