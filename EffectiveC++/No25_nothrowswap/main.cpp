/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 17时26分08秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

class widgetimpl
{
public:
private:
	int a,b,c;
	std::vector<double> v;
};

class widget
{
public:
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
		
private:
	widgetimpl* pimpl;

};



namespace std{
template<>
void swap<widget>(widget a&, widget b&)
{
	swap(a.pimpl, b.pimpl);
}


}



int main()
{



	return 0;
}
