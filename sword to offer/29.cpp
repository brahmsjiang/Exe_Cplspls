#include <iostream>
#include <memory>
#include <stack>
#include <assert.h>
#include <queue>

using namespace std;

void PrintMatrixCircle(int** num, int columns, int rows, int start);

void PrintMatrixClockwisely(int** num, int columns, int rows)
{
	if(num == nullptr || columns <= 0 || rows <= 0)
		return;
	int start = 0;
	while(columns > (start * 2) && rows > (start * 2))
	{
		PrintMatrixCircle(num, columns, rows, start);
		++start;
	}
}

void PrintMatrixCircle(int** num, int columns, int rows, int start)
{
	//num[row][column]
	int endX = columns - 1 - start;
	int endY = rows - 1 - start;
	//left to right
	for(int i = start; i <= endX; ++i)
	{
		cout << num[start][i] << " ";
	}
	//up to down
	if(start < endY)
	{
		for(int i = start + 1; i <= endY; ++i)
		{
			cout << num[i][endX] << " ";
		}
	}
	//right to left
	if(start < endX && start < endY)
	{
		for(int i = endX - 1; i >= start; --i)
		{
			cout << num[endY][i] << " ";
		}
	}
	//down to up
	if(start < endX && (start + 1) < endY)
	{
		for(int i = (endY - 1); i >= (start + 1); --i)
		{
			cout << num[i][start] << " ";
		}
	}
}

void Test(int columns, int rows)
{
	printf("Test Begin: %d columns, %d rows.\n", columns, rows);
	if(columns < 1 || rows < 1)
		return;
	int ** num = new int*[rows];
	for(int i = 0; i < rows; ++i)
	{
		num[i] = new int[columns];
		for(int j = 0; j < columns; ++j)
		{
			num[i][j] = i * columns + j + 1;
		}
	}
	PrintMatrixClockwisely(num, columns, rows);
	cout << endl;

	for(int i = 0; i < rows; ++i)
		delete[] (int*)num[i];
	
	delete[] num;
}



int main(int argc, char* argv[])
{
	Test(1, 1);
	Test(2, 2);
	Test(3, 3);
	Test(4, 4);
	Test(1, 5);
	Test(6, 2);
	
	return 0;
}


