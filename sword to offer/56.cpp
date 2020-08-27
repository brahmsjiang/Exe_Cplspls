#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>

void FineNumberAppearOnce(int data[], int len, int& num1, int& num2)
{
    if (data == nullptr || len < 2)//do not forget it
        return;

    int curRes = 0;
    //^ means 'xor' operator, no 'xnor' operator in C, but can use ! to 'not' xor res
    for (int i = 0; i < len; ++i)
        curRes ^= data[i];

    assert(curRes);
    int non_zeroNum = 1;
    while (curRes)
    {
        if (curRes & 0x01)
            break;

        curRes >>= 1;
        non_zeroNum <<= 1;
    }

    assert(non_zeroNum);
    for (int i = 0; i < len; ++i)
    {
        if (data[i] & non_zeroNum)
            num1 ^= data[i];
        else
            num2 ^= data[i];
    }

#if 0
    //no need to use extra two vector
    std::vector<int> subV1, subV2;
    for (int i = 0; i < len; ++i)
    {
        if (non_zeroNum & data[i])
            subV1.push_back(data[i]);
        else
            subV2.push_back(data[i]);
    }

    for (std::vector<int>::iterator it = subV1.begin(); it != subV1.end(); ++it)
    {
        num1 ^= *it;
    }
    for (std::vector<int>::iterator it = subV2.begin(); it != subV2.end(); ++it)
    {
        num2 ^= *it;
    }
#endif
}

int main(int argc, char* argv[])
{
    int vec[] = { 2,3,9,3,2,7,5,5,7,6 };
    int res1 = 0, res2 = 0;
    FineNumberAppearOnce(vec, sizeof(vec) / sizeof(int), res1, res2);
    return 0;
}