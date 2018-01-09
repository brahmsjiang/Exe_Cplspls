#include "Person.h"
#include "RealPerson.h"

Person* Person::create(const std::string& name)
{
	return new RealPerson(name);
}
