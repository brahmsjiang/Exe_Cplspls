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

using namespace std;

struct adder {
	adder(int n) : n_(n) {}
	int operator()(int x) const
	{
		return x + n_;
	}
private:
	int n_;
};

int add_2(int x)
{
	return x + 2;
}

template <typename T>
auto test1(T fn)
{
	return fn(2);
}

template <typename T>
auto test2(T& fn)
{
	return fn(2);
}

template <typename T>
auto test3(T* fn)
{
	return (*fn)(2);
}

class Obj
{
public:
	Obj() : mem(0)
	{
		cout << "Obj()" << endl;
	}
	Obj(int n) : mem(n)
	{
		cout << "Obj(int n)" << endl;
	}
	Obj(const Obj& obj)
	{
		mem = obj.mem;
		cout << "Obj(const Obj& obj)" << endl;
	}
	Obj& operator=(const Obj& obj)
	{
		mem = obj.mem;
		cout << "operator=(const Obj& obj)" << endl;
		return *this;
	}
	~Obj()
	{
		cout << "~Obj()" << endl;
	}
private:
	int mem;
};

int get_count()
{
	static int count = 0;
	return ++count;
}

class task {
public:
	task(int data) : data_(data) {}
	auto lazy_launch()
	{
		return [tmp = *this, count = get_count()]() mutable
		{
			ostringstream oss;
			oss << "Done work " << tmp.data_
				<< "(No. " << count
				<< ") in thread " << this_thread::get_id() << '\n';
			tmp.msg_ = oss.str();
			tmp.calculate();
		};
	}

	void calculate()
	{
		this_thread::sleep_for(100ms);
		cout << msg_;
	}

private:
	int data_;
	string msg_;
};

template <typename T1, typename T2>
auto sum(T1 x, T2 y)
{
	return x + y;
}

auto sum_lambda = [](auto x, auto y)
{
	return x + y;
};

int main(int argc, char* argv[])
{
	adder add_2(2);
	int res = add_2(5);

	auto add_2_c11 = add_2(2);
	auto res_c11 = add_2(5);

	auto fun1 = test1(add_2);
	auto fun2 = test2(add_2);
	auto fun3 = test3(&add_2);

	auto add_2_lambda = [](int x) {
		return x + 2;
	};
	auto res_lam = add_2_lambda(4);

	auto add_lambda = [](int n) {
		return [n](int x) {
			return x + n;
		};
	};
	auto res_lam1 = add_lambda(2)(5);

	std::vector<int> v{ 1,2,3,4,5 };
	//将容器里的每一项数值都加上 2
	//参数:源容器的起始、终止地址，目标容器起始地址
	std::transform(v.begin(), v.end(),
		v.begin(),
		[](int x) {
		return x + 2;
	});

	auto res2 = [](int x) { return x * x; }(3);

	int init_mod = 2;
	Obj obj;
	switch (init_mod)
	{
	case 1:
		obj = Obj(1);
	case 2:
		obj = Obj(2);
	default:
		break;
	}

	auto objCon1 = [init_mod]() {
		switch (init_mod)
		{
		case 1:
			return Obj(1);
			break;
		case 2:
			return Obj(2);
			break;
		default:
			break;
		}
	}();
	Obj obj3(3);
	Obj obj3_ = Obj(3);
	obj3 = obj3_;
	Obj obj3_copy1 = obj3;
	Obj obj3_copy2(obj3);

	vector<int> v1, v2;
	auto push_data = [&](int n) mutable {
		v1.push_back(n);
		v2.push_back(n);
		//init_mod = 1;
	};
	push_data(2), push_data(3);
	cout << "cur tid " << this_thread::get_id() << "==========\n";
	auto t = task{ 37 };
	thread t1{ t.lazy_launch() };
	thread t2{ t.lazy_launch() };
	t1.join();
	t2.join();

	array<int, 5> a{ 1,2,3,4,5 };
	auto s = accumulate(
		a.begin(), a.end(), 0,
		[](auto x, auto y) {
			return x + y;
		}
	);

	std::transform(v.begin(), v.end(),
		v.begin(),
		bind(plus<>(), placeholders::_1, 2));

	map<string, function<int(int, int)>> op_dict
	{
		{"+", [](int x, int y) {
			return x + y;
		}},
		{"-", [](int x, int y) {
			return x - y;
		}},
		{"*", [](int x, int y) {
			return x * y;
		}},
		{"/", [](int x, int y) {
			return x / y;
		}},
	};
	int ress1 = op_dict.at("+")(1, 6);
	int ress2 = op_dict["/"](6, 2);


    system("pause");
    return 0;
}











