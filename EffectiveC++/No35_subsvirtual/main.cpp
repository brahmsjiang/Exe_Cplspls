#include <iostream>
#include "chara.h"

using namespace std;

int main(int argc, char* argv[])
{
	character1* cp=new beggar1();
	cp->healthval();
	
	cp=new character1();
	cp->healthval();
	//////////////////////////////////////////////
	
	return 0;
}
