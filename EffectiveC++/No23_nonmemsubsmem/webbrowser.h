/*************************************************************************
    > File Name: webbrowser.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 10时01分20秒
 ************************************************************************/
#ifndef WEBB
#define WEBB

#include<iostream>
using namespace std;

namespace WebBrowserStuff{
class WebBrowser
{
public:
	void clearCache();
	void clearHistory();
	void clearBookmarks();
	void clearCookies();
};

void clearBrowser(WebBrowser& wb);

}

#endif
