
#include <boost/version.hpp>
#include <boost/config.hpp>
#include <iostream>

using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	cout<<BOOST_VERSION<<endl;
	cout<<BOOST_LIB_VERSION<<endl;
	cout<<BOOST_PLATFORM<<endl;
	cout<<BOOST_COMPILER<<endl;
	cout<<BOOST_STDLIB<<endl;
}
