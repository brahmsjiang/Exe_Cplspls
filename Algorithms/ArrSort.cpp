
#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <map>

using namespace std;


template<typename T>
void sort_stdalg(deque<T>& dq)
{
	std::sort(dq.begin(),dq.end());
}

template<typename T>
void sort_map(deque<T>& dq)
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
void sort_bubble(deque<T>& dq)
{
	int capa=dq.size();
	T arrtmp[capa];
	for(int i=0;i<capa;++i){
		T dqcur=dq.back();
		dq.pop_back();
		arrtmp[i]=dqcur;
	}
	T i,j,tmp;
	for(i=0;i<capa;++i){
		for(j=capa-1;j>=i;--j){
			if(arrtmp[j]<arrtmp[j-1]){
				tmp=arrtmp[j];
				arrtmp[j]=arrtmp[j-1];
				arrtmp[j-1]=tmp;
			}
		}
	}
	for(int i=0;i<capa;++i){
		dq.push_back(arrtmp[i]);	
	}

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
	sort_stdalg(dq1);
	printarr(dq1);

	std::deque<string> dq2{"Bb","Aa","pP","Ee"};
	printarr(dq2);
	sort_map(dq2);
	printarr(dq2);
	
	std::deque<int> dq3{8,6,9,2,3,7};
	printarr(dq3);
	sort_bubble(dq3);
	printarr(dq3);
	
	return 0;
}




