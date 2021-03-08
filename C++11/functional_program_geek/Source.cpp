#include <iostream>
#include <fstream>
#include <string>

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

int main(int argc, const char** argv)
{
    int total_lines = count_lines(argv + 1, argv + argc);
    cout << total_lines << endl;

    return 0;
}