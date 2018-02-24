
#include <iostream>
#include <queue>
#include <deque>
#include <vector>

#define ENTER {cout<<endl;}
using namespace std;

int main(int argc, char* argv[])
{
	queue<int,deque<int>> q;
	cout<<q.empty()<<endl;
	cout<<q.size()<<endl;
	for(int i=0;i<8;i++){
		q.push(i);
	}
	cout<<q.front()<<endl;
	cout<<q.back()<<endl;
	q.pop();
	cout<<q.front()<<endl;
	cout<<q.back()<<endl;

	//queue<int>::iterator itq;	//queue donot support iterator
	/////////////////////////////////////////////////////////////////
	deque<int> dq;
	cout<<dq.empty()<<endl;
	cout<<dq.size()<<endl;
	for(int i=0;i<8;i++){
		if(i<4)
			dq.push_front(i);//head insert
		else
			dq.push_back(i);//tail insert
	}
	ENTER
	for(deque<int>::iterator it=dq.begin();it<dq.end();it++){
		cout<<*it<<" ";
	}
	dq.pop_front();//head del
	dq.pop_back();//tail insert
	ENTER
	for(deque<int>::iterator it=dq.begin();it<dq.end();it++){
		cout<<*it<<" ";
	}
	ENTER
	return 0;
}

