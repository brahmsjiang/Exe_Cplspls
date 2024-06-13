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
using namespace std::chrono;

template <typename T>
class testInner
{};

template <typename T, typename U>
class testTemp
{};

void fun() {cout << "fun hello world"<<endl;}

class Timer {
public:
	Timer() : m_begin(high_resolution_clock::now()) {}
	void reset() { m_begin = high_resolution_clock::now();}
	
	template<typename Duration=milliseconds>
	int64_t elapsed() const {
		return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
	}
	int64_t elapsed_micro() const {
		return elapsed<microseconds>();
	}
	int64_t elapsed_nano() const {
		return elapsed<nanoseconds>();
	}
	int64_t elapsed_seconds() const {
		return elapsed<seconds>();
	}
private:
	time_point<high_resolution_clock> m_begin;
};

int main(int argc, const char * argv[]) {
	
	std::chrono::milliseconds ms{3};
	std::chrono::microseconds us = ms;
	cout << "3 ms has: " << ms.count() << " ticks\n" << "3000 us has: " << us.count() << " ticks\n";

	testTemp<int, char> temp1;
	testTemp<int, float> temp2;
	//temp1 = temp2;	//compile err

	std::chrono::minutes t1(10);
	std::chrono::seconds t2(60);
	std::chrono::seconds t3 = t1 - t2;
	cout << t3.count() << " second" << endl;

	std::chrono::duration<double, ratio<9, 7>> d1(3);	//ratio<x, y>, x/y standsfor seconds per clock period
	std::chrono::duration<double, ratio<6, 5>> d2(1);
	auto d3 = d1 - d2;
	cout << typeid(d3).name() << endl;
	cout << d3.count() << endl;
	cout << chrono::duration_cast<chrono::minutes>(t3).count() << " minutes" << endl;

	////time point
	typedef std::chrono::duration<int, std::ratio<60*60*24>> days_type;
	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
	cout << today.time_since_epoch().count() << " days since epoch" << endl;

	system_clock::time_point now = system_clock::now();
	std::time_t last = system_clock::to_time_t(now - hours(24));
	std::time_t next = system_clock::to_time_t(now + hours(24));
	cout << "One day ago, the time was " << std::put_time(std::localtime(&last), "%F %T") << endl
		 << "Next day, the time is " << std::put_time(std::localtime(&next), "%F %T") << endl;

	////clock
	system_clock::time_point t11 = system_clock::now();
	cout << "Hello World\n";
	system_clock::time_point t12 = system_clock::now();
	cout << (t12 - t11).count() << " tick count" << endl;

	t11 = system_clock::now();
	cout << "Hello World2\n";
	t12 = system_clock::now();
	cout << duration_cast<microseconds>(t12 - t11).count() << " microseconds" << endl;

	time_t now_c = system_clock::to_time_t(t12);
	cout << "now_c:" << now_c << endl;

	////timer
	Timer t;
	fun();
	cout << t.elapsed_micro() << endl;
	cout << t.elapsed_nano() << endl;
	cout << t.elapsed() << endl;

	return 0;
}
