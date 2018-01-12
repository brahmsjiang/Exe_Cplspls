/*************************************************************************
    > File Name: fly.h
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月12日 星期五 16时13分00秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

class airport{
public:
	airport(const std::string& name):
		sname(name)
	{}
	const std::string& name() const{	//const func must return const quote,see csdn collection article 
		return sname;
	}
private:
	std::string sname;
};

class airplane{
public:
	airplane(const std::string& name):
		sname(name)
	{}
	const std::string& name() const{
		return sname;
	}
	virtual void fly(const airport& dest)=0;
	
private:
	std::string sname;
};

void airplane::fly(const airport& dest)
{
	cout<<this->name()<<" fly to "<<dest.name()<<endl;
}

class boyin:public airplane{
public:
	boyin(const std::string& name):airplane(name)
	{
	}
	virtual void fly(const airport& dest)
	{
		airplane::fly(dest);
	}

};

class kongke:public airplane{
public:
	kongke(const std::string& name):airplane(name)
	{

	}
	virtual void fly(const airport& dest)
	{
		cout<<this->name()<<" fly to "<<dest.name()<<endl;
	}
};
