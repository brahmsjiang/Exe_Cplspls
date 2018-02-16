
#include <iostream>
#include <memory>


using namespace std;

class widget
{
public:
	widget(){
		cout<<"widget cons"<<endl;
	}
	void show(){
		cout<<"widget is showing"<<endl;
	}
	~widget()
	{
		cout<<"widget des"<<endl;
	}
};

int priority()
{
//	throw 1;
	return 0;
}

void processwidget(std::shared_ptr<widget> pw, int priority)
{
	pw->show();
	cout<<"priority is: "<<priority<<endl;
}

int main()
{
	//processwidget(new widget, priority());	//compile err,shared_ptr constructor is explict
//	processwidget(std::shared_ptr<widget>(new widget), priority());

	std::shared_ptr<widget> pw(new widget);
	processwidget(pw, priority());

	return 0;
}
