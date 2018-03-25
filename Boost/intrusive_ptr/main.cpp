
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <iostream>

using namespace boost;
using namespace std;

struct counted_data
{
	int m_count=0;
};

struct counted_data2:public intrusive_ref_counter<counted_data2>
{

};

void intrusive_ptr_add_ref(counted_data* p)
{
	++p->m_count;
}

void intrusive_ptr_release(counted_data* p)
{
	if(--p->m_count==0)
	{
		delete p;
	}
}

int main()
{
	typedef intrusive_ptr<counted_data> counted_ptr;
	
	counted_ptr p(new counted_data);
	assert(p);
	assert(p->m_count==1);	//ok

	counted_ptr p2(p);
	assert(p->m_count==2);

	counted_ptr weak_p(p.get(),false);	//weakref
	assert(p->m_count==2);	//m_count not change

	p2.reset();
	assert(!p2);
	assert(p);	//although p2 reset,p also exist
	assert(p->m_count==1);

	////////////////////////////////////////////
	typedef intrusive_ptr<counted_data2> counted_ptr2;
	counted_ptr2 p3(new counted_data2);
	assert(p3);
	assert(p3->use_count()==1);
	counted_ptr2 p4=p3;
	assert(p3->use_count()==2);
	assert(p4->use_count()==2);
	return 0;
}







