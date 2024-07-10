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

using namespace std;

const int MaxObjectNum = 10;

void PrintArgs() {
	cout << endl;
}
template<typename T, typename... Args>
void PrintArgs(T t, Args... args) {
	cout << t << " ";
	PrintArgs(args...);
}


template<typename T>
class ObjectPool {
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
	ObjectPool() : needClear(false) {}
	~ObjectPool() { needClear = true; }
	
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 || num > MaxObjectNum)
			throw std::logic_error("object num out of range.");
		PrintArgs("Init:", num, args...);
		auto constructName = typeid(Constructor<Args...>).name(); //不区分引用
		for (size_t i = 0; i < num; i++) {
			m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName, args...](T* p)
			{
				cout << "try deleting..." << constructName << endl;
				 //删除器中不直接删除对象，而是回收到对象池中，以供下次使用
				return createPtr(string(constructName), args...);
			}
			));
		}
	}

	template<typename... Args>
	std::shared_ptr<T> createPtr(const string& constructName, Args... args)
	{
		return std::shared_ptr<T>(new T(args...), [this, constructName](T* p)
		{
			if (needClear) {
				delete[] p;
			} else {
				cout << "emplace again..." << constructName << endl;
				m_object_map.emplace(constructName, std::shared_ptr<T>(p));
			}
		});
	}

	template<typename... Args>
	std::shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();
		auto range = m_object_map.equal_range(constructName);
		for (auto it = range.first; it != range.second; ++it) {
			auto ptr = it->second;
			m_object_map.erase(it);
			return ptr;
		}
		return nullptr;
	}

private:
	std::multimap<std::string, std::shared_ptr<T>> m_object_map;
	bool needClear;
};

struct BigObject
{
	BigObject() {}
	BigObject(int a) {}
	BigObject(const int& a, const int& b) {}
	void Print(const string& str) {
		cout << str << endl;
	}
};
void Print(shared_ptr<BigObject> p, const string& str)
{
	if (p != nullptr)
		p->Print(str);
}

void TestObjPool()
{
	ObjectPool<BigObject> pool;
	pool.Init(2);
	{
		auto p = pool.Get();
		Print(p, "p");
		auto p2 = pool.Get();
		Print(p2, "p2");
		cout << "block ended." << endl;
	}
	/*
	auto p = pool.Get();
	auto p2 = pool.Get();
	Print(p, "p");
	Print(p2, "p2");

	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	Print(p4, "p4");
	pool.Init(2, 1, 2);
	auto p5 = pool.Get<int, int>();
	Print(p5, "p5");
	*/
}

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;
};

template<typename T>
class ObjectPool1 : NonCopyable
{
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 || num > MaxObjectNum)
			throw std::logic_error("object num out of range.");
		auto constructName = typeid(Constructor<Args...>).name(); //不区分引用
		for (size_t i = 0; i < num; i++) {
			m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName, args...](T* p)
			{
				m_object_map.emplace(std::move(constructName), std::shared_ptr<T>(p));
			}
			));
		}
	}

	template<typename... Args>
	std::shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();
		auto range = m_object_map.equal_range(constructName);
		for (auto it = range.first; it != range.second; ++it) {
			auto ptr = it->second;
			m_object_map.erase(it);
			return ptr;
		}
		return nullptr;
	}
private:
	std::multimap<std::string, std::shared_ptr<T>> m_object_map;
};

void TestObjPool1()
{
	ObjectPool1<BigObject> pool;
	pool.Init(2);
	{
		auto p = pool.Get();
		Print(p, "p");
		auto p2 = pool.Get();
		Print(p2, "p2");
	}
	auto p = pool.Get();
	auto p2 = pool.Get();
	Print(p, "p");
	Print(p2, "p2");

	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	Print(p4, "p4");
	pool.Init(2, 1, 2);
	auto p5 = pool.Get<int, int>();
	Print(p5, "p5");
}

int main(int argc, const char * argv[]) {

	TestObjPool();
	cout << "/////////////////////" << endl;
	TestObjPool1();
	cout << "/////////////////////" << endl;

	return 0;
}
