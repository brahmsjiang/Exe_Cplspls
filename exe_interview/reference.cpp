#include <iostream>

using namespace std;

int glbVar = 10;

int& retRef()
{
    return glbVar;
}


class Base
{
public:
    virtual void func() { cout << "baseFunc()" << endl; }
    virtual void constFunc() const { cout << "constFunc()" << endl; }
};

class Inherit : public Base
{
public:
    virtual void func() { cout << "inheritFunc()" << endl; }
};

void callFunc(const Base& ref)
{
    //ref.func();
    const_cast<Base&>(ref).func();
    //const obj only can call const func
    //however non-const obj can call non-const & const func  
    ref.constFunc();
}

int main(int argc, char* argv[])
{
#if 0
    int tmp = 0;
    int* ptr_tmp = &tmp;

    tmp = retRef();
    int& rtmp = retRef();

    int* ptr_rtmp = &rtmp;

#endif
    Base* pBase = new Inherit;
    pBase->func();
    (*pBase).func();

    Base bObj = *pBase;
    bObj.func();

    callFunc(*pBase);

	Inherit oInherit;
	Base& rBase = oInherit;
	rBase.func();

    return 0;
}