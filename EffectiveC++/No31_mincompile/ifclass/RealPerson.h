#include <iostream>
#include "Person.h"
#include "string"

using namespace std;

class RealPerson:public Person
{
public:
	RealPerson(const std::string& name):sname(name){

	}
	virtual ~RealPerson(){

	}
	std::string name() const
	{
		cout<<"name is::";
		return sname;
	}
private:
	std::string sname;
};
