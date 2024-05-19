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

int main(int argc, const char * argv[]) {
	tuple<int, double, string> tp = make_tuple(1, 2.1, "ok");
	int index = find_index(tp, 2.1);
	cout << index << endl;
	
	//system("pause");
	return 0;
}