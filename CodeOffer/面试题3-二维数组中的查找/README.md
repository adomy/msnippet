[TOC]

# 题目

**内容**：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样一个二维数组和一个整数，判断数组中是否含有该整数。

例如，如下二维数组，每行每列递增排序。

1 2 8 9

2 4 9 12

4 7 10 13

6 8 11 15

如查找7，返回true；查找5，返回false。

# 思路

我们以左下角为参照点进行指定整数的查找。

令target为要查找的整数，二维数组为matrix[]，行数为RowCnt, 列数为ColumnCnt。

约定`matrix[i * ColumnCnt + j] <=> matrix[i][j]`

具体流程如下：

1. 初始化：当前行i = RowCnt - 1，当前列j = 0；
2. 如果 `target > matrix[i][j]` ，则i++；
3. 如果`target < matrix[i][j]`，则j--；
4. 如果`target == matrix[i][j] `，则返回true；
5. 当不满足`i >= 0 && j < RowCnt`时，结束，返回false。

详细源代码如下：

``` c++
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
```



另外，我们可以使用右上角作为参照点。

# 测试用例

* 二维数组中包含查找的数字（查找的数字是数组中的最大值和最小值，查找的数字介于数组中的最大值和最小值之间）。
* 二维数组中没有查找的数字（查找的数字大于数组中的最大值，查找的数字小于数组中的最小值，查找的数字在数组的最大值和最小值之间但数组中没有这个数字）。
* 特殊输入测试（空指针）。

推荐用例：

* 1
* 15
* 9
* -2
* 23
* 3

