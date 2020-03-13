#include <iostream>

using namespace std;

template<class T>
class SmartPtr
{
public:
	SmartPtr(T* p);
	~SmartPtr();
	SmartPtr(const SmartPtr<T>& orig);	//shallow copy
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs);	//shallow copy
private:
	T* ptr;
	int *use_count;
};

//���ǹ��캯����ע���Ǵ��޵��еĹ��죩��������ǰcount��0������Ҳ����delete��
template<class T>
SmartPtr<T>::SmartPtr(T* p)
	:ptr(p)
{
	try {
		use_count = new int(1);
	}
	catch (...)
	{
		delete ptr;
		ptr = nullptr;
		use_count = nullptr;
		cout << "Allocate memory for use_count fails." << endl;
		exit(1);
	}
	cout << "Constructor is called!" << endl;
}

template<class T>
SmartPtr<T>::~SmartPtr()
{
	if (--(*use_count) == 0) {
		delete ptr;
		delete use_count;
		ptr = nullptr;
		use_count = nullptr;
		cout << "Destructor is called!" << endl;
	}
}

//���ǿ������캯����ע���Ǵ��޵��еĹ��죩��������ǰcount��0������Ҳ����delete��
//ָ��origָ��Ķ���ptr = orig.ptr�������countҲ���ڱ�������count�����count++
template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& orig)
{
	ptr = orig.ptr;
	use_count = orig.use_count;
	++(*use_count);
	cout << "Copy constructor is called!" << endl;
}

//��ֵ��������Ѿ����ڵ�ǰ�����ʱ�򱻵��ã����������0�����ͷŵ�ǰ���󣬼�������rhs���ɣ�������rhs��count++��

//���ظ�ֵ�������ͬ�ڸ��ƹ��죬�Ⱥ���ߵĶ�������Ѿ�ָ��ĳ���ڴ棨Ҳ���ܲ�ָ�򣩡�
//���ǵ����ж���߶���ָ����ڴ��Ѿ������õĴ��������Ϊ1�����������ͷţ�
//��֮���ͷţ��������������ͷ�
template<class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& rhs)
{
	//�ڼ���������������ü���ǰʹrhs�����ü�����1����rhs��ָ�Ｔ��ָ��Ķ�����֮Ҫcount++�ģ����Ϳ�������һ����
	//�Ӷ���ֹ����ֵ�����������ͷ��ڴ�,��Ϊ�����Ҹ�ֵʱ�������Ϊ1��������delete�Լ�
	++(*rhs.use_count);

	if (--(*use_count) == 0)
	{
		delete ptr;
		delete use_count;
		cout << "Left side object is deleted!" << endl;
	}

	ptr = rhs.ptr;
	use_count = rhs.use_count;
	cout << "operator= is called!" << endl;
	return *this;
}


int main()
{
	SmartPtr<int> p1(new int(0));
	p1 = p1;

	SmartPtr<int> p2(p1);
	SmartPtr<int> p3(new int(1));
	p3 = p1;

	return 0;
}