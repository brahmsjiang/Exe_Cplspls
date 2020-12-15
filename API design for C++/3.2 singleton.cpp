#include <iostream>
#include <mutex> //c++11

using namespace std;

class Singleton
{
public:
	static Singleton& GetInstance();//���۷���ָ�뻹�����ã����޷�����private��Ա
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
	std::lock_guard<std::mutex> lock(m_mutex);//�����Ƿ��ʼ��������������
	static Singleton instance;//��仰��ԭ�Ӳ�������������ʵ��Ϊstatic char __buffer[] + placement new
	return instance;
}


Singleton& Singleton::GetInstance()
{
	static Singleton* instance = nullptr;
	if (!instance)//�Ѿ���ʼ�������������ˡ�
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!instance)//δ��ʼ����������������֮ǰȷʵ��Ҫ��������Ϊ����instance��д���п��ܣ�
		{
			//��������ʵ��Ϊ(1)operator new + (2)placement new + (3)pointer assignment
			// ���У�2����3���ɵ���
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