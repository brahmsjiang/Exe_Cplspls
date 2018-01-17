#include <iostream>
#include "widget.h"
//#pragma pack(1)

using namespace std;
class person{

};
class student:private person{
	operator person(){

	};

};
void eat(const person& p){

};
void study(const student& s){

};

class empty{

};

class holdaint1{
private:
	int x;
	empty obj;
};

class holdaint2:private empty{
private:
	int x;
};

int main(int argc, char* argv[])
{
	person p;
	student s;
	eat(p);
	//eat(s);//err	private and protected inherit is not is-a relationship, so student obj is not person obj; and father* fp=new chd(); is also err, although childfunc can overwrite fatherfunc
	//study(p);//err  father cannot convert child
	study(s);
	//////////////////////////
	widget* dd=new widget();
	dd->timertick();

//	widget ddd;
//	ddd.gettimer().ontick();

	cout<<"sizeof(int): "<<sizeof(int)<<endl;
	cout<<"sizeof(empty): "<<sizeof(empty)<<endl;
	cout<<"sizeof(holdaint1): "<<sizeof(holdaint1)<<endl;
	cout<<"sizeof(holdaint2): "<<sizeof(holdaint2)<<endl;
	return 0;
}
