#include <iostream>

#define ROW 4
#define COLUMN 4

void PrintMatrixClockwisely(int **numbers, int columns, int rows) { //有错待查
	int i, j, k;
	k = 0;
	while (true) {
		if (k >= columns - k - 1) {
			std::cout << numbers[k][k] << " ";
			break;
		}
		for (j = k; j < columns - k - 1; j++) 
			std::cout << numbers[k][j] << " ";

		if (k >= rows - k - 1) {
			std::cout << numbers[k][columns - k - 1] << " ";
			break;
		}
		for (i = k; i < rows - k - 1; i++) 
			std::cout << numbers[i][columns - k - 1] << " ";

		if (columns - k - 1 <= k) {
			std::cout << numbers[rows - k - 1][columns - k - 1] << " ";
			break;
		}
		for (j = columns - k - 1; j > k; j--)
			std::cout << numbers[rows - k - 1][j] << " ";

		if (rows - k - 1 <= k) {
			std::cout << numbers[rows - k - 1][k] << " ";
			break;
		}
		for (i = rows - k - 1; i > k; i--)
			std::cout << numbers[i][k] << " ";

		k++;
	}
}

void PrintMatrixInCircle(int **numbers, int columns, int rows, int start) {
	int endX = columns - 1 - start;
	int endY = rows - 1 -start;

	// 从左到右打印一行
	for (int j = start; j <= endX; j++) 
		std::cout << numbers[start][j] << " ";

	// 从上到下打印一列
	if (start < endY) {
		for (int i = start + 1; i <= endY; i++) 
			std::cout << numbers[i][endX] << " ";
	}

	// 从右到左打印一行
	if (start < endX && start < endY) {
		for (int j = endX - 1; j >= start; j--) 
			std::cout << numbers[endY][j] << " ";
	}

	if (start < endX && start < endY - 1) {
		for (int i = endY - 1; i >= start + 1; i--)
			std::cout << numbers[i][start] << " ";
	}
}

void PrintMatrix(int **numbers, int columns, int rows) {
	if (numbers == NULL || columns <= 0 || rows <= 0)
		return;

	int start = 0;

	while (columns > start * 2 && rows > start * 2) {
		PrintMatrixInCircle(numbers, columns, rows, start);

		++start;
	}

	std::cout << std::endl;
}



int main() {
	int **nums = new int* [ROW];
	for (int i = 0; i < ROW; i++)
		nums[i] = new int[COLUMN];

	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COLUMN; j++)
			nums[i][j] = COLUMN * i + j + 1;

	PrintMatrixClockwisely(nums, COLUMN, ROW);
	PrintMatrix(nums, COLUMN, ROW);

	return 0;
}