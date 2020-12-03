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
    T& maxVal();

private:
    queue<T> maxQue; //maxval in tail
    queue<T> dataQue;
};

template<typename T>
void CQueue<T>::push(const T& val)
{
    dataQue.push(val);
    if (maxQue.empty() || maxQue.back() < val)
        maxQue.push(val);
    else
        maxQue.push(maxQue.back());
}

template<typename T>
void CQueue<T>::pop()
{
    if (!dataQue.empty() && !maxQue.empty())
    {
        dataQue.pop();
        maxQue.pop();
    }
}

template<typename T>
T& CQueue<T>::maxVal()  //T& CQueue<T>::maxVal()
{
    assert(maxQue.size() > 0);
    return maxQue.back();
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

    for (int i = size; i < num.size(); ++i)
    {
        curQueue.pop();
        curQueue.push(num[i]);        
        maxInWins.push_back(curQueue.maxVal());
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