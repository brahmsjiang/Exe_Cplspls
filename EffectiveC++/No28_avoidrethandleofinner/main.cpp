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

class point
{
public:
	point(int xx=0,int yy=0)
		:x(xx),y(yy)
	{}
	void setx(int xx){
		x=xx;
	}
	void sety(int yy){
		y=yy;
	}
	void printp(){
		cout<<"x: "<<x<<"	y: "<<y<<endl;
	}
private:
	int x,y;
};

struct rectdata
{
	rectdata(const point& l=point(1,1), const point& r=point(0,0))
		:leftup(l)
		 ,rightdown(r){}
	rectdata(const rectdata& rd=rectdata())
		:leftup(rd.leftup)
		 ,rightdown(rd.rightdown){}
	point leftup;
	point rightdown;
};

class rect
{
public:
	typedef std::shared_ptr<rectdata> PRD;
	explicit rect(const rectdata& rd=rectdata())
		:dptr(&rd){
			cout<<"create rect"<<endl;
		}
	point& retleftup() const{
		return dptr->leftup;
	}
	point& retrightdown() const{
		return dptr->rightdown;
	}
private:
	PRD dptr;
};




int main()
{
	rect rect0;
	cout<<"lu: ";rect0.retleftup().printp();
	cout<<"rd: ";rect0.retrightdown().printp();
	
	rect(new rectdata(point(0,0),point(100,100)));
	
	return 0;
}
