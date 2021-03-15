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

using namespace std;

void interface_string_test1(const string& str)
{
    cout << "interface_string_test1: " << str << endl;
}

void interface_string_test2(const char* str)
{
    cout << "interface_string_test2: " << str << endl;
}

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
    v1.clear();
    v1.reserve(99);
    cout << "v1 size: " << v1.size() << " v1 capacity: " << v1.capacity() << "\n";//reserve could only increase the capacity


    list<int> l1{ 1,2,3,4,5 };
    cout << l1.front() << l1.back() << *l1.begin() << endl;

    system("pause");
    return 0;
}











