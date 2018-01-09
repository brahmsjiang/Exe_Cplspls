#include <iostream>
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

class character2;
int default_health(const character2& gc){
	return gc.getrawhealthval();
}

class character2{
public:
	typedef int (*healthcalfunc) (const character2&);
	explicit character2(healthcalfunc hcf=default_health, int rawval)
		:healthfunc(hcf),
		rawhealthval(rawval)
		
	{

	}
	int getrawhealthval(){
		return rawhealthval;
	}
	int healthval() const{
		return healthfunc(*this);
	}
private:
	int rawhealthval;
	healthcalfunc healthfunc;
};

