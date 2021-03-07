#include "ForwardDeclaration.h"
#include "ForwardDeclaration_impl.h"
#include <iostream>

MainClass::MainClass()
	:pImpl(new Impl)
{
}

MainClass::~MainClass()
{
}

void MainClass::Func()
{
	
}

int main(int argc, char* argv[])
{
	MainClass obj;
	obj.Func();
	return 0;
}


