#include "Person.h"

Person::Person(const std::string& name)
	:sname(name)
{

}

std::string Person::name() const
{
	return sname;
}
