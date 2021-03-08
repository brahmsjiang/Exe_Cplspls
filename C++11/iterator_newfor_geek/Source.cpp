#include "istream_line_reader.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>

using namespace std;



int main(int argc, char* argv[])
{
    vector<int> v1{ 1,2,3,4,5 };
    vector<int> v2;
    copy(v1.begin(), v1.end(), back_inserter(v2));

    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
}