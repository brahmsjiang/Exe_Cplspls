#include <iostream>
#include <string>
using namespace std;

class chara{
public:
	virtual int healthval() const;
};

class character1{
public:
	int healthval() const{
		cout<<"call healtval for NVI===>";
		int retval=dohealthval();
		return retval;
	}
private:
	virtual int dohealthval() const{
		cout<<"call character1::dohealthval"<<endl;
	}
};

class beggar1:public character1{
	virtual int dohealthval() const{
		cout<<"call beggar1::dohealthval"<<endl;
	}

};
/////////////////////////////////////////////////////////

class character2;	//statment for below func statement
//at this position, default_health can only statement and cannot be defined becasue compiler think character2's define is not complete for it is used as a parmeter(quote and pointer is the same)
//==================>invalid use of incomplete type 
int default_health(const character2& gc);

class character2{
public:
	typedef int (*healthcalfunc) (const character2&);
	explicit character2(healthcalfunc hcf=default_health, int rawval=100)//defaut par must initialize from right side
		:healthfunc(hcf),
		rawhealthval(rawval)
	{

	}
	int getrawhealthval() const{	//must const,  const obj can only call const func as defalut_health=======>passing ‘const *’ as ‘this’ argument of ‘*’ discards qualifiers
		return rawhealthval;
	}
	int healthval() const{
		return healthfunc(*this);
	}
private:
	int rawhealthval;
	healthcalfunc healthfunc;
};


int default_health(const character2& gc){
	gc.getrawhealthval();
}

class badguy:public character2{
public:
	explicit badguy(std::string str="", healthcalfunc hcf=default_health, int rawval=100)
		:character2(hcf,rawval)//子类fish的构造函数中，加上一个冒号(:)，然后加上父类的带参构造函数，这就是父类构造函数的显式调用
	{
		sname(str);
	}
	string& getname(){
		return sname;
	}
private:
	std::string sname;

};


class test{
public:
	test(string str=""):
		sname(str){

		}
	void print(){
		cout<<sname<<endl;
	}
private:
	string sname;
};









