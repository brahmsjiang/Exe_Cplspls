
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
using namespace std;

const int minpasswd = 6;

class myexp:public exception
{
public:
	virtual const char* what() const throw()	//tell user thisfunc will throw exception
	{
		return "myexp happened";
	}
}myex;

std::string encryptPswd(const std::string& pswd)
{
	if(pswd.length() < minpasswd){
		throw logic_error("encrpt err");
	}
	std::string tmp(pswd);
	tmp+="xxxxx";
	return tmp;
}

void try_catch()
{
	try{
		if(true)
			throw myex;
	}
	catch(myexp& ex){
		cout<<__LINE__<<" "<<ex.what()<<endl;
	}
	try{
		std::string str("err");
		if(true)
			throw str;
	}
	catch(const std::string& str){
		cout<<__LINE__<<" "<<str<<endl;
	}
	try{
		//int a=1/0; 
	}
	catch(...){
		//cout<<__LINE__<<" "<<ex.what()<<endl;
		cout<<__LINE__<<endl;
	}

}
int main()
{
	try{
		std::string pswd1("1234");
		cout<<"encrypted pswd: "<<encryptPswd(pswd1)<<endl;
	}
	catch(myexp& ex){
		cout<<__LINE__<<" "<<ex.what()<<endl;
		cout<<"myexception is catched"<<endl;
	}
	
	return 0;
}

