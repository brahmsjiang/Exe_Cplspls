#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <type_traits>
#include <memory>
#include <vector>
#include <list>
#include <typeindex>
#include <tuple>
#include <chrono>
#include <iomanip>
#include <assert.h>
#include <algorithm>
#include <numeric>
#include <map>
#include <thread>

using namespace std;

template<typename T>
class TestClass
{
public:
	TestClass() {}

	template<typename... Args>
	TestClass(Args&&... args) {
		intV = {args...};
	}
/*
	void Func(const T& x) {	//const T& universal reference, accept lvaue & rvalue
		cout << "Func(const T& x)" << endl;
	}
*/

	void Func(T&& x) {	//T&& not universal reference, only accept rvalue
		cout << "Func(T&& x)" << endl;
	}
	template<typename F>
	void Func(F&& x) {	//F&& universal reference, accept lvaue & rvalue
		cout << "template<tyepname F>, Func(F&& x)" << endl;
	}
	void Take(std::vector<T>& vec) {
		vec = std::move(intV);
	}
	size_t vSize() { return intV.size(); }
private:
	std::vector<T> intV;
};

void TestClassFunc() {
	TestClass<int> obj;
	obj.Func(1);
	int x = 1;
	obj.Func(x);
	TestClass<int> obj1(1,2,3);
	cout << "obj1 intV size:" << obj1.vSize() << endl;
	std::vector<int> res;
	obj1.Take(res);
	cout << "obj1 intV size:" << obj1.vSize() << endl;
	cout << "res size:" << res.size() << endl;
}

////////////////////////////////////////
////////////////////////////////////////
template<typename T>
class SyncQueue
{
public:
	SyncQueue(int maxSize) : m_maxSize(maxSize), m_needStop(false) {}
	void Put(const T& x) {
		Add(x);
	}
	void Put(T&& x) {
		Add(std::forward<T>(x));
	}
	void Take(std::list<T>& list) {
		std::unique_lock<std::mutex> locker(m_mutex);
		//conditionvar, unlock & wait if condition not satisfy; lock & go through if be notified and condition satisfy
		m_notEmpty.wait(locker, [this]{ return m_needStop || NotEmpty(); });
		if (m_needStop)
			return;
		list = std::move(m_queue);
		m_notFull.notify_one();
	}
	void Take(T& t) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty.wait(locker, [this]{ return m_needStop || NotEmpty(); });	//when take ele, watch notEmpty
		if (m_needStop)
			return;
		t = m_queue.front();
		m_queue.pop_front();
		m_notFull.notify_one();	//after take ele, notify notFull
	}
	template<typename F>
	void Add(F&& x) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notFull.wait(locker, [this]{ return m_needStop || NotFull(); });	//when add ele, watch notFull
		if (m_needStop)
			return;
		m_queue.push_back(std::forward<F>(x));
		m_notEmpty.notify_one();	//after add ele, notify notEmpty
	}
	void Stop() {
		{
			std::unique_lock<std::mutex> locker(m_mutex);
			m_needStop = true;
		}
		m_notFull.notify_all();
		m_notEmpty.notify_all();
	}
	
	size_t Size() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}
	int Count() {
		return m_queue.size();
	}
private:
	bool NotFull() const {
		bool full = m_queue.size() >= m_maxSize;
		if (full)
			cout << "cache full, need wait.." << endl;
		return !full;
	}
	bool NotEmpty() const {
		bool empty = m_queue.empty();
		if (empty)
			cout << "cache empty, need wait...sync thread ID:" << this_thread::get_id() << endl;
		return !empty;
	}
private:
	std::list<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_notEmpty;
	std::condition_variable m_notFull;
	int m_maxSize;
	bool m_needStop;
};

const int MaxTaskCount = 100;
class ThreadPool {
public:
	using Task = std::function<void()>;
	ThreadPool(int numThreads = std::thread::hardware_concurrency())
		: m_queue(MaxTaskCount) {	// sync/block queue size
		cout << "hardware_concurrency:" << numThreads << endl;
		Start(numThreads);
	}
	~ThreadPool(void) {
		Stop();
	}
	void Stop() {
		// make sure only once call StopThreadGroup
		std::call_once(m_flag, [this]{ StopThreadGroup(); });
	}
	void AddTask(Task&& task) {
		m_queue.Put(std::forward<Task>(task));
	}
	void AddTask(const Task& task) {
		m_queue.Put(task);
	}
private:
	void Start(int numThreads) {
		m_running = true;
		for (int i = 0; i < numThreads; ++i) {
			m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
		}
	}
	void RunInThread() {
		while (m_running) {
			std::list<Task> list;
			m_queue.Take(list);	// take all
			for (auto& task : list) {
				if (!m_running)
					return;
				cout << "do task, by Async thd ID:" << this_thread::get_id() << endl;
				task();
			}
		}
	}
	void StopThreadGroup() {
		m_queue.Stop();
		m_running = false;
		for (auto thread : m_threadgroup) {
			if (thread)
				thread->join();
		}
		m_threadgroup.clear();
	}
private:
	std::list<std::shared_ptr<std::thread>> m_threadgroup;
	SyncQueue<Task> m_queue;
	atomic_bool m_running;
	std::once_flag m_flag;
};

void TestThdPool() {
	ThreadPool pool(2);
	std::thread thd1([&pool] {
		for (int i = 0; i < 5; ++i) {
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId] {
				cout << "SyncLayer Thd1 ID:" << thdId << endl;
			});
		}
	});
	std::thread thd2([&pool] {
		for (int i = 0; i < 5; ++i) {
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId] {
				cout << "SyncLayer Thd2 ID:" << thdId << endl;
			});
		}
	});
	this_thread::sleep_for(std::chrono::seconds(5));
	getchar();
	pool.Stop();
	thd1.join();
	thd2.join();
}

int main(int argc, const char * argv[]) {
	TestClassFunc();
	cout << "/////////////////////" << endl;
	TestThdPool();

	return 0;
}
