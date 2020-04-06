#include <iostream>

using namespace std;

template<typename T>
void f1(T& param){}

template<typename T>
void f2(const T& param){}

template<typename T>
void f3(T* param){}

template<typename T>
void f4(T&& param){}

template<typename T>
void f5(T param){}

int main(int argc, char* argv[])
{
	//param是个指针或引用，但不是万能引用
	int x = 27;//x型别是int
	const int cx = x;//cx型别是const int
	const int& rx = x;//rx型别是const int&

	/////////////////////////////////////////////////////
	f1(x);//T型别是int，param型别是int&
	f1(cx);//T型别是const int，param型别是const int&
	f1(rx);//T型别是const int(T引用性在推导过程中被忽略)，param型别是const int&

	f2(x);//T型别是int，param型别是const int&
	f2(cx);//T型别是int(T引用性在推导过程中被忽略；既然param有const，T的const也被忽略了），param型别是const int&
	f2(rx);//T型别是int，param型别是const int&

	const int* px = &x;//px型别是const int*
	f3(&x);//T型别是int，param型别是int*
	f3(px);//T型别是const int(T指针性被忽略，const被保留了），param型别是const int*
	
	/////////////////////////////////////////////////////
	f4(x);//x是左值(expr左值，T和param都会被推导为左值引用)，T型别是int&，param型别是int&
	f4(cx);//cx是左值，T型别是const int&，param型别是const int&
	f4(rx);//rx是左值，T型别是const int&，param型别是const int&
	f4(27);//27是右值（使用常规规则），T型别是int，param型别是int&&

	/////////////////////////////////////////////////////
	f5(x);//T型别是int，param型别int
	f5(cx);//T型别是int(expr的const、volatile部分被忽略），param型别int
	f5(rx);//T型别是int(expr的const、引用型别被忽略），param型别int

	return 0;
}