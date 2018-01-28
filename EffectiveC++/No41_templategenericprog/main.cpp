#include <algorithm>	//swap
#include <iostream>
#include <string>

using namespace std;

class Widget
{
public:
	Widget(std::string name="default", std::size_t size=0)
		:sname(name), ssize(size)
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

//class someNastyWidget;
Widget someNastyWidget;


template<typename T>
void doProcessing(T& w)
{
	if (w.size() > 10 && w != someNastyWidget) {
		T temp(w);
		temp.normalize();
		temp.swap(w);
	}
}


class someNastyWidget
{

};

int main()
{
	Widget wg0("fuck",20);
	doProcessing(wg0);
	wg0.print();	
	Widget wg1("fuck",2);
	doProcessing(wg1);
	wg1.print();	


	return 0;
}
