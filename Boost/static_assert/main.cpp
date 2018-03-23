#include <boost/static_assert.hpp>
#include <iostream>
using namespace std;

template<typename T>
T my_min(T a,T b)
{
	//BOOST_STATIC_ASSERT(sizeof(T)<sizeof(int));	//gcc,g++
	BOOST_STATIC_ASSERT_MSG(sizeof(T)<sizeof(int),"only short or char");	//g++ std=c++11
	return a<b ? a:b;
}

namespace my_space
{
	class empty_class
	{
		BOOST_STATIC_ASSERT_MSG(sizeof(int)>=4,"for 32 bit");	//not accord,which meams when sizeof(int)<4,assert
	};
	BOOST_STATIC_ASSERT(sizeof(empty_class)==1);
}

BOOST_STATIC_ASSERT(2==sizeof(short));
BOOST_STATIC_ASSERT(true);

int main(int argc,char* argv[],char* envp[])
{
	cout<<my_min((short)1,(short)3);
	//cout<<my_min(1L,3L);	//will assert
}

