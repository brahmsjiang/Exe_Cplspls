#include <iostream>
#include <math.h>

using namespace std;

bool g_InvalidInput = false;

bool equal(double a, double b)
{
	return abs(a - b) < 0.000001 ? true : false;
}

double Power(double base, int exponent)
{
	g_InvalidInput = false;
	if (equal(base, 0.0) && exponent < 0) {
		g_InvalidInput = true;
		return 0.0;
	}
	double res = 1.0;
	if (0 == exponent)
		return res;
	
	unsigned int adbExpon = abs(exponent);
	while (adbExpon)
	{
		res *= base;
		--adbExpon;
	}
	if (0 < exponent)
		return res;
	else
		return 1.0 / res;

}

double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1.0;
	if (exponent == 1)
		return base;

	double res = PowerWithUnsignedExponent(base, exponent >> 1);
	res *= res;
	if (exponent & 0x1 == 1)
		res *= base;
	return res;
}

double Power2(double base, int exponent)
{
	g_InvalidInput = false;
	if (equal(base, 0.0) && exponent < 0) {
		g_InvalidInput = true;
		return 0.0;
	}
	double res = 1.0;
	unsigned int adbExpon = abs(exponent);
	res = PowerWithUnsignedExponent(base, adbExpon);
	if (0 < exponent)
		return res;
	else
		return 1.0 / res;
}



int main(int argc, char* argv[])
{
	cout << Power(3.1, 1) << endl;
	cout << Power(-3.1, -3) << endl;
	cout << Power(3.1, 0) << endl;
	cout << Power(-3.1, -1) << endl;
	cout << Power(0, -2) << endl;
	cout << Power(0, 2) << endl;
	cout << "==================" << endl;
	cout << Power2(3, 3) << endl;
	cout << Power2(-3.1, -3) << endl;
	cout << Power2(3.1, 0) << endl;
	cout << Power2(-3.1, -1) << endl;
	cout << Power2(0, -2) << endl;
	cout << Power2(0, 2) << endl;
	return 0;
}