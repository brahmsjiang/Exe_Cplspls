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
//////////

class A;
//Array's type is a pointer to base A*, use virtual func to realize recursion
A* Array[2];

class A
{
public:
    virtual unsigned int Sum(unsigned int n)
    {
        return 0;
    }
};

class B : public A
{
public:
    virtual unsigned int Sum(unsigned int n)
    {
        return (Array[!!n]->Sum(n - 1) + n);
    }
};
//////////

typedef unsigned int(*fun)(unsigned int);

unsigned int Solution3_Teminator(unsigned int n)
{
    return 0;
}

unsigned int Solution3_Sum(unsigned int n)
{
    static fun f[2] = { Solution3_Teminator, Solution3_Sum };
    return (f[!!n](n - 1) + n);
}
//////////

//complete in compile duration
template <unsigned int n>
struct Solution4_Sum
{
    enum Value
    {
        N = Solution4_Sum<n - 1>::N + n,
    };
};

template <>
struct Solution4_Sum<1>
{
    enum Value
    {
        N = 1,
    };
};

int main(int argc, char* argv[])
{
	Temp* pvTemp = new Temp[100];
	auto res1 = Temp::GetSum();
    delete[] pvTemp;
    //////////
    A a;
    B b;
    Array[0] = &a;
    Array[1] = &b;
    auto res2 = Array[1]->Sum(100);
    //////////
    auto res3 = Solution3_Sum(100);
    //////////
    auto res4 = Solution4_Sum<100>::N;

	return 0;
}