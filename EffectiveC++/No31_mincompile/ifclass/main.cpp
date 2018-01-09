#include <iostream>
#include "Person.h"

using namespace std;

int main(int argc, char* argv[])
{
	Person* pp = Person::create("ppp~");
	cout<<pp->name()<<endl;
	return 0;
}
