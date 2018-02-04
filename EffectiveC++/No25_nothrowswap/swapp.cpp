

#include <iostream>



template<typename T>
void dosomething(T& a,T& b)
{
	using std::swap;
	swap(a,b);
}


int main()
{
	int a=1,b=2;
	dosomething(a,b);
	return 0;
}
