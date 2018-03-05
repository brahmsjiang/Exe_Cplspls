
#include <iostream>
#include <memory>
#include <string>
using namespace std;

template<typename T>
void test_func0(std::unique_ptr<T>& up)	//must use quote, because unique not support copy
{
	if(NULL == up.get()){
		cout<<"up is NULL,ret"<<endl;
			return;
	}
	cout<<"test_func *up: "<<*up<<endl;
}

template<class T>
std::unique_ptr<T> test_func1(const T& tp)
{
	std::unique_ptr<T> ptmp(new T(tp));
	return ptmp;	//can ret unique<T>, implicit move
}


int main()
{
	/////////////unique_ptr initialize
	std::unique_ptr<std::string> pname0(new std::string("Algernon"));
	cout<<*pname0<<endl;
	auto pname1 = std::make_unique<std::string>("Peter");	//c++14
	cout<<*pname1<<endl;
	////////////unique_ptr get raw pointer
	auto pname2 = std::make_unique<std::string>(6,'*');	//c++14
	std::string* pstr(pname2.get());	//get raw pointer
	cout<<"str is:"<<*pstr<<endl;

	////////////unique_ptr point to array 
	size_t len{10};	//c++11 initialized
	std::unique_ptr<int[]>pnum0{new int[len]};
	auto pnums1 = std::make_unique<int[]>(len);	//why??
	for(size_t i{};i<len;++i){
		pnum0[i]=i*i;
		cout<<pnum0[i]<<" ";
	}cout<<endl;

	////////////unique_ptr as parameter
	std::unique_ptr<size_t> psize(new size_t(20));
	std::unique_ptr<std::string> pstr2(new std::string("verrry"));
	test_func0(psize);	//actual parameter instantiation
	test_func0<size_t>(psize);
	//test_func0<size_t>(pstr2);	//err
	test_func0(pstr2);	//ok

	////////////unique_ptr as retval
	std::string strr0(7,'=');
	auto petrr0 = test_func1(strr0);
	test_func0(petrr0);	
	
	////////////unique_ptr reset
	auto pname3 = std::make_unique<std::string>("fffffuck");
	test_func0(pname3);
	pname3.reset(new std::string("sssshit"));
	test_func0(pname3);
	pname3.reset();	//destory obj pointed to, and raw ptr willbe NULL
	test_func0(pname3);
	
	////////////unique_ptr release
	auto pname4 = std::make_unique<std::string>("bbbitch");
	std::string* pname5 = pname4.release();
	std::unique_ptr<std::string> pname6(pname5);
	cout<<"*pname5: "<<*pname5<<endl;	
	test_func0(pname6);
	test_func0(pname4);	

	////////////unique_ptr swap
	auto pn1 = std::make_unique<std::string>("Jack");
	auto pn2 = std::make_unique<std::string>("Jill");
	pn2.swap(pn1);
	test_func0(pn1);
	test_func0(pn2);
		
	////////////unique_ptr swap
	auto up_name = std::make_unique<std::string>("algernon");
	std::unique_ptr<std::string> up_name2;
	//up_name2 = up_name;	//err, assignment operator only accepts rvalues, which are typically generated by std::move
	up_name2 = std::move(up_name);
	if(up_name2 == up_name2)
		cout<<"up_name2 is equal to up_name2"<<endl;
	if(up_name2 == up_name)
		cout<<"up_name2 is equal to up_name"<<endl;
	else
		cout<<"up_name2 isnot equal to up_name"<<endl;

	//std::string ttmmpp(8,'!');
	//up_name.reset(ttmmpp);	//err, obj only at the heap
	up_name.reset(new std::string(7,'~'));
	std::unique_ptr<std::string> up_new(up_name.release());
	if(up_new)
		cout<<"the *up_new is "<<*up_new<<endl;
	if(!up_name)
		cout<<"the up_name is nullptr"<<endl;
	
	if(up_new != up_name)
		cout<<"up_new is not equal to up_name"<<endl;
	else
		cout<<"up_new is equal to up_name"<<endl;

	return 0;
}















