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
    int val;
};

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
        //for sort, third para accepts a binary function
        sort(vUser.begin(), vUser.end(), less<userdefined>());

        vector<int> v{ 13,6,4,11,29 };
        sort(v.begin(), v.end());//default is less
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
        cout << "lower_bound second: " << mmp.lower_bound("four")->second << endl;//!(x < k)
        cout << "upper_bound second: " << mmp.upper_bound("four")->second << endl;//k < x
    }





    system("pause");
    return 0;
}

