#include <iostream>
#include "widget.h"

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

int main(int argc, char* argv[])
{
	person p;
	student s;
	eat(p);
	//eat(s);//err	private and protected inherit is not is-a relationship, so student obj is not person obj; and father* fp=new chd(); is also err, although childfunc can overwrite fatherfunc
	//study(p);//err  father cannot convert child
	study(s);
	//////////////////////////
	widget* dd=new spwidget();
	dd->gettimer().ontick();

	widget ddd;
	ddd.gettimer().ontick();

	spwidget dddd;
	dddd.ontick();
	//////////////////////////
	A a;a.printA();
	AA aa;aa.callprintA();	

	A* ap=new AA();
	ap->callprintA();
	return 0;
}
