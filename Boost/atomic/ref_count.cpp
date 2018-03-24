
#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>
#include <iostream>

using namespace std;
using namespace boost;

template<typename T>
class ref_count
{
private:
	typedef boost::atomic<int> atomic_type;
	mutable atomic_type m_count{0};
protected:
	ref_count(){}
	~ref_count(){}
public:
	

};





int main(int argc,char* argv[],char* envp[])
{
	return 0;
}
