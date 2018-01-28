/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年01月22日 星期一 15时46分54秒
 ************************************************************************/

#include<iostream>
using namespace std;

class rational
{
public:
	rational(int num=0, int deno=1)
		:m_num(num),m_deno(deno){}
	int retnum() const{
		return m_num;
	}
	int retdeno() const{
		return m_deno;
	}
#if 0
	const rational operator*(const rational& rhs){
		cout<<"call inner *"<<endl;
		int tmp_num = this->m_num * rhs.m_num;
		int tmp_deno = this->m_deno * rhs.m_deno;
		return rational(tmp_num, tmp_deno);
	}
#endif
//	friend const rational operator*(const rational& lhs, const rational& rhs);
	void printr() const{
		cout<<m_num<<"/"<<m_deno<<endl;
	}
private:
	int m_num;
	int m_deno;
};


const rational operator*(const rational& lhs, const rational& rhs)
{
	cout<<"call outer *"<<endl;
	return rational(lhs.retnum()*rhs.retnum(), lhs.retdeno()*rhs.retdeno());
}
#if 0
const rational operator*(const rational& lhs, const rational& rhs)
{
	cout<<"call friend *"<<endl;
	return rational(lhs.m_num*rhs.m_num, lhs.m_deno*rhs.m_deno);
}
#endif

int main()
{
	rational res0 = rational(1,2) * 2;
	rational res00 = rational(7,9);
	rational res000 = res0 * res00; 
	res000.printr();
	rational res1 = 7 * rational(1,2);
	res1.printr();

	return 0;
}



