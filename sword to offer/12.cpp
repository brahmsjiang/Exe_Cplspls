#include <iostream>
#include <stack>

using namespace std;

struct vec2 {
	vec2(int ro, int co){
		row = ro;
		col = co;
	}
	int row;
	int col;
};

bool hasPathCore(const char* matrix, int rows, int cols, int row,
	int col, const char* str, int& pathLength, bool* visited, stack<vec2>& stk);
bool hasPath(char* matrix, int rows, int cols, char* str)
{
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
		return false;

	bool* visited = new bool[rows * cols];

	stack<vec2> stk;
	memset(visited, 0, rows * cols);

	int pathLength = 0;
	for (int row = 0; row < rows; ++row)	//row & col from 0
	{
		for (int col = 0; col < cols; ++col)
		{
			if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited, stk)) {
				cout << "trace: ";
				while (!stk.empty())
				{
					cout << "[" << stk.top().row << "," << stk.top().col << "];";
					stk.pop();
				}
				cout << endl;
				return true;
			}
		}
	}
	delete[] visited;

	return false;
}

bool hasPathCore(const char* matrix, int rows, int cols, int row,
	int col, const char* str, int& pathLength, bool* visited, stack<vec2>& stk)
{
	if (str[pathLength] == '\0')//must judge first
		return true;

	if (visited[row * cols + col]
		|| col < 0 || col >= cols || row < 0 || row >= rows)
		return false;

	if (matrix[row * cols + col] == str[pathLength]) {
		pathLength++;
		visited[row * cols + col] = true;
		stk.push(vec2(row, col));
	}
	else {
		return false;
	}

	
	bool hasPath = hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited, stk)
		|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited, stk)
		|| hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited, stk)
		|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited, stk);
	
	if (!hasPath)
	{
		pathLength--;
		visited[row * cols + col] = false;
		stk.pop();
	}

	return hasPath;
}

int main(int argc, char* argv[])
{
	char matrix1[] = { 'n', 'b', 't', 'g', 'c', 'f', 'c', 's', 'j', 'd', 'e', 'h' };
	char matrix2[] = { 'b', 'b', 'b', 'b', 'c', 'b', 'c', 's', 'j', 'd', 'e', 'h' };
	char matrix3[] = { 'b', 'f', 'c', 'e'};
	char matrix4[] = { 'b', 'f', 'c', 'e' };
	char matrix5[] = { 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c' };
	char* tarstr = "bfce";
	cout << hasPath(matrix1, 3, 4, tarstr) << endl;
	cout << hasPath(matrix2, 3, 4, tarstr) << endl;
	cout << hasPath(matrix3, 1, 4, tarstr) << endl;
	cout << hasPath(matrix4, 4, 1, tarstr) << endl;
	cout << hasPath(matrix5, 4, 2, tarstr) << endl;
	cout << hasPath(matrix5, 2, 4, tarstr) << endl;
	return 0;
}