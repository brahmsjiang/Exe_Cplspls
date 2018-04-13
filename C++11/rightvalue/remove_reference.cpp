#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

template <typename T>
class remove_reference
{
public:
	typedef T type;
	typedef T& type_ref;
	typedef T* type_pointer;
};


template <typename T>
class remove_reference<T&>
{
public:
	typedef T type;
	typedef T& type_ref;
	typedef T* type_pointer;
};

template <typename T>
class GetType
{
public:
	typedef T type;
	typedef T& type_ref;
	typedef T* type_pointer;
};

template<typename T>
class GetType<T&>
{
public:
	typedef typename remove_reference<T>::type type;
	typedef typename remove_reference<T>::type_ref type_ref;
	typedef typename remove_reference<T>::type_pointer type_pointer;
};

template<typename T>
class GetType<T*>
{
public:
	typedef typename remove_reference<T>::type type;
	typedef typename remove_reference<T>::type_ref type_ref;
	typedef typename remove_reference<T>::type_pointer type_pointer;
};


int main(int argc,char* argv[],char* envp[])
{
	int a0=7;
	decltype(a0) b0=a0;
	a0=77;
	cout<<"b0: "<<b0<<endl;
	//////////////////////////
	a0=7;
	int& a1=a0;
	decltype(a1) b1=a0;
	a0=77;
	cout<<"b1: "<<b1<<endl;
	/////////////////////////
	a0=7;
	int& a2=a0;
	remove_reference<decltype(a2)>::type b2=a0;
	a0=77;
	cout<<"b2: "<<b2<<endl;
	cout<<"====================="<<endl;
	int c0=0;
	
	int* c1=&c0;
	cout<<"c0 type: "<<typeid(c0).name()<<endl;
	cout<<"c0 type: "<<typeid(GetType<decltype(c0)>::type_pointer).name()<<endl;
	cout<<"c1 type: "<<typeid(c1).name()<<endl;
	cout<<"c1 type: "<<typeid(GetType<decltype(c1)>::type).name()<<endl;
	
	return 0;
}




