#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
public:
	virtual ~Person(){

	}
	virtual std::string name() const=0;
	static Person* create(const std::string& name);
};

#endif
