#include <iostream>
using namespace std;


class B{
public:
	void mf(){	//nonvirtual and D defined==>BD; nonvirtual and D nodefined==>BB;virtual==>DD
		cout<<"call B:mf"<<endl;
	}
};

class D:public B{
public:
	void mf(){
		cout<<"call D:mf"<<endl;
	}
};

int main()
{
	D x;
	B* pb=&x;
	D* pd=&x;
	pb->mf();
	pd->mf();
	cout<<"==============="<<endl;	
	B b;b.mf();
	D d;d.mf();

	return 0;
}
