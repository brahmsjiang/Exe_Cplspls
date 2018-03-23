
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_unique.hpp>
#include <iostream>

using namespace boost;
using namespace std;

int main(int argc,char* argv[],char* envp[])
{
	int* arr=new int[100];
	scoped_array<int> sa(arr);
	fill_n(&sa[0],100,5);
	fill(&sa[0],&sa[4],10);
	//*sa=1;	//compile err
	//*(sa+1)=2;	//compile err
	sa[20]=3;
	sa[10]=sa[20]+sa[30];
	for(int i=0;i<100;++i)
		cout<<sa[i]<<" ";
	cout<<endl;

	unique_ptr<int[]> up(new int[10]);
	assert(up);
	cout<<up[0]<<endl;
	up.reset();
	assert(!up);
	//cout<<up[0]<<endl;	//dump
	
	auto a=boost::make_unique<int[]>(5);
	a[0]=100;
	a[4]=500;
	//a[5]=700;	//undefined behavior
	//for(auto i : a)
	//	cout<<i;	//compile err,because std::unique_ptr<int []>’ has no member named ‘end’
	int aa[10]={0};
	for(auto i : aa)
		cout<<i<<" ";
	cout<<endl;

	return 0;
}
