#include <iostream>
#include <mutex> //c++11

using namespace std;

class Singleton
{
public:
	static Singleton& GetInstance();//无论返回指针还是引用，都无法访问private成员
private:
	Singleton() 
	{ 
		cout << "Singleton()" << endl; 
	}
	~Singleton() 
	{
		cout << "~Singleton()" << endl;
	}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
private:
	static std::mutex m_mutex;
};


Singleton& Singleton::GetInstance()
{
	std::lock_guard<std::mutex> lock(m_mutex);//无论是否初始化，都会锁定。
	static Singleton instance;//这句话非原子操作，编译器可实现为static char __buffer[] + placement new
	return instance;
}


Singleton& Singleton::GetInstance()
{
	static Singleton* instance = nullptr;
	if (!instance)//已经初始化，不用锁定了。
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!instance)//未初始化，才锁定。（读之前确实需要锁定，因为对于instance读写都有可能）
		{
			//编译器可实现为(1)operator new + (2)placement new + (3)pointer assignment
			// 其中（2）（3）可调换
			instance = new Singleton();
		}
	}
	return *instance;
}


int main(int argc, char* argv[])
{
	Singleton& obj = Singleton::GetInstance();

	return 0;
}