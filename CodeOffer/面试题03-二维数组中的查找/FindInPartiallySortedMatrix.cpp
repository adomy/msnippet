#include <iostream>

bool find(int matrix[], int RowCnt, int ColumnCnt, int target) {

	if (matrix == NULL || RowCnt == 0 || ColumnCnt == 0)
		return false;

	int i = RowCnt - 1, j = 0;
	while (i >= 0 && j < ColumnCnt) {
		if (matrix[i * ColumnCnt + j] > target) {
			i--;
		} else if (matrix[i * ColumnCnt + j] < target) {
			j++;
		} else {
			return true;
		}
	}

	return false;
}

int main() {
	int matrix[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
	int t;
	std::cin >> t;
	std::cout << find(matrix, 4, 4, t) << std::endl;

	return 0;
}