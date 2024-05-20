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

namespace detail
{
	template<typename T, typename U>
	typename enable_if<is_convertible<T, U>::value || is_convertible<U, T>::value, bool>::type compare(T t, U u) {
		return t == u;
	}

	bool compare(...) {
		return false;
	}

	template<int I, typename T, typename... Args>
	struct find_index {
		static int call(const tuple<Args...>& t, T&& val) {
			return compare(get<I - 1>(t), val) ? I - 1 : find_index<I - 1, T, Args...>::call(t, forward<T>(val));
		}
	};

	template<typename T, typename... Args>
	struct find_index<0, T, Args...> {
		static int call(const tuple<Args...>& t, T&& val) {
			return compare(get<0>(t), val) ? 0 : -1;
		}
	};
}

template<typename T, typename... Args>
int find_index(tuple<Args...> const& t, T&& val)
{
	return detail::find_index<sizeof...(Args), T, Args...>::call(t, forward<T>(val));
}

void TestFindIndex() {
	tuple<int, double, string> tp = make_tuple(1, 2.1, "ok");
	int index = find_index(tp, 2.1);
	cout << index << endl;
}

template<size_t k, typename Tuple>
typename enable_if<k == tuple_size<Tuple>::value>::type GetArgByIndex(size_t index, Tuple& tp) {
	//throw invalid_argument("arg index out of range");
	cout << ("!!arg index out of range") << endl;
}

template<size_t k = 0, typename Tuple>
typename enable_if<k < tuple_size<Tuple>::value>::type GetArgByIndex(size_t index, Tuple& tp) {
	if (k == index)
		cout << get<k>(tp) << endl;
	else
		GetArgByIndex<k + 1>(index, tp);
}

void TestTuple() {
	using Tuple = tuple<int, double, string, int>;
	Tuple tp = make_tuple(1, 2, "test", 3);
	const size_t length = tuple_size<Tuple>::value;

	GetArgByIndex<0>(1, tp);
	/*
	for (size_t i = 0; i < length; ++i) {
		GetArgByIndex<0>(i, tp);
	}
	*/
	//GetArgByIndex(4, tp);
}

template<typename Arg>
void GetArgByIndex1(int index, tuple<Arg>& tp) {
	cout << get<0>(tp) << endl;
}

template<typename T, typename... Args>
void GetArgByIndex1(int index, tuple<T, Args...>& tp) {
	if (index < 0 || index >= tuple_size<tuple<T, Args...>>::value)
		throw invalid_argument("index is not valid");
	if (index > 0) {
		Tuple newTp = make_tuple(get<0>(tp)...);
		GetArgByIndex1(index - 1, tp);
	}
	else
		cout << get<0>(tp) << endl;
}

void TestTuple1() {
	using Tuple = tuple<int, double>;
	Tuple tp = make_tuple(1, 2.1);
	const size_t length = tuple_size<Tuple>::value;

	GetArgByIndex1(1, tp);
	/*
	for (size_t i = 0; i < length; ++i) {
	GetArgByIndex<0>(i, tp);
	}
	*/
}

int main(int argc, const char * argv[]) {
	//TestFindIndex();

	TestTuple1();
	//system("pause");
	return 0;
}