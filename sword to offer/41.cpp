#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T>
class DynamicArray
{
public:
	void Insert(T num)
	{
		//even total size, add to right(min heap)
		if (((min.size() + max.size()) & 1) == 0)//through saved size whether is odd or not, because may don't know size of input stream
		{
			if (max.size() > 0 && num < max[0])
			{
				max.push_back(num);
				push_heap(max.begin(), max.end(), less<T>());
				num = max[0];

				pop_heap(max.begin(), max.end(), less<T>());
				max.pop_back();
			}
			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}
		//odd total size, add to left(max heap)
		else
		{
			
			if (min.size() > 0 && min[0] < num)
			{
				min.push_back(num);
				push_heap(min.begin(), min.end(), greater<T>());//push a ele to paticipate in heap sort

				num = min[0];

				pop_heap(min.begin(), min.end(), greater<T>());//pop a ele excluded then heap sort
				min.pop_back();
			}
			max.push_back(num);
			push_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()
	{
		int size = min.size() + max.size();
		if (size == 0)
			throw exception("No numbers are avaliable");

		T median = 0;
		if ((size & 1) == 1)
			median = min[0];
		else
			median = (min[0] + max[0]) / 2;

		return median;
	}

private:
	vector<T> min;
	vector<T> max;
};

int main(int argc, char* argv[])
{
	DynamicArray<int> arr;
	vector<int> nums = { 1,5,6,2,8,3,9,4,7 };
	for each (auto num in nums)
	{
		arr.Insert(num);
	}
	auto res = arr.GetMedian();
	return 0;
}