#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;


class A
{
public:
    static A* getInstance() {
        if (pA == nullptr) {
            return (pA = new A());
        }
        else {
            return pA;
        }
    };
    void destory() {
        // kill self: delete this
        delete this;
    }
private:
    A() {
        cout << "A construct" << endl;
    }
    //private prevent copy
    A(const A&) {}
    A& operator=(const A&) {}
    ~A() {
        cout << "~A destruct" << endl;
    }
    //a member with an in-class initializer must be const, so it can't be initialize here
    static A* pA;
};

// in-class static member must be initialize outside of class and its type is needed.
A* A::pA = nullptr;

class Base 
{
public:
    void basefunc() {
        cout << "Base::basefunc" << endl;
    };
};
class Derive : private Base 
{
public:
    void derivefunc() {
        basefunc();//if basefunc is private, invalid
        //---------
    }
};

class UPNumber {
public:
    UPNumber() { init(); }
    UPNumber(int initValue) { init(); }
    UPNumber(double initValue) { init(); }
    UPNumber(const UPNumber& rhs) { init(); }
    // pseudo destructor, const
    void destory() const { delete this; }
protected:
    void init(){ cout << "UPNumber ctor" << endl; }
    ~UPNumber() { cout << "UPNumber dtor" << endl; }
};

class NonNegativeUPNumber: public UPNumber
{
};

class Asset {
public:
    Asset(int initValue)
        // because UPNumber dtor is protected, only use pseudo to call dtor. so use a pointer and creat it on heap 
        :value(new UPNumber(initValue)) {
        cout << "Asset ctor" << endl;
    }
    ~Asset()
    {
        cout << "Asset dtor" << endl;
        value->destory();
    }
private:
    UPNumber *value;
};

int main(int argc, char* argv[])
{
    {
        A* p_A = A::getInstance();
        p_A->destory();
    }
    {
        Derive dr;
        dr.derivefunc();
    }

    {
        cout << "-----UPNumber-----" << endl;
        //UPNumber n;   //error, private dtor 
        UPNumber *p = new UPNumber; //OK
        p->destory();
    }
    {
        cout << "-----const UPNumber-----" << endl;
        const UPNumber *p = new UPNumber; //OK
        p->destory(); //if destory() isn't const, error
    }
    {
        cout << "-----NonNegativeUPNumber-----" << endl;
        NonNegativeUPNumber nn; //error if base dtor is private, protected will OK
    }
    {
        cout << "-----Asset-----" << endl;
        Asset as(2); //error, if base dtor is private or contain base obj member
    }


    system("pause");
    return 0;
}