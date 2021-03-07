#ifndef FORWARD_DECLARATION
#define FORWARD_DECLARATION

class Impl;

class MainClass
{
public:
	MainClass();
	~MainClass();

	void Func();
private:
	Impl* pImpl;
};




#endif // FORWARD_DECLARATION
