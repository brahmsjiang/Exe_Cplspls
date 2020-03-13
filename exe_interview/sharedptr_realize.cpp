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

//这是构造函数（注意是从无到有的构造），被构造前count是0（不用也不能delete）
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

//这是拷贝构造函数（注意是从无到有的构造），被构造前count是0（不用也不能delete）
//指向orig指向的对象（ptr = orig.ptr），因此count也等于被拷贝的count；最后count++
template<class T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& orig)
{
	ptr = orig.ptr;
	use_count = orig.use_count;
	++(*use_count);
	cout << "Copy constructor is called!" << endl;
}

//赋值运算符在已经存在当前对象的时候被调用，如果计数是0，不释放当前对象，计数等于rhs即可（别忘了rhs的count++）

//重载赋值运算符不同于复制构造，等号左边的对象可能已经指向某块内存（也可能不指向）。
//我们得先判断左边对象指向的内存已经被引用的次数。如果为1，表明可以释放；
//反之则不释放，由其他对象来释放
template<class T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& rhs)
{
	//在减少左操作数的引用计数前使rhs的引用计数加1，（rhs所指物即被指向的对象，总之要count++的，这点和拷贝构造一样）
	//从而防止自身赋值而导致提早释放内存,因为若自我赋值时自身计数为1，会首先delete自己
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