#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>

//default is private inherit
class do_not_copy:boost::noncopyable
{


};


int main(int argc,char* argv[],char* envp[])
{
	do_not_copy d1;
	//do_not_copy d2(d1);
	do_not_copy d3;
	//d3=d1;
	return 0;
}
