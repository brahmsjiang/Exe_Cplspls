
#include <iostream>
#include <string>

const int minpasswd = 6;

using namespace std;

std::string encryptPswd(const std::string& pswd)
{
	if(pswd.length() < minpasswd){
		throw logic_error("passwd is too short");
	}	
}

int main()
{
	std::string pswd1("12345");
	encryptPswd(pswd1);
	
	return 0;
}
