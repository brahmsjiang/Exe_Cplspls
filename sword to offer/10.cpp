#include <iostream>
#include <vector>

using namespace std;

long long Fibonacci1(unsigned int n)
{
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	
	return Fibonacci1(n - 1) + Fibonacci1(n - 2);
}

long long Fibonacci2(unsigned int n)
{
	long long FibIni[] = { 0,1 };
	if (n < 2)
		return FibIni[n];

	long long lastlastEle = FibIni[0];
	long long lastEle = FibIni[1];
	long long curRes;
	for (int i = 2; i <= n; i++)
	{
		curRes = lastEle + lastlastEle;
		lastlastEle = lastEle;
		lastEle = curRes;
	}
	return curRes;
}

int main(int argc, char* argv[])
{
	cout << "Fib 5 : " << Fibonacci1(5) << endl;
	cout << "Fib 1: " << Fibonacci2(1) << endl;
	cout << "Fib 5 : " << Fibonacci2(5) << endl;
	cout << "Fib 7 : " << Fibonacci2(7) << endl;
	cout << "Fib 20 : " << Fibonacci2(20) << endl;
	cout << "Fib 50 : " << Fibonacci2(50) << endl;
	cout << "Fib 100 : " << Fibonacci2(100) << endl;
	return 0;
}