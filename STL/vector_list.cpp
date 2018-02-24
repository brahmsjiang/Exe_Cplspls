
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main(void)
{
	vector<int> v;
	list<int> l;
	
	for(int i=0;i<8;i++)
	{
		v.push_back(i);
		l.push_back(i);
	}
	cout<<"v[2]="<<v[2]<<endl;
	//cout<<"l[2]="<<l[2]<<endl;
	cout<<"v.begin():"<<*(v.begin())<<" v.end()-1:"<<*(v.end()-1)<<" "<<(v.begin()<v.end())<<endl;
	//cout<<(l.begin()<l.end())<<endl;
	cout<<*(v.begin()+1)<<endl;

	vector<int>::iterator itv = v.begin();
	list<int>::iterator itl = l.begin();
	itv = itv+2;
	//itl = itl+2;
	itl++;itl++;
	cout<<*itv<<endl;
	cout<<*itl<<endl;

	for(;itv<v.end();itv++)
	{
		cout<<*itv<<" ";
	}
	cout<<endl;
#if 0	
	for(;itl!=l.end();itl++)
	{
		cout<<*itl<<" ";
	}
	
	cout<<endl;
	for(list<int>::iterator it=l.begin();it!=l.end();++it)
	{
		cout<<"~"<<*it<<endl;	//before erase and current iterator
		if(*it % 2 ==0)
		{
			it=l.erase(it);	//erase return the next iterator
			cout<<"~~"<<*it<<endl;	//after erase and current iterator
			it--;	//in loop,the iterator need to be minused by 1
		}
	}
	cout<<endl;
#endif
	for(vector<int>::iterator it=v.begin();it!=v.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	
	for(vector<int>::iterator it=v.begin();it<v.end();++it)
	{
		cout<<"-"<<*it<<endl;	//before erase and current iterator
		if(*it % 2 !=0)
		{
			v.erase(it);	//erase return the next iterator
			cout<<"--"<<*it<<endl;	//after erase and current iterator
			//it--;	//in loop,the iterator need to be minused by 1
		}
	}
	cout<<endl;
	for(vector<int>::iterator it=v.begin();it<v.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;

	vector<int> vv;
	cout<<vv.capacity()<<endl;
	vv.push_back(1);
	cout<<vv.capacity()<<endl;
	vv.reserve(3);
	vv.push_back(2);
	cout<<vv.capacity()<<endl;
	cout<<vv.size()<<endl;
	vv.push_back(3);
	vv.push_back(4);
	cout<<vv.capacity()<<endl;//capacity will double if cannot hold elements,so 3->6
	cout<<vv.size()<<endl;
	return 0;
}


