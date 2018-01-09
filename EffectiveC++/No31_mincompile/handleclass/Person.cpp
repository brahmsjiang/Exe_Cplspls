#include "Person.h"
#include "PersonImpl.h"

Person::Person(const std::string& name)
	:pImpl(new PersonImpl(name))
{

}

std::string Person::name() const
{
	return pImpl->name();
}
