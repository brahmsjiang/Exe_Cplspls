/*************************************************************************
    > File Name: Base.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月19日 星期五 14时21分06秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Base{
public:
	Base():i(0),j(0){

	}
	virtual void print(){
	}
	virtual void setnum(int ii){
		i=ii;
	}
int i,j;
};



class Derived:public Base{
public:
	virtual void setnum(int ii,int jj){
		//static_cast<Base>(*this).setnum(ii);	//static_cast return a copy
		Base::setnum(ii);
		j=jj;
	}
};

