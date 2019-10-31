#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool cmp(const pair<int, char>& a, const pair<int, char>& b)
{
    return a.first < b.first;
}

int main()
{
    vector<pair<int, char>> p;
    p.push_back(make_pair(10, 'a'));
    p.push_back(make_pair(9, 'c'));
    p.push_back(make_pair(10, 't'));
    p.push_back(make_pair(17, 'y'));
    p.push_back(make_pair(10, 'b'));
	
    sort(p.begin(), p.end(), cmp);
    for (auto i = 0; i < p.size(); ++i)
        cout << p[i].first << " " << p[i].second << endl;
    cout << endl;

    p.erase(p.begin());//erase delete element by iterator
    for (auto i = 0; i < p.size(); ++i)
        cout << p[i].first << " " << p[i].second << endl;
	cout << endl;

    cout << "end ele first: "<< p.end()->first << " second: " << p.end()->second << endl;
    cout << "end ele first: "<< (end(p)-1)->first << " second: " << (end(p)-1)->second << endl;
    p.erase(end(p)-1);
    for (auto &i : p)    //auto &i means can change
        cout << i.first << " " << i.second << endl;


    
    return 0;
}
