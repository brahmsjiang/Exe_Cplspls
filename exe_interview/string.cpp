#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string ostr("GET / HTTP / 1.1");
    size_t ops = ostr.find("/");
    cout << ops << endl;
    ops = ostr.find("/");
    cout << ops << endl;
    return 0;
}