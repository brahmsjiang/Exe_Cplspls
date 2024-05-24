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

template<int...>
struct IndexTuple{};

template<int N, int... Indexes>
struct make_indexes : make_indexes<N-1, N-1, Indexes...>{};

//termination condition
template<int... Indexes>
struct make_indexes<0, Indexes...> {
	using type = IndexTuple<Indexes...>;
};

////////
template<int I, typename IndexTuple, typename... Types>
struct make_indexes_reverse_impl;

//declare
template<int I, int... Indexes, typename T, typename...Types>
struct make_indexes_reverse_impl<I, IndexTuple<Indexes...>, T, Types...>
{
	using type = typename make_indexes_reverse_impl<I-1, IndexTuple<Indexes..., I-1>, Types...>::type;
};

//terminate
template<int I, int... Indexes>
struct make_indexes_reverse_impl<I, IndexTuple<Indexes...>>
{
	using type = IndexTuple<Indexes...>;
};


template<typename... Types>
struct make_reverse_indexes : make_indexes_reverse_impl<sizeof...(Types), IndexTuple<>, Types...>
{};

template <class... Args, int... Indexes>
auto reverse_imp(tuple<Args...>&& tup, IndexTuple<Indexes...>&&) {
	return make_tuple(get<Indexes>(forward<tuple<Args...>>(tup))...);
}

template <class... Args>
auto Reverse(tuple<Args...>&& tup) {
	return reverse_imp(forward<tuple<Args...>>(tup), typename make_reverse_indexes<Args...>::type());
}

void TupleReverse() {
	auto tp2 = Reverse(make_tuple<int, char>(1,'a'));
}

int main(int argc, const char * argv[]) {
	TupleReverse();

	return 0;
}
