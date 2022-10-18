//#include "output_container.h"

#include <stdlib.h>
#include <assert.h>

#include <functional>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <array>
#include <numeric>
#include <functional>
#include <map>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

//last one permit variadic param
template <typename F>
auto compose(F f)
{
  return [f](auto&&... x) {
    return f(
      forward<decltype(x)>(x)...);
  };
}

template <typename F, typename... Args>
auto compose(F f, Args... other)
{
    return [f, other...](auto&&... x) {
        return f(compose(other...)());
    };
}


template <
  template <typename, typename>
  class OutContainer = vector,
  typename F, class R>
auto fmap(F&& f, R&& inputs)
{
  typedef decay_t<decltype(
    f(*inputs.begin()))>
    result_type;
  OutContainer<
    result_type,
    allocator<result_type>>
    result;
  for (auto&& item : inputs) {
    result.push_back(f(item));
  }
  return result;
}

auto square_list = [](auto&& container) {
    return fmap([](int x) { return x * x; }, container);
};

auto sum_list = [](auto&& container) {
    return accumulate(container.begin(), container.end(), 0);
};



int main(int argc, char* argv[])
{
    //auto squared_sum = compose(square_list, sum_list);
    
    vector<int> v{1,2,3,4,5};
    auto tmp_res = compose(square_list);

    
    cout << tmp_res(v) << endl;

    return 0;
}

