
#include<iostream>
#include<memory>

using namespace std;

class B;
class A{
public:
	A(){cout<<"cons A"<<endl;}
	std::shared_ptr<B> pa; 
	~A(){cout<<"des A"<<endl;}
};

class B{
public:
	B(){cout<<"cons B"<<endl;}
	std::shared_ptr<A> pb; 
	~B(){cout<<"des B"<<endl;}
};

class BB;
class AA{
public:
	AA(){cout<<"cons AA"<<endl;}
	std::weak_ptr<BB> pa; 
	~AA(){cout<<"des AA"<<endl;}
};

class BB{
public:
	BB(){cout<<"cons BB"<<endl;}
	std::weak_ptr<AA> pb; 
	~BB(){cout<<"des BB"<<endl;}
};

int main()
{
	//loop quote
	{
	std::shared_ptr<A> ptra(new A());
	auto ptrb = std::make_shared<B>();	//B() is constructor, not new B()
	//auto ptrb = std::make_shared<B>(B());	//B() is constructor, not new B()
	ptra->pa = ptrb;
	ptrb->pb = ptra;
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	ptra = nullptr;	//cannot res
	//ptrb.reset();	//cannot res
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	}
	cout<<"=========================="<<endl;
	{
	std::shared_ptr<AA> ptra(new AA());
	auto ptrb = std::make_shared<BB>(BB());
	ptra->pa = ptrb;
	ptrb->pb = ptra;
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	ptra = nullptr;	//cannot res
	//ptrb.reset();	//cannot res
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	}


	return 0;
}
