
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

class B;
class A{
public:
	std::shared_ptr<B> pa; 
};

class B{
public:
	std::shared_ptr<A> pb; 
};


int main()
{
	//shared_ptr initialization
	std::shared_ptr<double> pdata(new double(999.99));
	cout<<*pdata<<endl;
	*pdata = 888.8;
	cout<<*pdata<<endl;
	auto pdata0 = make_shared<double>(999.9);
	auto pdata1(pdata0);
	std::shared_ptr<double> pdata2(pdata1);
	auto pdata3 = pdata2;
	cout<<*pdata0<<endl;
	cout<<*pdata1<<endl;
	cout<<*pdata2<<endl;
	cout<<*pdata3<<endl;
	auto ptmp0 = pdata2.get();
	cout<<ptmp0<<"	"<<*ptmp0<<endl;
	cout<<pdata0.use_count()<<endl;
	cout<<pdata3.use_count()<<endl;
	//std::shared_ptr<double> pdata4(pdata3.get());	//dump err, use shared_ptr::get() to initialize another shared_ptr is forbidden
	
	//reset
	pdata1 = nullptr;	//NULL denotes 0(also can be seen int),but nullptr is a nullpointer	
	cout<<pdata0.use_count()<<endl;
	pdata2.reset();
	cout<<"pdata1:	"<<pdata1.use_count()<<endl;
	cout<<"pdata2:	"<<pdata2.use_count()<<endl;
	cout<<"pdata0:	"<<pdata0.use_count()<<endl;
	pdata1.reset(new double(444.4));
	cout<<"pdata1:	"<<pdata1.use_count()<<endl;
	cout<<"pdata0:	"<<pdata0.use_count()<<endl;

	//compare
	if((pdata0 == pdata3) && (pdata0 != nullptr))	cout<<"pdata0 and pdata3 point to the same obj"<<endl;
	if(pdata0 != pdata1)	cout<<"pdata0 notequal to pdata1"<<endl;	
	if(!pdata2)	cout<<"pdata2 is null"<<endl;
	if(!pdata0.unique())	cout<<"there is more than one,num is:	"<<pdata0.use_count()<<endl;
	else					cout<<"there is only one"<<endl;

	//loop quote
	{
	//A* aptr = new A();
	//B* bptr = new B();
	std::shared_ptr<A> ptra(new A());
	auto ptrb = std::make_shared<B>();	//B() is constructor, not new B()
	//auto ptrb = std::make_shared<B>(B());	//B() is constructor, not new B()
	ptra->pa = ptrb;
	ptrb->pb = ptra;
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	}
	//cout<<"ptra count:	"<<ptra.use_count()<<endl;	//err,cannot find ptra by compiler
	
	return 0;
}

#if 0
class A{
public:
	std::shared_ptr<B> pa; 
};

class B{
public:
	std::shared_ptr<A> pb; 
};
#endif








