#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include "assert.h"

char FirstNotRepeating_1(char* pString)
{
    for (int i = 0; i < strlen(pString); ++i)
    {
        char curChr = pString[i];
        bool DuplicateFlg = false;
        for (int j = i + 1; j < strlen(pString); ++j)
        {
            if (curChr == pString[j])
            {
                DuplicateFlg = true;
                break;
            }
        }
        if (!DuplicateFlg)
            return curChr;
    }
    return EOF;
}

char FirstNotRepeating_2(char* pString)
{

}

int main(int argc, char* argv[])
{
    char res0 = FirstNotRepeating_1("")
    return 0;
}