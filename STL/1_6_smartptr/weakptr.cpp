
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
	auto ptrb = std::make_shared<B>();	//() calls B constructor, not new B()
	//auto ptrb = std::make_shared<B>(B());	//B() calls copy constructor, not new B()
	ptra->pa = ptrb;
	ptrb->pb = ptra;
	*ptra->pa;	//admit
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
	auto ptrb = std::make_shared<BB>();
	ptra->pa = ptrb;
	ptrb->pb = ptra;
	//*ptra->pa;	//weak not support *pointer
	auto patmp(ptra->pa);	//weakptr copy
	//*patmp;	//patmp is weak
	
	std::shared_ptr<BB> pashtp(patmp);	//through weakptr to create sharedptr
	//std::shared_ptr<BB> pashtp=patmp;	//err, operator=
	if(pashtp)	cout<<"shared ptr create success"<<endl;
	else	cout<<"shared ptr create failed"<<endl;
	std::shared_ptr<AA> pbshtp(ptrb->pb.lock());	//through weakptr to create sharedptr
	if(pbshtp)	cout<<"shared ptr create success"<<endl;
	else	cout<<"shared ptr create failed"<<endl;

	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	cout<<"pashtp:	"<<pashtp<<"	"<<pashtp.use_count()<<endl;
	cout<<"pbshtp:	"<<pbshtp<<"	"<<pbshtp.use_count()<<endl;
	ptra = nullptr;
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	cout<<"pashtp:	"<<pashtp<<"	"<<pashtp.use_count()<<endl;
	cout<<"pbshtp:	"<<pbshtp<<"	"<<pbshtp.use_count()<<endl;
	ptrb.reset();
	cout<<"ptra:	"<<ptra<<"	"<<ptra.use_count()<<endl;
	cout<<"ptrb:	"<<ptrb<<"	"<<ptrb.use_count()<<endl;
	cout<<"pashtp:	"<<pashtp<<"	"<<pashtp.use_count()<<endl;
	cout<<"pbshtp:	"<<pbshtp<<"	"<<pbshtp.use_count()<<endl;
	pashtp.reset();
	pbshtp.reset();
	if(ptra==nullptr)	cout<<"ptra is null"<<endl;
	//if(ptra->pa==nullptr)	cout<<"ptra->pa is null"<<endl;	//err
	if(patmp.expired())	cout<<"patmp's obj no longer exist"<<endl;
	
	std::shared_ptr<BB> pbthtp2(patmp.lock());
	if(pbthtp2)	cout<<"shared ptr create success"<<endl;
	else	cout<<"shared ptr create failed"<<endl;

	}



	return 0;
}
