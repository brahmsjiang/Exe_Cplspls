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

using namespace std;

void interface_string_test1(const string& str)
{
    cout << "interface_string_test1: " << str << endl;
}

void interface_string_test2(const char* str)
{
    cout << "interface_string_test2: " << str << endl;
}

class Obj1
{
public:
	Obj1() { cout << "Obj1()\n"; }
	Obj1(const Obj1&) { cout << "Obj1(const Obj1&)\n"; }
	Obj1(Obj1&&) noexcept { cout << "Obj1(Obj1&&)\n"; }
};

class Obj2
{
public:
	Obj2() { cout << "Obj2()\n"; }
	Obj2(const Obj2&) { cout << "Obj2(const Obj2&)\n"; }
	Obj2(Obj2&&) { cout << "Obj2(Obj2&&)\n"; }
};

int main(int argc, char* argv[])
{
    const char* pchar1 = "constchar*";
    char* pchar2 = "char*";

    interface_string_test1(pchar1);
    interface_string_test1(pchar2);
    interface_string_test2(pchar1);
    interface_string_test2(pchar2);

#if 0
    string name;
    cout << "What's your name?";
    getline(cin, name);
    cout << "Nice to meet you, " << name << "!\n";
    cout << name.front() << name.back() << endl;
#endif

    vector<int> v1;
    for (auto it = 1; it <= 50; ++it)
    {
        v1.push_back(it);
        cout << "v1 capacity: " << v1.capacity() << "\n";//vs expands with 1.5 times; GCC with 2 times
    }
    cout << v1.front() << " " << v1.back() << " " << *v1.begin() << endl;
    v1.resize(40);
    cout << "v1 size: " << v1.size() << " v1 capacity: " << v1.capacity() << "\n";//resize can change, ignore the capacity
    v1.resize(70);
    cout << "v1 size: " << v1.size() << " v1 capacity: " << v1.capacity() << "\n";
    v1.reserve(99);
    cout << "v1 size: " << v1.size() << " v1 capacity: " << v1.capacity() << "\n";//reserve could only increase the capacity
	v1.pop_back();
	v1.push_back(69);
	v1.insert((v1.begin() + 3), 3);//insert a new ele at the iterator specified, the backward ele would be moved
	v1.erase(v1.begin() + 3);//del the ele at the iterator specified
	v1.emplace((v1.begin() + 3), 3);//result is the same as insert
	v1.emplace_back(999);
    cout << "*data: " << *(v1.data() + 1) << endl;//get raw ptr

	{
		vector<Obj1> v11;
		v11.reserve(1);
		v11.emplace_back();
		v11.emplace_back();

		vector<Obj2> v12;
		v12.reserve(1);
		v12.emplace_back();//just construct at back without para, copy/move construct is not called
		v12.emplace_back();
		//noexcept seems no difference in vs15
	}

    {
        deque<int> d1{ 1,2,3,4,5,6,7,8,9 };
        d1.push_front(0);
        d1.pop_front();
        d1.emplace_front(0);//construct int, if no para, the default val is 0
        //deque has no data/capacity/reserve func, because memory just continuous partially
        cout << "deque[] " << d1[9] << endl;//support [], because every chunk's size is the same
    }

    {
        list<int> l1{ 1,2,3,4,5 };
        //for list, random access such as begin()+x/[] not support; only ++/-- support
        l1.insert(l1.begin(), 3, 99);//para: pos, count, val

        l1.remove(99);//remove all eles with specific value
        l1.insert(l1.begin(), 99), l1.insert(l1.begin(), 88);
        l1.erase(++l1.begin());
        //because list::iterator can't random access, usr should calculate iter or use std::advanve/next 
        list<int>::iterator it1 = std::next(l1.begin(), list<int>::iterator::difference_type(2));//'2' offset (1 by default), shall only be negative for random/bidirectional iter
        l1.erase(it1);
        //or
        auto it2 = l1.end();
        std::advance(it2, -2);//advances the iter by n element pos
        l1.erase(it2);

        l1.push_front(0);
        l1.pop_front();
        l1.emplace_front(0);//C++11

        list<int> l2{ 1,7,2,8,3 };
        vector<int> v1{ 1,7,2,8,3 };
        sort(v1.begin(), v1.end());
        //sort(l2.begin(), l2.end());//compile err
        l2.sort();

        list<int> l3{ 1,7,2,8,3 };
    }

    {
        forward_list<int> l1{ 1,7,2,8,3 };
        //only allow add ele at front
    }

    //container adapter, realized by deque defaultly
    {
        queue<int> q;
        q.push(1);
        q.push(2);
        q.push(3);
        q.emplace(4);
        while (!q.empty())
        {
            cout << q.front() << " ";
            q.pop();
        }
        cout << endl;
    }

    {
        stack<int> s;
        s.push(1);
        s.push(2);
        s.push(3);
        s.emplace(4);
        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
    }
    system("pause");
    return 0;
}

