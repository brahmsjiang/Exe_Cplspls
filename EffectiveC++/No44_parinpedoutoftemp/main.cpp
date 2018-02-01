/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月01日 星期四 20时53分56秒
 ************************************************************************/

#include<iostream>
#include<typeinfo>

using namespace std;

template<typename T, std::size_t n>
class SquareMatrix_r
{
public:
	void invert(){
		cout<<"SquareMatix_r<"<<typeid(T).name()<<">"<<n<<"==>invert!"<<endl;
	}

};

template<typename T>
class SquareMatrixBase
{
protected:
	SquareMatrixBase(std::size_t n, T* pMem)
		:size(n),pData(pMem){}
	void invert(std::size_t n){
		cout<<"SquareMatix<"<<typeid(T).name()<<">"<<n<<"==>invert!"<<endl;
	}
private:
	std::size_t size;
	T* pData;
};

template<typename T, std::size_t n>
class SquareMatrix:private SquareMatrixBase<T>	//private inherit
{
private:
	using SquareMatrixBase<T>::invert;
public:
	void invert(){
		this->invert(n);
	}
};

int main()
{
	SquareMatrix_r<double,5> smr0;
	smr0.invert();
	SquareMatrix_r<double,10> smr1;
	smr1.invert();

	return 0;
}

