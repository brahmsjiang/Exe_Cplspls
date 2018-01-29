#include <algorithm>	//swap
#include <iostream>
#include <string>
#define someNastyWidget 128
using namespace std;

struct Mem
{
	Mem(int num)
		:mmem(num){}
	int mmem;
};


class Widget
{
public:
	Widget(std::string name="default", std::size_t size=0)
		:sname(name), ssize(size)
	{

	}
	Widget(std::size_t size=0)
		:sname("default"), ssize(size)
	{

	}
	virtual ~Widget(){

	}
	void print() const{
		cout<<"sname: "<<sname<<"	ssize:"<<ssize<<endl;
	}
	std::size_t size() const{
		return ssize;
	}
	virtual void normalize(){
		sname="===="+sname+"===";
		ssize/=ssize;
	}
	void swap(Widget& other){
		std::swap(this->sname, other.sname);
		std::swap(this->ssize, other.ssize);
	}
	bool operator!=(const Widget other) const{
		return (this->sname != other.sname);
	}
private:
	std::string sname;
	std::size_t ssize;
};

class WidgetSp
{
public:
	WidgetSp(std::string name="default", const Mem& Memobj=Mem(0))
		:sname(name), smem(Memobj)
	{

	}
	WidgetSp(const Mem& Memobj=Mem(0))
		:sname("default"), smem(Memobj)
	{

	}
	WidgetSp(int num)
		:sname("default"), smem(Mem(num))	//it only canbe convert once, int->Mem->WidgerSp is prohibit
	{

	}
	virtual ~WidgetSp(){

	}
	void print() const{
		cout<<"sname: "<<sname<<"	ssize:"<<smem.mmem<<endl;
	}
	const Mem& size() const{
		return smem;
	}
	virtual void normalize(){
		sname="===="+sname+"===";
		smem.mmem/=smem.mmem;
	}
	void swap(WidgetSp& other){
		std::swap(this->sname, other.sname);
		std::swap(this->smem.mmem, other.smem.mmem);
	}

private:
	std::string sname;
	Mem smem;

};



//Widget someNastyWidget;
//WidgetSp someNastyWidget;



template<typename T>
void doProcessing(T& w)
{
	if (w.size() > 10 && w != someNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}

bool operator>(const Mem& lhs, const Mem& rhs)
{
	return (lhs.mmem > rhs.mmem);
}

bool operator!=(const WidgetSp& lhs, const WidgetSp& rhs){
	return true;
}


int main()
{

	Widget wg0("fffff",20);
	doProcessing(wg0);
	wg0.print();	
	Widget wg1("fffff",2);
	doProcessing(wg1);
	wg1.print();

	cout<<"------------"<<endl;
	WidgetSp wgs0("shit",3);
	doProcessing(wgs0);
	wgs0.print();
	WidgetSp wgs1("shit",13);
	doProcessing(wgs1);
	wgs1.print();

	return 0;
}

