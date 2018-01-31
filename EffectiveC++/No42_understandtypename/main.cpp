/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月29日 星期一 21时52分47秒
 ************************************************************************/

#include<iostream>
#include<vector>

using namespace std;


template<typename T> class Widget;
template<class T>class Widget;

template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2) {
		typename C::const_iterator iter(container.begin());	//nested dependent name  
		++iter;
		int val = *iter;	//non-independent
		cout<<val<<endl;

		//C::const_iterator* x;	//error, need typename, default isnt a typename regarded by compiler 
	}
}

template<typename C>
void func0(const C& container, typename C::const_iterator iter)	//1st para cannot add typename, 2st para must add typename
{
	if(container.size() >= 2){
		iter = container.begin();
		++iter;
		int val = *iter;
		cout<<val<<endl;
	}
}

template<typename T>
class Base<T>
{
	struct Nested{

	}

};

template<typename T>
class Derived:public Base<T>::Nested {
public:
	explicit Derived(int x)
		:Base<T>Nested(x)
	{
		typename Base<T>::Nested temp;
	}
};

int main()
{
	vector<int> vi0(10,5);
	print2nd(vi0);

	vector<int> vi1(5,4);
	vector<int>::iterator iter1=vi1.begin();
	//vector<int>::iterator iter1;
	func0(vi1,iter1);
	return 0;
}





