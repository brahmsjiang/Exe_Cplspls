/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 09时56分55秒
 ************************************************************************/

#include<iostream>
#include "webbrowser.h"
//#include "webbrowserbookmarks.h"
#include "webbrowsercookies.h"

using namespace std;
using namespace WebBrowserStuff;

int main()
{

	WebBrowser wbs;
	::clear_Cookies(&wbs);

	return 0;
}


