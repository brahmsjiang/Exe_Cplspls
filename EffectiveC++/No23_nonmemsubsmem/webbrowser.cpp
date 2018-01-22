/*************************************************************************
    > File Name: webbrowser.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 10时55分50秒
 ************************************************************************/

#include<iostream>
#include "webbrowser.h"

using namespace std;
using namespace WebBrowserStuff;

void WebBrowser::clearCache()
{
	cout<<"webbroser clearcache"<<endl;
}
void WebBrowser::clearHistory()
{
	cout<<"webbroser clearhistory"<<endl;
}
void WebBrowser::clearBookmarks()
{
	cout<<"webbroser clearbookmarks"<<endl;
}
void WebBrowser::clearCookies()
{
	cout<<"webbroser clearcookies"<<endl;
}

void clearBrowser(WebBrowser& wb)
{
	wb.clearCache();
	wb.clearHistory();
	wb.clearBookmarks();
	wb.clearCookies();
}
