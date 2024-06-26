#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>

using namespace std;

//MaxType
template<typename T, typename... Args>
struct MaxType
: std::integral_constant<int, (sizeof(T)>MaxType<Args...>::value ? sizeof(T) : MaxType<Args...>::value) > {};

template<typename T>
struct MaxType<T> : std::integral_constant<int, sizeof(T) > {};

//Contains
template < typename T, typename... List >
struct Contains : std::true_type {};

template < typename T, typename Head, typename... Rest >
struct Contains<T, Head, Rest...>
: std::conditional< std::is_same<T, Head>::value, std::true_type, Contains<T, Rest...>>::type{};

template < typename T >
struct Contains<T> : std::false_type {};

//VariantHelper
template<typename... Args>
struct VariantHelper;

template<typename T, typename... Args>
struct VariantHelper<T, Args...> {
	inline static void Destroy(type_index id, void * data)
	{
		if (id == type_index(typeid(T)))
			((T*)(data))->~T();
		else
			VariantHelper<Args...>::Destroy(id, data);
	}
};

template<> struct VariantHelper<> {
	inline static void Destroy(type_index id, void * data) { }
};

//Variant
template<typename... Types>
class Variant
{
	typedef VariantHelper<Types...> Helper_t;
public:
	Variant(void)
	:m_typeIndex(typeid(void)) {}

	~Variant()
	{
		Helper_t::Destroy(m_typeIndex, &m_data);
	}

	template<typename T>
	bool Is()
	{
		return (m_typeIndex == type_index(typeid(T)));
	}

	bool Empty() const
	{
		return m_typeIndex == type_index(typeid(void));
	}

	type_index Type() const
	{
		return m_typeIndex;
	}

	template<typename T>
	T& Get()
	{
		if (!Is<T>())
		{
			cout << typeid(T).name() << " is not defined. " << "current type is " << m_typeIndex.name() << endl;
			throw std::bad_cast();
		}
		return *(T*)(&m_data);
	}

	template <class T, class = typename std::enable_if<Contains<typename std::remove_reference<T>::type, Types...>::value>::type>
		Variant(T&& value)
		: m_typeIndex(type_index(typeid(void)))
	{
		Helper_t::Destroy(m_typeIndex, &m_data);
		typedef typename std::decay<T>::type U;//remove_reference
		new(m_data) U(std::forward<T>(value));
		m_typeIndex = type_index(typeid(T));
	}

	template<typename F>
	void Visit(F&& f)
	{	
		using T = typename function_traits<F>::arg<0>::type;
		if (Is<T>())
			f(Get<T>());
	}

	template<typename F, typename... Rest>
	void Visit(F&& f, Rest&&... rest)
	{
		using T = typename function_traits<F>::arg<0>::type;
		if (Is<T>())
			Visit(std::forward<F>(f));
		else
			Visit(std::forward<Rest>(rest)...);
	}

private:
	char m_data[MaxType<Types...>::value];
	std::type_index m_typeIndex;
};

void TestVariant()
{
	typedef Variant<int, char, double> cv;
	int x = 10;

	cv v = x;
	v = 1;
	v = 1.123;
	//v = "";//compile error
	v.Get<int>(); //1
	v.Get<double>(); //1.23
	v.Get<short>(); //exception: short is not defined. current type is int
	v.Is<int>();//true
}

template<typename... Args>
void print(Args...args);

template<T>
void print<>() { cout << "template<>" << endl; }

template<typename T, typename... Args>
void print(T t, Args...args)
{ 
	cout << "template<typename T, typename... Args>" << endl;
	print(args...);
}

int main(int argc, const char * argv[]) {
	print(1, 2.2);
	//TestVariant();

	//system("pause");
	return 0;
}