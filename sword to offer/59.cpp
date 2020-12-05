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
		deque<int> index;
		for (size_t i = 0; i < size; i++)
		{
			while (!index.empty() && num[index.back()] < num[i])
				index.pop_back();

			index.push_back(i);
		}

		for (size_t i = size; i < num.size(); i++)
		{
			maxInWins.push_back(num[index.front()]);

			while (!index.empty() && num[index.back()] < num[i])
				index.pop_back();
			if (!index.empty() && size <= (i - index.front()))
				index.pop_front();

			index.push_back(i);
		}
		maxInWins.push_back(num[index.front()]);
	}
	return maxInWins;
}

template<typename T>
class QueueWithMax
{
public:
	QueueWithMax():curIdx(0)
	{}

	void push_back(T number)
	{
		while (!maxVal.empty() && number >= maxVal.back().number)
			maxVal.pop_back();

		InternalData internalData = { number, curIdx };
		data.push_back(internalData);
		maxVal.push_back(internalData);

		++curIdx;
	}

	void pop_front()
	{
		if (maxVal.empty())
			throw new exception("queue is empty");

		if (maxVal.front().index == data.front().index)
			maxVal.pop_front();

		data.pop_front();
	}

	T max() const
	{
		if (maxVal.empty())
			throw new exception("queue is empty");

		return maxVal.front().number;
	}
private:
	struct InternalData
	{
		T number;
		int index;
	};
	deque<InternalData> data;
	deque<InternalData> maxVal;
	int curIdx;
};

int main(int argc, char* argv[])
{
    vector<int> vec1 = { 2,3,4,2,6,2,5,1 };
    auto res1 = maxInWindows_1(vec1, 3);
	for (auto i : res1)
		cout << i << " ";
	cout << endl;
    auto res2 = maxInWindows_2(vec1, 3);
	for (auto i : res2)
		cout << i << " ";
    return 0;
}