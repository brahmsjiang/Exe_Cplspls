/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月28日 星期三 11时42分24秒
 ************************************************************************/

#include<iostream>
#include"object.h"

using namespace std;

int main()
{
	Object obj1,obj2;
	Object::db_connect(&obj1,"sig1",&obj2,"slot2");
	obj1.testSignal();
	return 0;
}
