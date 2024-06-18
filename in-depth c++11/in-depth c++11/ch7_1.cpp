#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>

using namespace std;

class class_c {
public:
	int max;
	int min;
	int middle;

	class_c() {}
	class_c(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	class_c(int my_max, int my_min) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	class_c(int my_max, int my_min, int my_middle) {
		max = my_max > 0 ? my_max : 10;
		min = my_min > 0 && my_min < max ? my_min : 1;
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};

class class_c1 {
public:
	int max;
	int min;
	int middle;

	class_c1() {}
	class_c1(int my_max) {
		max = my_max > 0 ? my_max : 10;
	}
	class_c1(int my_max, int my_min) : class_c1(my_max) {
		min = my_min > 0 && my_min < max ? my_min : 1;
	}
	class_c1(int my_max, int my_min, int my_middle) : class_c1(my_max, my_min) {
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
};


int main(int argc, const char * argv[]) {
	


	return 0;
}
