/*************************************************************************
    > File Name: widget.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月15日 星期一 15时48分21秒
 ************************************************************************/

#include<iostream>
#include"timer.h"
#include"widget.h"

using namespace std;

widget::widget()
	:mtimer(new widgettimer())
{

}

widgettimer* widget::gettimer()
{
	return mtimer;
}

void widget::timertick()
{
	mtimer->ontick();
}

void timer::ontick()
{
	cout<<"on tick!!!!"<<endl;
}

void widgettimer::ontick()
{
	cout<<"on widgetdddd !!!!"<<endl;
}
