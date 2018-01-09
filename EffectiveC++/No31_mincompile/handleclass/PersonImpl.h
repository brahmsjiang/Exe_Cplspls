#include <string>
#include <memory>
#include <iostream>

using namespace std;

class PersonImpl{
public:
	PersonImpl(const std::string& name):sname(name){

	}
	std::string name() const{
		cout<<"!";
		return sname;
	}
private:
	std::string sname;
};
