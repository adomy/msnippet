[TOC]

# 题目

**内容**：输入一个整数数组，实现一个函数来调整该数组中数字的顺序。使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

# 思路

## 解法一：最简单的思路

最简单的思路是：从头扫描该数组，每碰到一个偶数，拿出这个数字，并把位于这个数字后面的所有数字往前挪动一位。挪完之后在数组的末尾有一个空位，这时把该偶数放入这个空位。由于每碰到一个偶数就需要移动O(n)个数字，因此，总的时间复杂度为$O(n^2)$。

## 解法二：基本功能解法

维护两个指针，第一个指针初始化时指向数组的第一个数字，它只向后移动；第二个指针初始化时指向数组的最后一个数字，它只向前移动。

在两个指针相遇之前，第一个指针总是位于第二个指针的前面。如果第一个指针指向的数字是偶数，并且第二个指针指向的数字是奇数，则交换这两个数字。

详细代码如下：

``` c++
void swap(int &first, int &second) {
	int tmp = first;
	first = second;
	second = tmp;
}

void ReorderArray(int *number, int length) {
	if (number == NULL || length == 0)
		return;

	int head = 0;
	int tail = length - 1;

	while (head < tail) {
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		while (head < tail && number[head] % 2 == 1) // odd
			head++;
		
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		while (head < tail && number[tail] % 2 == 0) // even
			tail--;
		
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		if (head < tail)
			swap(number[head], number[tail]);
	}
}
```

## 解法三：可扩展性

将判定条件函数化。

详细代码：

```c++

typedef bool (*FUNC)(int);

void swap(int &first, int &second) {
	int tmp = first;
	first = second;
	second = tmp;
}

bool isEven(int i) {
  	return i % 2 == 0;
}

void ReorderArray(int *number, int length, FUNC func) {
	if (number == NULL || length == 0)
		return;

	int head = 0;
	int tail = length - 1;

	while (head < tail) {
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		while (head < tail && !func(number[head])) // odd
			head++;
		
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		while (head < tail && func(number[tail])) // even
			tail--;
		
      	// 切记一定要在内部循环中判断是否达到边界条件，否则会出现错误
		if (head < tail)
			swap(number[head], number[tail]);
	}
}

调用方式：ReorderArray(nums, len, isEven);
```

如上，我们对整个函数进行了解耦，解耦的好处是提高了代码的重用性，为功能扩展提供了便利。

# 测试用例

* 功能测试（输入数组中的奇数、偶数交替出现，输入的数组中所有偶数都出现在奇数的前面，输入数组中所有奇数都出现在偶数前面）；
* 特殊输入测试。

