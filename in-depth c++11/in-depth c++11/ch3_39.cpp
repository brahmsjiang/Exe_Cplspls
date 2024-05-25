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
struct MakeIndexes : MakeIndexes<N-1, N-1, Indexes...>{};

template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
	typedef IndexTuple<Indexes...> type;
};

/////
namespace details
{
	template<size_t N, typename T1, typename T2>
	using pair_type = std::pair<typename tuple_element<N, T1>::type, typename tuple_element<N, T2>::type>;

	template<size_t N, typename T1, typename T2>
	pair_type<N, T1, T2> pair(const T1& tup1, const T2& tup2) {
		return make_pair(get<N>(tup1), get<N>(tup2));
	}

	template<int... Indexes, typename T1, typename T2>
	auto pairs_helper(IndexTuple<Indexes...>, const T1& tup1, const T2& tup2) {
		return make_tuple(pair<Indexes>(tup1, tup2)...);
	}
}

template<typename Tuple1, typename Tuple2>
auto Zip(Tuple1 tup1, Tuple2 tup2) {
	static_assert(tuple_size<Tuple1>::value == tuple_size<Tuple2>::value, "tuples should be the same size.");
	return details::pairs_helper(typename MakeIndexes<tuple_size<Tuple1>::value>::type(), tup1, tup2);
}

void TupleZip() {
	auto tp1 = make_tuple<int, short, double, char>(1, 2, 2.5, 'a');
	auto tp2 = make_tuple<double, short, double, char>(1.5, 2, 2.5, 'z');
	auto mypairs = Zip(tp1, tp2);
	cout << "" << endl;
}

/////
template<typename F, typename Tuple, int... Indexes>
auto apply(F&& f, IndexTuple<Indexes...>&& in, Tuple&& tp) {
	forward<F>(f)(get<Indexes>(tp)...);
}

void TestF(int a, double b, int c) { cout << a + b + c << endl;}

void Test() {
	apply(TestF, MakeIndexes<3>::type(), make_tuple(1, 2.1, 3));
}

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
	//TupleReverse();
	//Test();
	TupleZip();
	return 0;
}
