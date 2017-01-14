[TOC]

# 题目

**内容**：输入一个矩阵，按照从外到里以顺时针的顺序依次打印出每个数字。

例如：输入以下矩阵：

1   2   3   4

5   6   7   8  

9  10 11 12

13 14 15 16

则依次打印出数字：1/2/3/4/8/12/16/15/14/13/9/5/6/7/11/10

# 思路

假设矩阵的行数是rows，列数是columns。打印第一圈的左上角的坐标是(0, 0)，第二圈的左上角的坐标是(1, 1)；依次类推。

我们可以注意到，左上角的坐标中行标和列标总是相同的，于是，可以在矩阵中选取左上角为(start, start)的一圈作为我们分析的目标。

对于一个$5\times5$的矩阵而言，最后一圈只有一个数字，对应的坐标为(2, 2)，我们发现$5>2\times2$。对于一个$6\times6$的矩阵而言，最后一圈有4个数字，其左上角的坐标仍然是(2, 2)。我们发现$6>2\times2$亦然成立。

于是，我们可以得出，循环继续的条件是$columns > startX\times2$且$rows>startY\times2$。

故详细代码为：

``` c++
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
```

接着，我们考虑如何打印一圈的功能，我们可以把打印一圈分为四步：第一步从左到右打印一行、第二步从上到下打印一列、第三步从右到左打印一行、第四步从下到上打印一列。

不过，值得注意的是，最后一圈有可能退化为只有一行、只有一列，甚至只有一个数字，因此，打印这样的一圈就不再需要四步。

详细代码为：

``` c++
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
```



