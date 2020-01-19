#include <string.h>
#include <iostream>

void ReplaceBlank(char string[], int length)
{
	if (string == nullptr || length <= 0)
		return;

	int blankNum = 0;
	int oriLen = strlen(string) + 1;
	for (int i = 0;; ++i) {
		if (' ' == string[i]) {
			blankNum++;
		}
		else if ('\0' == string[i]){
			break;
		}
	}
	char* oriEnd = string + strlen(string);
	char* dstEnd = oriEnd + blankNum * 2;
	// need to judge before replace str!
	if (oriLen + blankNum * 2 > length)
		return;
	while (oriEnd != dstEnd && oriEnd >= string)
	{
		if (' ' != *oriEnd) {
			strncpy(dstEnd, oriEnd, 1);
		}
		else {
			dstEnd -= 2;
			strncpy(dstEnd, "%20", 3);
		}
		oriEnd--;
		dstEnd--;
	}
}


int main(int argc, char* argv[])
{
	using namespace std;
	char str[100] = "We are happy.";
	cout << str << endl;
	ReplaceBlank(str, 100);
	cout << str << endl;
	return 0;
}