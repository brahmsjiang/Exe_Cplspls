/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月12日 星期五 16时08分59秒
 ************************************************************************/

#include<iostream>
#include "shape.h"
#include "fly.h"
using namespace std;


int main(){
	airport port0("shanghai");
	kongke plane0("kongke_p0");
	boyin plane1("boyin_p1");
	plane0.fly(port0);
	plane1.fly(port0);
	return 0;
}

