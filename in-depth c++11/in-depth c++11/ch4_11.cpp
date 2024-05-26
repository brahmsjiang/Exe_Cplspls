#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>

using namespace std;

template<typename T>
shared_ptr<T> make_shared_array(size_t size)
{
	return shared_ptr<T>(new T[size], default_delete<T[]>());
}

template<typename T, typename... Args> inline
typename enable_if < !is_array<T>::value, unique_ptr<T> >::type
make_unique(Args&&... args) {
	return unique_ptr<T>(new T(forward<Args>(args)...));
}

template<typename T> inline
typename enable_if<is_array<T>::value && extent<T>::value == 0, unique_ptr<T>>::type
make_unique(size_t size) {
	typedef typename remove_extent<T>::type U;
	return unique_ptr<T>(new U[size]());
}

template<typename T, typename... Args>
typename enable_if<extent<T>::value != 0, void>::type
make_unique(Args&&...) = delete;

int main(int argc, const char * argv[]) {
	
	shared_ptr<int> p(new int(1), [](int* p) {delete p; });
	shared_ptr<int> p1(new int[10], [](int* p) {delete[] p; });
	shared_ptr<int> p2(new int[10], std::default_delete<int[]>());

	auto p3 = make_shared_array<int>(10);
	auto p4 = make_shared_array<char>(10);

	{
		int* ptr = new int(55);
		shared_ptr<int> p5(ptr);
		cout << "p5.use_count()" << p5.use_count() << endl;
		shared_ptr<int> p6(p5);
		cout << "p6.use_count()" << p5.use_count() << endl;
	}
	{
		int* ptr = new int(55);
		shared_ptr<int> p5(ptr);
		cout << "p5.use_count()" << p5.use_count() << endl;
		//shared_ptr<int> p6(ptr);//cause crash
		cout << "p6.use_count()" << p5.use_count() << endl;
	}
	{
		struct A {};
		shared_ptr<A> spa1(new A);
		cout << "spa1.use_count()" << spa1.use_count() << endl;
		shared_ptr<A> spa2(spa1);
		cout << "spa2.use_count()" << spa2.use_count() << endl;
	}
	return 0;
}
