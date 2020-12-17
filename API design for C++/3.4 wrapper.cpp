#include <iostream>

class IOriginal
{
public:
    virtual bool DoSomething(int value) = 0;
};

class Original : public IOriginal
{
public:
    bool DoSomething(int value) {}
private:

};

class Proxy : public IOriginal
{
public:
    
private:
    Proxy(const Proxy&);
    const Proxy& operator=(const Proxy&);

    Original* mOrig;
};

int main(int argc, char* argv[])
{

    return 0;
}