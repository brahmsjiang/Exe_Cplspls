
#include <iostream>
#include <string>

using namespace std;

enum SearchDir{
	FORWARD,
	BACKWARD,
};
enum CaseSen{
	CASE_SENSITVE,
	CASE_INSENTIVE,
};

std::string FindString0(const std::string& text,bool search_forward,bool case_sensitive)
{
	string tmp;
	return tmp;
}

std::string FindString1(const std::string& text,SearchDir search_forward,CaseSen case_sensitive)
{
	cout<<"1st par: "<<search_forward<<endl;
	cout<<"2nd par: "<<case_sensitive<<endl;
	string tmp;
	return tmp;
}

std::string FindString2(const std::string& text,int search_forward,int case_sensitive)
{
	string tmp;
	return tmp;
}


int main(int argc,char* argv[],char* envp[])
{
	//enum can conver to int or bool automatically, but int/bool cannot convert to enum in case of convert forcely
	string text("fuck");
	FindString0(text,true,false);
	FindString0(text,false,true);
	FindString0(text,FORWARD,CASE_INSENTIVE);
	

	FindString1(text,FORWARD,CASE_INSENTIVE);
	//FindString1(text,false,true);	//err
	//FindString1(text,CASE_INSENTIVE,FORWARD);	//err
	
	
	FindString2(text,FORWARD,CASE_INSENTIVE);
	FindString2(text,CASE_INSENTIVE,FORWARD);
	FindString2(text,0,1);
	FindString2(text,1,0);
	return 0;
}
