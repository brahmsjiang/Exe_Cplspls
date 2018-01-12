/*************************************************************************
    > File Name: shape.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月12日 星期五 16时02分08秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

class shape{
public:
	virtual void draw() const=0;
	virtual void error(const std::string& msg){

	}
	int objID() const{
		return m_id;
	}
private:
	int m_id;

};

class ellipse:public shape{

};

class rectangle:public shape{

};
