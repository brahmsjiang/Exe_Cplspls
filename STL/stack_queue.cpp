
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

int main(int argc, char* argv[])
{
	stack<int, vector<int>> s;
	queue<int, deque<int>> q;
	
	for(int i=1;i<10;i++)
	{
		s.push(i);
		q.push(i);
	}
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
	}
	while(!q.empty()){
		cout<<q.front()<<endl;
		q.pop();
	}
	return 0;
}

