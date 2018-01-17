#include <iostream>
#include <string>
#include <functional>
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
	void sethealthfunc(healthcalfunc hcf){
		healthfunc=hcf;
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
	explicit badguy(healthcalfunc hcf=default_health, int rawval=100, std::string str="")
		:character2(hcf,rawval),//子类的构造函数中，加上一个冒号(:)，然后加上父类的带参构造函数，这就是父类构造函数的显式调用
		sname(str)
	{
	}
	string& getname(){
		return sname;
	}
private:
	std::string sname;

};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class character3;	//statment for below func statement
//at this position, default_health can only statement and cannot be defined becasue compiler think character2's define is not complete for it is used as a parmeter(quote and pointer is the same)
//==================>invalid use of incomplete type 
int default_health1(const character3& gc);
class character3
{
public:
	typedef std::function<int (const character3&)> healthcalfunc;
	explicit character3(healthcalfunc hcf=default_health1, int rawval=100)
		:healthfunc(hcf),
		rawhealthval(rawval)
	{
	}
	int getrawhealthval() const{
		return rawhealthval;
	}
	int healthval() const{
		return healthfunc(*this);
	}
	void sethealthfunc(healthcalfunc hcf){
		healthfunc=hcf;
	}
private:
	int rawhealthval;
	healthcalfunc healthfunc;
};

int default_health1(const character3& gc){
	gc.getrawhealthval();
}


class evilbadguy:public character3{
public:
	explicit evilbadguy(healthcalfunc hcf=default_health1, int rawval=100, std::string str="")
		:character3(hcf,rawval),
		sname(str)
	{
	}
	string& getname(){
		return sname;
	}
private:
	std::string sname;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class character4;
class healthcal{
public:
	virtual int calc(const character4&) const=0;
};


class character4{
public:
	explicit character4(healthcal* phc, int rawval=100)//defaut par must initialize from right side
		:ptr_hc(phc),
		rawhealthval(rawval)
	{

	}
	int getrawhealthval() const{	//must const,  const obj can only call const func as defalut_health=======>passing ‘const *’ as ‘this’ argument of ‘*’ discards qualifiers
		return rawhealthval;
	}
	int healthval() const{
		return ptr_hc->calc(*this);
	}
	void sethealthfunc(healthcal* phc){
		ptr_hc=phc;
	}
	virtual string& getname(){
		string aa;
		return aa;
	}
private:
	int rawhealthval;
	healthcal* ptr_hc;
};

class char4_guy0:public character4{
public:
	explicit char4_guy0(healthcal* phc=NULL, int rawval=100, std::string str="")
		:character4(phc,rawval),
		sname(str)
	{
	}
	string& getname(){
		return sname;
	}
private:
	std::string sname;

};

class badguy_healthcal:public healthcal{
public:
	virtual int calc(const character4& gc) const{
		return gc.getrawhealthval()*1.5;
	}
};

class candyguy_healthcal:public healthcal{
public:
	virtual int calc(const character4& gc) const{
		return gc.getrawhealthval()*0.7;
	}
};
