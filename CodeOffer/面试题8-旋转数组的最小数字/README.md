[TOC]



# 题目

**内容**：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。

例如，数组{3, 4, 5, 1, 2}为{1, 2, 3, 4, 5}，该数组的最小值为1。

# 思路

对于该题，最朴实的思路就是，遍历一次数组，用一个临时变量存储当前最小元素。遍历完成后，临时变量存储的即为最小值。该方法的时间复杂度为O(n)。但是，仅仅这样做是极为低效的，我们需要寻找更加高效的方法来解决这个问题。

我们注意到旋转之后的数组实际上可以划分为两个排序的子数组，而且前面的子数组的元素都大于或等于后面子数组的元素。我们还可以注意到最小的元素刚好是这两个子数组的分界线。

我们可以试着用二分查找法的思路来寻找这个最小的元素。

在具体讲述二分查找法的方法之前，我们需要注意以下几点：

* 如果数组旋转为0，则表示数组从第0个元素到第n-1个元素是递增的，此时，我们只需返回第0个元素，即为该旋转数组的最小元素。
* 如果数组存在相同值，如{1, 0, 1, 1, 1}，第一个数字和最后一个数字和中间数字都是1，此时，我们无法确定中间的数字1是属于第一个递增子数组还是第二个递增子数组。因此，此时，可以采用O(n)复杂度的常规方法进行最小值寻找。

现在，我们来仔细分析如何用二分查找的方法来寻找最小值。

假设数组为nums[]，我们设定两个索引low_i和high_i，分别指向数组的第一个元素和最后一个元素。现在，利用二分思想，我们找到中间元素mid_i（其中mid_i = (low_i + high_i) / 2），做出如下判断：

* 如果nums[mid_i] >= nums[high_i]，此时，表明中间元素大于最后一个元素。因此，我们可以肯定，最小值位于中间索引mid_i和最后一个元素索引high_i之间。故，设定low_i = mid_i + 1；
* 如果nums[mid_i] < nums[high_i]，此时，表明中间元素小于最后一个元素。因此，我们可以肯定，最小值位于最先索引low_i和中间索引mid_i之间（含中间索引）。故，设定high_i = mid_i；
* 循环条件：low_i < high_i。为什么不能等于？准确地说，low_i <= high_i是可以的，但是，low_i == high_i时，mid_i == low_i == high_i。故，该步骤是多余的，不如直接省略。
* 返回值：nums[low_i]。

综上所述，整个核心代码如下：

``` c++
int MinNumberInRotatedArray(int *numbers, int length) {
	if (numbers == NULL || length <= 0)
		throw new std::exception("Invalid parameters.");

	int low_i = 0;
	int high_i = length - 1;
	int mid_i = 0;

	while (low_i < high_i) {
		if (numbers[low_i] < numbers[high_i])
			return numbers[low_i];

		if (numbers[low_i] == numbers[high_i]) {
			int min = numbers[low_i];
			for (int i = low_i + 1; i <= high_i; i++) {
				if (min > numbers[i])
					min = numbers[i];
			}

			return min;
		}

		mid_i = (low_i + high_i) / 2;
		
		if (numbers[mid_i] >= numbers[high_i])
			low_i = mid_i + 1;
		else
			high_i = mid_i;
	}

	return numbers[low_i];
}
```



# 测试用例

* 功能测试（输入的数组是升序排序数组的一个旋转，数组中有重复数字或者没有重复数字）。
* 边界值测试（输入的数组是一个升序排序的数组、只包含一个数字的数组）。
* 特殊输入测试。

