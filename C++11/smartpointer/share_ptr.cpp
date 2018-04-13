
#include <memory>
#include <iostream>

using namespace std;


void DeleteIntPtr(int* p)
{
	cout<<"call DeleteIntPtr"<<endl;
	delete p;
}

int main(int argc,char* argv[],char* envp[])
{
	//std::shared_ptr<int> p0(new int(11), DeleteIntPtr);
	std::shared_ptr<int> p0(new int(11), [](int* p){
			cout<<"call lambda delete"<<endl;
			delete p;
			});
	std::shared_ptr<int> p1=p0;
	std::shared_ptr<int> p2(p1);
	cout<<p2.use_count()<<endl;
	return 0;
}
