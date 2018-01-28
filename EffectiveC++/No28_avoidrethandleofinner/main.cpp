/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月19日 星期五 20时11分41秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<memory>
using namespace std;

void spaceline()
{
	cout<<"=============="<<endl;
}
class point
{
public:
	point(int xx=0,int yy=0)
		:x(xx),y(yy)
	{
		cout<<"point cons"<<endl;
	}
	point(const point& pt)	//可访问性是相对于类型来说的，而不是实例
		:x(pt.x),y(pt.y)
	{
		cout<<"point copy"<<endl;
	}
	point& operator=(const point& pt)	//default复制构造函数将来源对象的每一个非static成员拷贝到目标对象
	{
		cout<<"point operator="<<endl;
		this->x=pt.x;
		this->y=pt.y;
		return *this;
	}
	~point()
	{
		cout<<"~point"<<endl;
	}
	void setx(int xx){
		x=xx;
	}
	void sety(int yy){
		y=yy;
	}
	void printp() const{
		cout<<"x: "<<x<<"	y: "<<y<<endl;
	}
private:
	int x,y;
};
class rectdata
{
public:
	rectdata(const point& l=point(9,9), const point& r=point(12,12))
		:leftup(l),rightdown(r)
	{
		cout<<"rectdata cons"<<endl;	 
	}
	rectdata(const rectdata& rd)
		:leftup(rd.leftup),rightdown(rd.rightdown)
	{
		 cout<<"rectdata copy"<<endl;
	}
	rectdata& operator=(const rectdata& rd)
	{
		cout<<"rectdata operator="<<endl;
		this->leftup=rd.leftup;
		this->rightdown=rd.rightdown;
		return *this;
	}
	~rectdata()
	{
		cout<<"~rectdata"<<endl;
	}
	point leftup;
	point rightdown;
};

class rect
{
public:
	typedef std::shared_ptr<rectdata> PRD;
	explicit rect(rectdata* rd=new rectdata())
		:dptr(rd)
	{
		cout<<"rect cons"<<endl;
	}
	rect(const rect& re)
		:dptr(new rectdata(*re.dptr))	//deap copy
	//	:dptr(re.dptr)	//shallow copy
	{
			
		cout<<"rect copy"<<endl;

	}
	const point& retleftup() const{
		return dptr->leftup;
	}
	const point& retrightdown() const{
		return dptr->rightdown;
	}
	~rect()
	{
		//cout<<"~rect"<<endl;
		//delete dptr;
	}

public:
	PRD dptr;
	//rectdata* dptr;
};

const rect boundbox()
{
	rect temp;
	return temp;
}

int main()
{
	rect* ptr=new rect(new rectdata());
	rect rect1(*ptr);
	cout<<"ptr addr: "<<(*ptr).dptr<<endl;
	cout<<"rect1 addr: "<<rect1.dptr<<endl;

	cout<<"lu: ";rect1.retleftup().printp();
	cout<<"rd: ";rect1.retrightdown().printp();
	delete ptr;ptr=NULL;	
	cout<<"lu: ";rect1.retleftup().printp();
	cout<<"rd: ";rect1.retrightdown().printp();
	//rect1.retleftup().setx(1000);	//err,retleftup is const
		
	spaceline();	
	const point* pgo=&(boundbox().retleftup());	//ret handle is null when this statement is end,the obj will destory
	pgo->printp();
		
	spaceline();	
	return 0;
}






