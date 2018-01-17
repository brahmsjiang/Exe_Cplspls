
#include <iostream>

using namespace std;



class widgettimer;		

class widget{
private:
	widgettimer* mtimer;
public:
	widget();
	widgettimer* gettimer();
	void timertick();
};






