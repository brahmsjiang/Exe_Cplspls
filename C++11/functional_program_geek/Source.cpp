#include "istream_line_reader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric> //accumulate 

using namespace std;

int count_file(const char* name)
{
    int count = 0;
    ifstream ifs(name);//default ifstream::in
    string line;
    for (;;)
    {
        getline(ifs, line);
        if (!ifs) {
            break;
        }
        ++count;
    }
    return count;
}

int count_lines(const char** begin, const char** end)
{
    int count = 0;
    for (; begin != end; ++begin)
    {
        count += count_file(*begin);
    }
    return count;
}

int count_file_transform(const char* name)
{
    ifstream ifs(name);
    istream_line_reader reader(ifs);
    return distance(reader.begin(), reader.end());

    /*
    int count = 0;
    for (auto&& line : istream_line_reader(ifs)) {
        ++count;
    }
    return count;
    */
}

int count_lines_transform(const char** begin, const char** end)
{
    vector<int> count(end - begin);//initialize with (end - begin) elements

    transform(begin, end, count.begin(), count_file_transform);
    return accumulate(count.begin(), count.end(), 0);//return accumulate val from begin to end, based on the initial val of the sum
}

int main(int argc, const char** argv)
{
    int total_lines = count_lines_transform(argv + 1, argv + argc);
    cout << total_lines << endl;

    return 0;
}