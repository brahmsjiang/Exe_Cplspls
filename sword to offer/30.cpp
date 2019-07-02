#include<iostream>
#include<memory>
#include<stack>

using namespace std;

template<typename T> class StackWithMin;

template <typename T>
void StackWithMin::push(const T& value)
{

}

template <typename T>
void StackWithMin::pop()
{

}

template <typename T>
const T& StackWithMin::min() const
{
	
}


template <typename T>
class StackWithMin
{
public:
	StackWithMin();
	~StackWithMin();
	StackWithMin(const StackWithMin&)
	void push(const T& value);
	void pop();
	const T& min();

private:
	stack<T> m_min;
}



int main(int argc,char* argv[])
{
	
	return 0;
}



