#include <iostream>
#include <list>
#include <assert.h>

using namespace std;

int LastRemaining(unsigned int n, unsigned int m)
{
    if (n < 1 || m < 1)
        return -1;

    list<int> circle;
    for (int i = 0; i < n; ++i)
        circle.push_back(i);
    
    list<int>::iterator curIt = circle.begin();
    list<int>::iterator nxtIt;

    while (circle.size() > 1)
    {
        for (int i = 1; i < m; ++i)
        {
            curIt++;
            if (curIt == circle.end())//simulate a circular list
                curIt = circle.begin();
        }

        nxtIt = ++curIt;//use nxtIt for curIt become invalid if execute erase()
        if (nxtIt == circle.end())
            nxtIt = circle.begin();
        circle.erase(--curIt);
        curIt = nxtIt;
    }
    return circle.back();
}

int LastRemaining2(unsigned int n, unsigned int m)
{
    return 0;
}


int main(int argc, char* argv[])
{
    auto res1 = LastRemaining(8, 3);
    return 0;
}