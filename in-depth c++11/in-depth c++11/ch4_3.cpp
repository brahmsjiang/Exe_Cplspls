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


int main(int argc, const char * argv[]) {
	
	shared_ptr<int> sp(new int(10));
	weak_ptr<int> wp(sp);
	cout << wp.use_count() << endl;

	return 0;
}
