//#include "output_container.h"

#include <stdlib.h>
#include <assert.h>

#include <algorithm>    //sort
#include <functional>   //less/greater/hash
#include <iostream>     //cout/endl
#include <string>       //string
#include <vector>       //vector
#include <queue>        //priotiry_queue
#include <set>
#include <map>


using namespace std;

class userdefined
{
public:
    userdefined(int v) : val(v) {}
	bool operator<(const userdefined& rhs) const
	{
		cout << "userdefined::operator<" << endl;
		less<int> lessfunc;
		return lessfunc(this->val, rhs.val);
	}
    int val;
};

//或者针对特定类型对less进行特化
template<>
struct less<userdefined> {
    bool operator()(const userdefined& x, const userdefined& y) const
    {
        cout << "less<userdefined>::operator()" << endl;
        return x.val < y.val;
    }
};


int main(int argc, char* argv[])
{
    {
        userdefined user6(6), user1(1), user3(3), user2(2);
        vector<userdefined> vUser{ user6,user1,user3,user2 };
		//for sort, no third binary func specified, operator must provide operator<
		sort(vUser.begin(), vUser.end());
		cout << "------------\n";
		vUser = { user6,user1,user3,user2 };
		//for sort, third para accepts a binary function
		//less<userdefined>() is just a temp obj
        sort(vUser.begin(), vUser.end(), less<userdefined>());

        vector<int> v{ 13,6,4,11,29 };
        sort(v.begin(), v.end());//default compare is less
        sort(v.begin(), v.end(), greater<int>());

        auto hp = hash<int*>();
        cout << "hash(nullptr) = " << hp(nullptr) << endl;
        cout << "hash(v.data()) = " << hp(v.data()) << endl;
        cout << "v.data() = " << static_cast<void*>(v.data()) << endl;

        auto hs = hash<string>();
        cout << "hash(\"hello\") = " << hs(string("hello")) << endl;
        cout << "hash(\"hellp\") = " << hs(string("hellp")) << endl;
    }
    {
        //use less as compare template para, the bigger one would appear at the top
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> q;
        q.push({ 1, 1 });
        q.push({ 2, 2 });
        q.push({ 0, 3 });
        q.push({ 9, 4 });
        while (!q.empty())
        {
            cout << q.top().first << " " << q.top().second << endl;//first/second value in the pair
            q.pop();
        }
    }
    {
        set<int> s{ 1,1,1,2,3,4 };

        multiset<int, less<int>> ms1{ 1,1,1,2,3,4 };
        multiset<int, greater<int>> ms2{ 1,1,1,2,3,4 };

        map<string, int> mp{ {"one",1},{"two",2},{"three",3},{"four",4} };
        cout << (mp.find("four") == mp.end()) << endl;
        cout << (mp.find("five") == mp.end()) << endl;
        mp["five"] = 5;


        multimap<string, int> mmp{ { "one",1 },{ "two",2 },{ "three",3 },{ "four",4 } };
        mmp.insert(pair<string, int>("four", -4));
        mmp.emplace("four", 0);//construct directly, err: mmp.emplace({ "four", 0 });
        cout << "second: " << mmp.find("four")->second << endl;
        cout << "lower_bound second: " << mmp.lower_bound("four")->second << endl;//第一个不小于键k的元素
        cout << "upper_bound second: " << mmp.upper_bound("four")->second << endl;//第一个大于键k的元素
		cout << "--upper_bound second: " << (--mmp.upper_bound("four"))->second << endl;
		
		multimap<string, int>::iterator lower, upper;
		//std::tie创建左值引用的tuple，或用于解包pair,因为tuple拥有从pair的转换赋值
		{
			struct S {
				int n;
				std::string s;
				float d;
				bool operator<(const S& rhs) const
				{
					// 比较n与rhs.n; s与rhs.s,d与rhs.d
					return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
				}
			};

			set<S> set_of_s;
			S val{ 42,"Test",3.14 };
			set<S>::iterator iter;
			bool inserted;
			//解包insert的返回值iter 与 inserted
			std::tie(iter, inserted) = set_of_s.insert(val);
		}
		//equal_range returns a pair
		std::tie(lower, upper) = mmp.equal_range("four");//半开半闭
		assert(lower != upper);

		using pairIt = multimap<string, int>::iterator;
		pairIt lower1, upper1;
		std::pair<pairIt, pairIt> resp = mmp.equal_range("four");
		lower1 = resp.first;
		upper1 = resp.second;
		cout << "----------\n";
		cout << lower1->second << endl;//lower is a iter of map
		cout << (--upper1)->second << endl;//map/list/set的迭代器都是双向迭代器
	}





    system("pause");
    return 0;
}

