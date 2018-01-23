
#include <iostream>
#include "webbrowser.h"
#include "webbrowsercookies.h"


using namespace std;

namespace WebBrowserStuff{


void clear_Cookies(WebBrowser& wb)
{
	wb.clearCookies();
}


}
