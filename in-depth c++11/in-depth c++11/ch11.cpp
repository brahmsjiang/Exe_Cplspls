#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <list>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <map>
#include <unordered_map>
#include <thread>
#include <typeinfo>
#include <typeindex>
#include "../../Utilties/Any.hpp"
#include "../../Utilties/NonCopyable.hpp"

using namespace std;

void TestAny() {
	Any n;
	auto r = n.IsNull();
	string s1 = "hello";
	n = s1;
	n.AnyCast<string>();
	Any n1 = 1;
	n1.Is<int>();
}

struct Base
{
	virtual void Func(){}
	virtual ~Base(){}
};
struct DerivedB : Base
{
	DerivedB() = default;
	DerivedB(int a, double b) : m_a(a), m_b(b) {}
	void Func() override { cout << "call func in DerivedB: " << m_a + m_b << endl; }
private:
	int m_a;
	double m_b;
};
struct DerivedC : Base
{
	void Func() override { cout << "call func in DerivedC" << endl; }
};
struct DerivedD : Base
{
	void Func() override { cout << "call func in DerivedD" << endl; }
};
struct Bus
{
	void Test() { cout << "Bus::test()" << endl; }
	void Test(int a, int b) { cout << "Bus::test(): " << a+b << endl; }
};
struct Car
{
	void Test() { cout << "Car::test()" << endl; }
};
class A //A-->Base
{
public:
	A(Base* interface) : m_interface(interface) {}
	void Func() { m_interface->Func(); }
	~A() {
		if (m_interface != nullptr) {
			delete m_interface;
			m_interface = nullptr;
		}
	}
private:
	Base* m_interface;
};
void TestOld0() {
	A* a = new A(new DerivedB());
	a->Func();
	delete a;
}
void TestOld1(int sel) {
	A* a = nullptr;
	if (sel == 0)
		a = new A(new DerivedB());
	else if (sel == 1)
		a = new A(new DerivedC());
	else if (sel == 2)
		a = new A(new DerivedD());
	a->Func();
	delete a;
}

struct Factory
{
	static Base* Create(const string& condition) {
		if (condition == "B")
			return new DerivedB();
		else if (condition == "C")
			return new DerivedC();
		else if (condition == "D")
			return new DerivedD();
		else
			return nullptr;
	}
};
void TestOld2() {
	string temp = "C";
	A* a = new A(Factory::Create(temp));
	a->Func();
	delete a;
}

///////////////////////////////
template<class T>
class IocContainer
{
public:
	IocContainer() = default;
	~IocContainer() = default;
	template <class Drived>
	void RegisterType(string strKey) {
		std::function<T*()> function = []{ return new Drived(); };
		RegisterType(strKey, function);
	}
	T* Resolve(string strKey) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end())
			return nullptr;
		std::function<T*()> function = m_creatorMap[strKey];
		return function();
	}
	std::shared_ptr<T> ResolveShared(string strKey) {
		T* ptr = Resolve(strKey);
		return std::shared_ptr<T>(ptr);
	}
private:
	std::map<string, std::function<T*()>> m_creatorMap;
private:
	void RegisterType(string strKey, std::function<T*()> creator) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
			throw std::invalid_argument("this key has already exist!");
		m_creatorMap.emplace(strKey, creator);
	}
};

void TestNew() {
	IocContainer<Base> baseIoc;
	baseIoc.RegisterType<DerivedB>("DerivedB");
	baseIoc.RegisterType<DerivedC>("DerivedC");
	std::shared_ptr<Base> b = baseIoc.ResolveShared("DerivedB");
	b->Func();
	std::shared_ptr<Base> c = baseIoc.ResolveShared("DerivedC");
	c->Func();
}
/////////////////////////////////
class IocContainer1
{
public:
	IocContainer1() = default;
	~IocContainer1() = default;
	IocContainer1(const IocContainer1&) = delete;
	IocContainer1(IocContainer1&&) = default;
	IocContainer1& operator=(const IocContainer1&) = default;

	template <class T, typename... Depend>
	void RegisterType(const string& strKey) {
		std::function<T*()> function = [] { return new T(new Depend()...); };//erase type T by lambda
		RegisterType(strKey, function);	//store function<T*()> in Any
	}
	template <class T>
	T* Resolve(const string& strKey) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end())
			return nullptr;
		Any resolver = m_creatorMap[strKey];
		std::function<T*()> function = resolver.AnyCast<std::function<T*()>>();//just convert Any to template-func's para <T>
		return function();
	}
	template <class T>
	std::shared_ptr<T> ResolveShared(const string& strKey) {
		T* t = Resolve<T>(strKey);
		return std::shared_ptr<T>(t);
	}
private:
	std::unordered_map<string, Any> m_creatorMap;
private:
	void RegisterType(const string& strKey, Any creator) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
			throw std::invalid_argument("this key has already exist!");
		m_creatorMap.emplace(strKey, creator);
	}
};

void TestNew1() {
	IocContainer1 ioc;	//no need specify template para as <base>
	ioc.RegisterType<A, DerivedB>("DerivedB");
	ioc.RegisterType<A, DerivedC>("DerivedC");
	auto b = ioc.ResolveShared<A>("DerivedB");
	b->Func();
	auto c = ioc.ResolveShared<A>("DerivedC");
	c->Func();
	////////////
	ioc.RegisterType<Bus>("bus");
	ioc.RegisterType<Car>("car");
	auto bus = ioc.ResolveShared<Bus>("bus");
	bus->Test();
	auto car = ioc.ResolveShared<Car>("car");
	car->Test();
}

struct AAA {
	AAA(const AAA&) = default;
};
bool testAAA() {
	std::map<int, AAA> m;
    return m.begin() == m.end(); // line 9
}
/////////////////////////////////
class IocContainer2 : NonCopyable
{
public:
	IocContainer2(void) = default;
	~IocContainer2(void) = default;
	template<class T, typename... Args>
	void RegisterSimpleType(const string& strKey) {
		std::function<T*()> function = [](Args... args){ return new T(args...); };
		RegisterType(strKey, function);
	}
	template<class T, typename Depend, typename... Args>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type RegisterType(const string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(new Depend(args...)); };
		RegisterType(strKey, function);
	}
	template<class T, typename Depend, typename... Args>
	typename std::enable_if<std::is_base_of<T, Depend>::value, void>::type RegisterType(const string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new Depend(args...); };
		RegisterType(strKey, function);
	}
	////////
	template<class T, typename... Args>
	T* Resolve(const string& strKey, Args... args) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end())
			return nullptr;
		Any resolver = m_creatorMap[strKey];
		std::function<T*(Args...)> function = resolver.AnyCast<std::function<T*(Args...)>>();
		return function(args...);
	}
	template<class T, typename... Args>
	std::shared_ptr<T> ResolveShared(const string& strKey, Args... args) {
		T* t = Resolve<T>(strKey, args...);
		return std::shared_ptr<T>(t);
	}
private:
	void RegisterType(const string& strKey, Any constructor) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end())
			throw std::invalid_argument("this key has already exist!");
		m_creatorMap.emplace(strKey, constructor);
	}
private:
	unordered_map<string, Any> m_creatorMap;
};
void TestNew2() {
	IocContainer2 ioc;
	ioc.RegisterType<A, DerivedC>("DerivedC");
	auto c = ioc.ResolveShared<A>("DerivedC");
	c->Func();
	////////////
	ioc.RegisterType<A, DerivedB>("DerivedB1");
	ioc.RegisterType<A, DerivedB, int, double>("DerivedB2");
	auto b1 = ioc.ResolveShared<A>("DerivedB1");
	b1->Func();
	auto b2 = ioc.ResolveShared<A>("DerivedB2", 1, 2.0);
	b2->Func();
	///////////
	ioc.RegisterSimpleType<Bus>("bus");
	auto bus = ioc.ResolveShared<Bus>("bus");
	bus->Test(1, 2);
	///////////
	ioc.RegisterType<Base, DerivedB>("DerivedB");
	auto b = ioc.ResolveShared<Base>("DerivedB");
	b->Func();
}


int main(int argc, const char * argv[]) {
	TestOld0();
	cout << "/////////////////////" << endl;
	TestOld1(2);
	cout << "/////////////////////" << endl;
	TestOld2();
	cout << "/////////////////////" << endl;
	TestNew();
	cout << "/////////////////////" << endl;
	TestNew1();
	cout << "/////////////////////" << endl;
	//auto res = testAAA();
	TestNew2();

	return 0;
}
