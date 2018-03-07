
#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <map>

using namespace std;


template<typename T>
void sort_1(deque<T>& dq)
{
	std::sort(dq.begin(),dq.end());
}

template<typename T>
void sort_2(deque<T>& dq)
{
	map<T,int> mpp;
	int capa=dq.size();
	for(int i=0;i<capa;++i){
		auto dqcur=dq.back();
		dq.pop_back();
		mpp.insert(pair<T,int>(dqcur,0));
	}
	for(auto it=mpp.begin();it!=mpp.end();++it){
		dq.push_back(it->first);
	}
}

template<typename T>
void sort_3(deque<T>& dq)
{
	int capa=dq.size();
	T arrtmp[capa];


}


template<typename T>
void printarr(const deque<T>& dq)
{
	auto it=std::begin(dq);
	for(;it!=dq.end();++it)
		cout<<*it<<" ";
	cout<<endl;
}

int main(int argc, char* argv[])
{
	std::deque<int> dq1{4,2,6,1,9,8};
	printarr(dq1);
	sort_2(dq1);
	printarr(dq1);

	std::deque<string> dq2{"Bb","Aa","pP","Ee"};
	printarr(dq2);
	sort_1(dq2);
	printarr(dq2);
	
	return 0;
}




