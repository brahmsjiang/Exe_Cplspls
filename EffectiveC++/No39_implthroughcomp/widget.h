
#include <iostream>

using namespace std;


class timer{
	virtual void ontick() const{
		cout<<"on tick!"<<endl;
	}
};

class widget{
private:
	class widgettimer:public timer{
	public:
		virtual void ontick() const{
			cout<<"on widget tick!!"<<endl;
		}
	};
	widgettimer* mtimer;
public:
	widget():mtimer(new widgettimer()){}
	widgettimer& gettimer(){
		return *mtimer;
	}
};


class spwidget:public widget{
public:
	virtual void ontick() const{
		cout<<"on spwidget tick!!"<<endl;
	};

};


class A{
public:
	virtual void callprintA(){
		printA();
	}
	virtual void printA(){
		cout<<"printA"<<endl;
	}
};

class AA:private A{
public:
	virtual void callprintA(){
		printA();
	}
private:
	virtual void printA(){
		cout<<"printAA"<<endl;
	}
};


