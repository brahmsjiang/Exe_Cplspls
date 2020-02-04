#include <iostream>

using namespace std;

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited);
int movingCount(int threshold, int rows, int cols)
{
	if (0 > threshold || 0 >= rows || 0 >= cols)
		return 0;
	
	bool* visited = new bool[rows * cols];
	//need initialize
	for (int i = 0; i < rows * cols; ++i)
		visited[i] = false;

	//col,row from (0,0) to (rows-1,cols-1)
	int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
	delete[] visited;
	return count;
}

int movingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited)
{
	if (0 > row || row >= rows || 0 > col || col >= cols
		|| nullptr == visited || visited[row * cols + col])
		return 0;

	visited[row * cols + col] = true;
	int count = 0;
	if (row / 10 + row % 10 + col / 10 + col % 10 <= threshold)//if cur grid cannot enter, no need to walk near grid again
	{
		count = 1 + movingCountCore(threshold, rows, cols, row - 1, col, visited)
			+ movingCountCore(threshold, rows, cols, row + 1, col, visited)
			+ movingCountCore(threshold, rows, cols, row, col - 1, visited)
			+ movingCountCore(threshold, rows, cols, row, col + 1, visited);
	}

	return count;
}

int main(int argc, char* argv[])
{
	cout << movingCount(18, 1, 8) << endl;
	cout << movingCount(18, 2, 8) << endl;
	cout << movingCount(8, 3, 8) << endl;
	cout << movingCount(0, 3, 8) << endl;
	cout << movingCount(6, 3, 8) << endl;
	cout << movingCount(15, 1, 1) << endl;
	cout << movingCount(0, 1, 1) << endl;
	cout << movingCount(-10, 10, 10) << endl;
	return 0;
}