#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <stack>
#include <queue>


using namespace std;

vector<int> maxInWindows_1(const vector<int>& num, unsigned int size)
{
    vector<int> maxInWins;
    //it + size <= num.end() would cause dump
    for (vector<int>::const_iterator it = num.begin(); it <= (num.end() - size); ++it)
    {
        int curMaxInWins = 0;
        for (vector<int>::const_iterator itSub = it; itSub < (it + size); ++itSub)
        {
            if (*itSub > curMaxInWins)
                curMaxInWins = *itSub;
        }
        maxInWins.push_back(curMaxInWins);
    }
    return maxInWins;
}

vector<int> maxInWindows_2(const vector<int>& num, unsigned int size)
{
    vector<int> maxInWins;
	if (num.size() >= size && size >= 1)
	{
		deque<int> maxQue;
		for (size_t i = 0; i < size; i++)
		{
			if (maxQue.empty() || maxQue.front() < num[i])
				maxQue.emplace_front(num[i]);
			else
				maxQue.push_back(num[i]);
		}
		maxInWins.push_back(maxQue.front());

		for (size_t i = size; i < (num.size() - size); i++)
		{
			if (maxQue.front() < num[i])
				maxQue.emplace_front(num[i]);
			else
				maxQue.push_back(num[i]);
			maxInWins.push_back(maxQue.front());
		}
	}
	return maxInWins;

}

int main(int argc, char* argv[])
{
    vector<int> vec1 = { 2,3,4,2,6,2,5,1 };
    auto res1 = maxInWindows_1(vec1, 3);
    auto res2 = maxInWindows_2(vec1, 3);
    return 0;
}