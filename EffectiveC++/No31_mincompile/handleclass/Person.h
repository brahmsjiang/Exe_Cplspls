#include <string>
#include <memory>

class PersonImpl;

class Person{
public:
	Person(const std::string& name);
	std::string name() const;
private:
	PersonImpl* pImpl;
};
