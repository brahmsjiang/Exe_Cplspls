/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 17时26分08秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

typedef std::vector<double> VD;

class widgetimpl
{
public:
	widgetimpl(int vara=0, const VD& varv=VD())
		:a(vara),v(varv){}
	void printimpl()
	{
		cout<<"a: "<<a<<"	v: ";
		for(VD::iterator it=v.begin();it!=v.end();++it)
		{
			cout<<*it<<" ";
		}
		cout<<endl;
	}
private:
	int a;
	VD v;
};

class widget
{
public:
	widget(widgetimpl* pt=new widgetimpl())
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
	void swap(widget& other)
	{
		using std::swap;
		cout<<"swaping..."<<endl;
		swap(pimpl, other.pimpl);
	}
	void printimpl()
	{
		if(pimpl)	pimpl->printimpl();
	}
	~widget()
	{
		pimpl=NULL;
	}
private:
	widgetimpl* pimpl;

};



namespace std{
template<>
void swap<widget>(widget& a, widget& b)
{
	a.swap(b);
	//swap(a.pimpl, b.pimpl);	//err, pimpl is private
}
}



int main()
{
	widgetimpl wi0(666,VD(4,3.14));
	widgetimpl wi1(777,VD(2,6.66));
	widget wg0(&wi0);
	widget wg1(&wi1);
	cout<<"wg0 ";wg0.printimpl();
	cout<<"wg1 ";wg1.printimpl();
	
	swap(wg0,wg1);
	cout<<"wg0 ";wg0.printimpl();
	cout<<"wg1 ";wg1.printimpl();

	return 0;
}




