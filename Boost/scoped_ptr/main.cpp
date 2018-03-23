
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>
#include <string>
#include <iostream>
using namespace boost;
using namespace std;

class ptr_owned final
{
	scoped_ptr<int> m_ptr;
};

//class derived:ptr_owned	//ptr_owned final forbid other class derived from it
//{};

struct posix_file
{
	posix_file(const char* file_name)
	{
		cout<<"open file:"<<file_name<<endl;
	}
	~posix_file()
	{
		cout<<"close file"<<endl;
	}
};

int main(int argc,char* argv[],char* envp[])
{
	scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));
	scoped_ptr<int> ip(new int);
	if(ip)
	{
		*ip=100;
		cout<<*ip<<endl;
	}
	ip.reset();
	assert(ip==0);
	if(!ip)
		cout<<"scoped_ptr==nullptr"<<endl;

	scoped_ptr<string> sp(new string("text"));
	assert(sp);
	assert(sp!=nullptr);
	cout<<*sp<<endl;
	cout<<sp->size()<<endl;
	//sp++;	//has no operator++
	//std::prev(sp);	//has no operator--
	//delete sp.get();	//forbidden,destruct twice
	//scoped_ptr<string> sp2=sp;	//forbidden,call private scoped_ptr(scoped_ptr const &)
	scoped_ptr<string> sp2;
	//sp2=sp;	//forbidden,call private scoped_ptr & operator=(scoped_ptr const &)
	
	ptr_owned p;
	//ptr_owned p2(p);	//complie error,because scoped_ptr cannot be copied
	
	
	////////////////////////////////////////////////////////////////////////////
	unique_ptr<int> up(new int);
	assert(up);
	*up=10;
	cout<<*up<<endl;
	unique_ptr<int> up2;
	//up2=up;	//compile err
	up.reset();
	assert(!up);

	auto pp=boost::make_unique<int>(10);
	assert(pp && *pp==10);
	auto pnums=boost::make_unique<int[]>(7);
	for(size_t i{};i<7;++i)
		pnums[i]=i*i;
	for(size_t i{};i<7;++i)
		cout<<pnums[i]<<endl;
	auto upname=boost::make_unique<string>("Algernon");
	unique_ptr<string> upname2(upname.release());
	assert(!upname);
	assert(upname2);
	return 0;
}




