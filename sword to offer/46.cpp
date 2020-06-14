#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int layer = 0;
void printTab(int layer)
{
    for (size_t i = 0; i < layer; i++)
        printf("    ");
}

int getTransCount1(const string& number)
{
    ++layer;
    printTab(layer);

    cout << "==>cur number:" << number << endl;

    if (number.empty())
    {
        printTab(layer);
        cout << "count: 1" << endl;
        --layer;
        return 1;
    }

    int count = 0;
    char curNumberstr[3];
    memset(curNumberstr, 0, sizeof(curNumberstr) / sizeof(char));

    //last char
    string numbertmp = number;
    numbertmp.pop_back();
    printTab(layer);
    cout << "before getTransCount, use cur char1" << endl;
    count = getTransCount1(numbertmp);

    //second last two char
    if (number.size() >= 2)
    {
        strcat(curNumberstr, number.substr(number.size() - 2, 2).c_str());
        if (10 <= atoi(curNumberstr) && atoi(curNumberstr) <= 25)
        {
            numbertmp.pop_back();
            printTab(layer);
            cout << "before getTransCount, use cur char2" << endl;
            count += getTransCount1(numbertmp);
        }
    }
   
    printTab(layer);
    cout << "count: " << count << endl;

    --layer;
    return count;
}

int getTransCount2(const string& number)
{
	int length = number.length();
	int* counts = new int[length];
	int count = 0;
	
	for (size_t i = length - 1; i >= 0; --i)
	{
		count = 0;
		if (i < length - 1)
			count = counts[i + 1];
		else
			count = 1;

		if (i < length - 1)
		{
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int converted = digit1 * 10 + digit2;
			if (converted >= 10 && converted <= 25)
			{
				if (i < length - 2)
					count += counts[i + 2];
				else
					count += 1;
			}
		}
		counts[i] = count;
	}

	count = counts[0];
	delete[] counts;

	return count;
}

int getTransCount(int number)
{
    if (number < 0)
        return 0;

    string numberInStr = std::to_string(number);
    return getTransCount2(numberInStr);
}

int main(int argc, char* argv[])
{
    cout << getTransCount(0) << endl;
    cout << getTransCount(10) << endl;
    cout << getTransCount(125) << endl;
    cout << getTransCount(126) << endl;
    cout << getTransCount(426) << endl;
    cout << getTransCount(100) << endl;
    cout << getTransCount(101) << endl;
    cout << getTransCount(12258) << endl;
    cout << getTransCount(-100) << endl;
    return 0;
}