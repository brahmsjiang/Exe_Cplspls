#include<iostream>
#include<memory>
#include<stack>
#include<assert.h>

using namespace std;

template<typename T> class StackWithMin;


template <typename T>
class StackWithMin
{
public:
	void push(const T& value);
	void pop();
	const T& min() const;

private:
	stack<T> m_min;
	stack<T> m_data;
};

template <typename T> void StackWithMin<T>::push(const T& value)
{
	m_data.push(value);
	if (m_min.size() == 0 || value < m_min.top())
		m_min.push(value);
	else
		m_min.push(m_min.top());
}

template <typename T> void StackWithMin<T>::pop()
{
	assert(m_data.size() > 0 && m_min.size() > 0);
	m_data.pop();
	m_min.pop();
}

template <typename T> const T& StackWithMin<T>::min() const
{
	assert(m_data.size() > 0 && m_min.size() > 0);
	return m_min.top();	
}



int main(int argc,char* argv[])
{
	StackWithMin<int> swm;	
	swm.push(3);
	cout << swm.min() << endl;
	swm.push(4);
	cout << swm.min() << endl;
	swm.push(2);
	cout << swm.min() << endl;
	swm.push(1);
	cout << swm.min() << endl;
	swm.pop();
	cout << swm.min() << endl;
	swm.pop();
	cout << swm.min() << endl;
	swm.push(0);
	cout << swm.min() << endl;
	return 0;
}



