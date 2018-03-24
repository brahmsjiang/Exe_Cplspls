
#include <boost/atomic.hpp>
#include <boost/utility.hpp>
#include <boost/static_assert.hpp>
#include <iostream>
#include <bitset>
using namespace boost;
using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	atomic<int> a(10);
	assert(a==10);
	atomic<long> l;	//bad,no initial val
	cout<<l<<endl;

	atomic<bool> b{false};
	assert(!b.load());	//load
	b.store(true);	//store
	assert(b);	//T() <==>load
	b=false;	//operator= <==>stroe
	assert(!b);

	atomic<int> n(100);
	assert(n.exchange(200)==100);
	assert(n==200);

	atomic<long> l1(100);
	long v = 100;	//expected val, lval 
	if(l1.compare_exchange_weak(v,313))	//compare and swap
	{
		assert(l1==313 && v==100);
	}
	v = 700;
	auto b1=l1.compare_exchange_strong(v,99);	//v become previous val(313)
	assert(v==313 && l1==313 && !b1);	//swap failed,ret false
	b1=l1.compare_exchange_weak(v,99);
	assert(v==313 && l1==99 && b1);	//swap success,ret true/false
	cout<<"load(): "<<l1.load()<<endl;	//load() ret lval,cannot be operated
	cout<<"storage(): "<<++l1.storage()<<endl;	//storage() ret ref

	atomic<int> n1(100);
	assert(n1.fetch_add(10)==100);
	assert(n1==110);
	assert(++n1==111);	//after val
	assert(n1++==111);	//prev val
	assert(n1==112);

	atomic<int> b2(BOOST_BINARY(1101));
	atomic<int> b3{BOOST_BINARY(1101)};
	auto x=b3.fetch_and(BOOST_BINARY(0110));
	assert(x==BOOST_BINARY(1101) && b3==BOOST_BINARY(0100));
	cout<<"b3: "<<bitset<sizeof(b3)>(b3)<<endl;	//binary output
	assert((b3|=BOOST_BINARY(1001)) == BOOST_BINARY(1101));	// operator|= ret after val,which call fetch_or
	b3=BOOST_BINARY(0100);
	assert(b3.fetch_or(BOOST_BINARY(1001)) == BOOST_BINARY(0100));	// fetch_or ret perv val
	//compile err,strictly requires its condition to be a constant expression that can be evaluated at compile time
	//BOOST_STATIC_ASSERT(b3==BOOST_BINARY(1101));
	BOOST_STATIC_ASSERT(7==BOOST_BINARY(111));

	atomic<bool> b4{true};
	assert(b4);
	b4=false;
	assert(!b4);
	assert(!b4.load());
	auto x2=b4.exchange(true);	//exchange() ret prev val
	assert(!x2 && b4);
	return 0;
}






