#include <iostream>

class Temp
{
public:
	Temp() { N++; Sum += N; }

	static void Reset() { N = 0; Sum = 0; }
	static unsigned int GetSum() { return Sum; }
private:
	static unsigned int N;
	static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

int main(int argc, char* argv[])
{
	Temp* pvTemp = new Temp[100];
	auto res1 = Temp::GetSum();

	return 0;
}