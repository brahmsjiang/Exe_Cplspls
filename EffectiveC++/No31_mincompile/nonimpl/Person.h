#include <string>
#include <memory>
#include <iostream>

using namespace std;

class Person{
public:
	Person(const std::string& name);
	std::string name() const;
private:
	std::string sname;
};
