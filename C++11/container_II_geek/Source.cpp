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
#include <unordered_map>
#include <unordered_set>
#include <complex>
#include <iterator>     //std::size
#include <array>


using namespace std;

//һ�㲻�����û���std�������
namespace std {

    template <typename T>
    struct hash<complex<T>>
    {
        size_t operator()(const complex<T>& v) const noexcept
        {
            cout << "hash<complex<T>\n";
            hash<T> h;
            return h(v.real()) + h(v.imag());
        }
    };
}

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

//��������ض����Ͷ�less�����ػ�
template<>
struct less<userdefined> {
    bool operator()(const userdefined& x, const userdefined& y) const
    {
        cout << "less<userdefined>::operator()" << endl;
        return x.val < y.val;
    }
};

void test(int arr[])
{
    //compile err
    //cout << std::size(arr) << endl;
}

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
        cout << "lower_bound second: " << mmp.lower_bound("four")->second << endl;//��һ����С�ڼ�k��Ԫ��
        cout << "upper_bound second: " << mmp.upper_bound("four")->second << endl;//��һ�����ڼ�k��Ԫ��
		cout << "--upper_bound second: " << (--mmp.upper_bound("four"))->second << endl;
		
		multimap<string, int>::iterator lower, upper;
		//std::tie������ֵ���õ�tuple�������ڽ��pair,��Ϊtupleӵ�д�pair��ת����ֵ
		{
			struct S {
				int n;
				std::string s;
				float d;
				bool operator<(const S& rhs) const
				{
					// �Ƚ�n��rhs.n; s��rhs.s,d��rhs.d
					return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
				}
			};

			set<S> set_of_s;
			S val{ 42,"Test",3.14 };
			set<S>::iterator iter;
			bool inserted;
			//���insert�ķ���ֵiter �� inserted
			std::tie(iter, inserted) = set_of_s.insert(val);
		}
		//equal_range returns a pair
		std::tie(lower, upper) = mmp.equal_range("four");//�뿪���
		assert(lower != upper);

		using pairIt = multimap<string, int>::iterator;
		pairIt lower1, upper1;
		std::pair<pairIt, pairIt> resp = mmp.equal_range("four");
		lower1 = resp.first;
		upper1 = resp.second;
		cout << "----------\n";
		cout << lower1->second << endl;//lower is a iter of map
		cout << (--upper1)->second << endl;//map/list/set�ĵ���������˫�������
	}
    {
        unordered_set<int> s{ 1,1,2,3,5,8,13,21 };
        unordered_map<complex<double>, double> umc{ {{1.0, 1.0}, 1.4142},{ { 3.0, 4.0 }, 5.0 } };
    }
    {
        int arr[] = { 1,2,3,4,5 };
        cout << "The array length is " << std::size(arr) << endl;
        test(arr);

        typedef char mykey_t[8];
        //C����Ҳû�����ø�����Ϊ���޷���Ϊmap/unordered_map�ļ�
        map<mykey_t, int> mp;
        mykey_t myket{ "hello" };
        //mp[myket] = 5;//compile err


        typedef std::array<char, 8> mykey_t2;
        map<mykey_t2, int> mp2;
        mykey_t2 myket2{ "hello" };
        mp2[myket2] = 5;//ok
    }



    system("pause");
    return 0;
}

