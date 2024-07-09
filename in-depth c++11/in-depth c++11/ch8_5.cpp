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

template<typename T>
class ObjectPool {
	template<typename.... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
	ObjectPool() : needClear(false) {}
	~ObjectPool() { needClear = true; }
	
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num <= 0 || num > MaxObjectNum)
			throw std::logic_error("object num out of range.");
		auto constructName = typeid(Constructor<Args...>).name(); //不区分引用
		for (size_t i = 0; i < num; i++) {
			m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p)
			{
				return createPtr<T>(string(constructName), args...);
			}
			));
		}
	}

	template<typename T, typename... Args>
	std::shared_ptr<T> createPtr(string& constructName, Args... args)
	{
		return std::shared_ptr<T>(new T(args...), [constructName, this](T* t)
		{
			if (needClear)
				delete[] t;
			else
				m_object_map.emplace(constructName, std::shared_ptr<T>(t));
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


int main(int argc, const char * argv[]) {

	cout << "/////////////////////" << endl;

	cout << "/////////////////////" << endl;

	return 0;
}
