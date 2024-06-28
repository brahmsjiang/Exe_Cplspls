#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include <numeric>

using namespace std;

#if 0
template <typename T>
class Singleton
{
public:
	static T* Instance() {
		if (m_pInstance == nullptr)
			m_pInstance = new T();
		return m_pInstance;
	}
	template<typename T0>
	static T* Instance(T0 arg0) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0);
		return m_pInstance;
	}
	template<typename T0, typename T1>
	static T* Instance(T0 arg0, T1 arg1) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1);
		return m_pInstance;
	}
	template<typename T0, typename T1, typename T2>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1, arg2);
		return m_pInstance;
	}
	template<typename T0, typename T1, typename T2, typename T3>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1, arg2, arg3);
		return m_pInstance;
	}
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1, arg2, arg3, arg4);
		return m_pInstance;
	}
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1, arg2, arg3, arg4, arg5);
		return m_pInstance;
	}
	/*better less than 6 pars, because 6 pars would be stored in register rdi, rsi, rdx, rcx, r8, r9,
	**others would pushed into stack
	*/
	template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
		return m_pInstance;
	}

	static T* GetInstance() {
		if (m_pInstance == nullptr)
			throw std::logic_error("the instance is not init, pls init first");
		return m_pInstance;
	}
	static void DestoryInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	Singleton();
	virtual ~Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
private:
	static T* m_pInstance;
};
#endif

template <typename T>
class Singleton
{
public:
	template<typename... Args>
	static T* Instance(Args&&... args) {
		if (m_pInstance == nullptr)
			m_pInstance = new T(std::forward<Args>(args)...);
		return m_pInstance;
	}
	static T* GetInstance() {
		if (m_pInstance == nullptr)
			throw std::logic_error("the instance is not init, pls init first");
		return m_pInstance;
	}
	static void DestoryInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}

	Singleton() = delete;
	virtual ~Singleton() = delete;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	static T* m_pInstance;
};

template<typename T>
T* Singleton<T>::m_pInstance = nullptr;

struct A {
	A(const string&) {cout << "lvaue" << endl;}
	A(string&&) {cout << "rvaue" << endl;}
};
struct B {
	B(const string&) {cout << "lvaue" << endl;}
	B(string&&) {cout << "rvaue" << endl;}
};
struct C {
	C(int x, double y) {}
	void Fun() {cout << "test" << endl;}
};

int main(int argc, const char * argv[]) {
	string str = "bb";
	Singleton<A>::Instance(str);
	Singleton<B>::Instance(std::move(str));
	Singleton<C>::Instance(1, 3.14);
	Singleton<C>::GetInstance()->Fun();

	Singleton<A>::DestoryInstance();
	Singleton<B>::DestoryInstance();
	Singleton<C>::DestoryInstance();

	return 0;
}
