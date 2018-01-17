/*************************************************************************
    > File Name: timer.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月15日 星期一 14时03分28秒
 ************************************************************************/

#include<iostream>
using namespace std;

class timer
{
public:
	virtual void ontick();

};

class widgettimer:public timer{
public:
	virtual void ontick();

};
