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
	void draw(shapecolor col=Red) const{
		dodraw(col);
	}
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
private:
	virtual void dodraw(shapecolor col) const=0;
};

class rectangle:public shape{
private:
	virtual void dodraw(shapecolor col) const{
		cout<<"rectangle::draw "<<retcol(col)<<endl;
	}
};

class circle:public shape{
private:
	virtual void dodraw(shapecolor col) const{	//when user call draw,para have to be set
		cout<<"circle::draw "<<retcol(col)<<endl;
	}
};

int main()
{
	rectangle rec;
	rec.draw();

	circle cir;
	shape* ptr=&cir;
	ptr->draw();
	
	return 0;
}
