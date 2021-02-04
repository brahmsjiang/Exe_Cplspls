#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string ostr("GET / HTTP / 1.1");
    size_t ops = ostr.find("/", 0);
    cout << ops << endl;
    ops = ostr.find("/", ops+1);
    cout << ops << endl;
    return 0;
}