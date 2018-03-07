/*************************************************************************
    > File Name: db_Object.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月28日 星期三 11时46分32秒
 ************************************************************************/

#include<iostream>
#include "object.h"
using namespace std;

static const char sig_names[]="sig1/n";
static const char slts_names[]="slot1/n";
MetaObject Object::meta = {signames,slts_names};

void Object::sig1()
{
	MetaObject::active(this,0);
}

void Object::metacall(int idx)
{
	switch(idx){
		case 0:
			slot1();
			break;
		default:
			break;
	};
}

