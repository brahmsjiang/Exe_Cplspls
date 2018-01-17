/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月17日 星期三 16时52分30秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

class shape{
public:
	enum shapecolor{Red,Green,Blue};
	virtual void draw(shapecolor col=Red) const=0;
	std::string retcol(shapecolor col) const{
		std::string str;
		switch(col)
		{
			case Red:
				str="Red";break;
			case Green:
				str="Green";break;
			case Blue:
				str="Blue";break;
			default:
				break;
		}
		return str;
	}
};

class rectangle:public shape{
public:
	virtual void draw(shapecolor col=Green) const{
		cout<<"rectangle::draw "<<retcol(col)<<endl;
	}
};

class circle:public shape{
public:
	virtual void draw(shapecolor col) const{	//when user call draw,para have to be set
		cout<<"circle::draw "<<retcol(col)<<endl;
	}
};

int main()
{
	rectangle rec;
	rec.draw();
	circle cir;
	cir.draw(shape::Blue);	//err

	shape* ptr=new rectangle();
	ptr->draw();
	shape* ptr1=new circle();
	ptr1->draw();

	//////////////////////////////////
	return 0;
}
