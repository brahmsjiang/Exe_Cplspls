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
	//param�Ǹ�ָ������ã���������������
	int x = 27;//x�ͱ���int
	const int cx = x;//cx�ͱ���const int
	const int& rx = x;//rx�ͱ���const int&

	/////////////////////////////////////////////////////
	f1(x);//T�ͱ���int��param�ͱ���int&
	f1(cx);//T�ͱ���const int��param�ͱ���const int&
	f1(rx);//T�ͱ���const int(T���������Ƶ������б�����)��param�ͱ���const int&

	f2(x);//T�ͱ���int��param�ͱ���const int&
	f2(cx);//T�ͱ���int(T���������Ƶ������б����ԣ���Ȼparam��const��T��constҲ�������ˣ���param�ͱ���const int&
	f2(rx);//T�ͱ���int��param�ͱ���const int&

	const int* px = &x;//px�ͱ���const int*
	f3(&x);//T�ͱ���int��param�ͱ���int*
	f3(px);//T�ͱ���const int(Tָ���Ա����ԣ�const�������ˣ���param�ͱ���const int*
	
	/////////////////////////////////////////////////////
	f4(x);//x����ֵ(expr��ֵ��T��param���ᱻ�Ƶ�Ϊ��ֵ����)��T�ͱ���int&��param�ͱ���int&
	f4(cx);//cx����ֵ��T�ͱ���const int&��param�ͱ���const int&
	f4(rx);//rx����ֵ��T�ͱ���const int&��param�ͱ���const int&
	f4(27);//27����ֵ��ʹ�ó�����򣩣�T�ͱ���int��param�ͱ���int&&

	/////////////////////////////////////////////////////
	f5(x);//T�ͱ���int��param�ͱ�int
	f5(cx);//T�ͱ���int(expr��const��volatile���ֱ����ԣ���param�ͱ�int
	f5(rx);//T�ͱ���int(expr��const�������ͱ𱻺��ԣ���param�ͱ�int

	return 0;
}