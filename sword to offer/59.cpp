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

///////
template<typename T>
class CQueue
{
public:
    void push(const T& val);
    void pop();
    const T& maxVal();

private:
    stack<T> maxStk;
    stack<T> dataStk;
};

template<typename T>
void CQueue::push(const T& val)
{
    dataStk.push(val);
    if (maxStk.empty() || maxStk.top() < val)
        maxStk.push(val);
    else
        maxStk.push(dataStk.top());
}

template<typename T>
void CQueue::pop()
{
    if ()
    {
    }
}

template<typename T>
const T& CQueue::maxVal();
{
    assert(dataStk.size() > 0 && maxStk.size() > 0);
    return maxStk.top();
}

vector<int> maxInWindows_2(const vector<int>& num, unsigned int size)
{
    vector<int> maxInWins;
    CQueue<int> curQueue;

    if (num.size() < size)
        return maxInWins;

    for (int i = 0; i < size; ++i)
    {
        curQueue.push(num[i]);
    }
    maxInWins.push_back(curQueue.maxVal());

    for (int i = 1; i <= (num.size() - size); ++i)
    {
        curQueue.push(*it);
        int curMaxInWins = 0;
        
        maxInWins.push_back(curMaxInWins);
    }
    return maxInWins;
}


int main(int argc, char* argv[])
{
    vector<int> vec1 = { 2,3,4,2,6,2,5,1 };
    auto res1 = maxInWindows_1(vec1, 3);
    return 0;
}