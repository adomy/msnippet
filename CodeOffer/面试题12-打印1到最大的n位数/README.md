[TOC]

# 题目

**内容**：输入数字n，按顺序打印出从1到最大的n位十进制数。比如，输入3，则打印出1/2/3一直到最大的3位数999。

# 思路

## 坑

最大的数不能直接用整数或者长整数表示。

错误代码：

``` c++
void Print1ToMaxOfNDigits_1(int n) {
	int number = 1;
	int i = 0;
	while (i < n) {
		number *= 10;
		i++;
	}

	for (i = 1; i < number; i++) {
		std::cout << i << "\t";
	}

	std::cout << std::endl;
}
```

## 解法一：在字符串上模拟数字加法的解法

表达一个大数最常用也是最容易的方法是用字符串或者数组表示大数。

我们需要一个长度为n+1的字符串。当实际数字不够n位的时候，在字符串的前半部分补0。

首先，我们把字符串的每一个数字都初始化为'0'，然后每一次为字符串表示的数字加1，再打印出来。

因此，我们只需要做两件事：一是在字符串表达的数字上模拟加法；二是把字符串表达的数字打印出来。

```c++
void Print1ToMaxOfNDigits_2(int n) {
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	std::memset(number, '0', n);
	number[n] = '\0';

	while (!IncrementNumber(number)) 
		PrintNumber(number);

	std::cout << std::endl;
	delete []number;
}
```

然后就是如何实现字符串表达的数字模拟加法，代码如下：

``` c++
bool IncrementNumber(char *number) {
	int length = std::strlen(number);

	int tmp = 0;
	int carry = 1; // 每次加一，通过Carry携带
	for (int i = length - 1; i >= 0; i--) {
		tmp = number[i] - '0' + carry;

		if (tmp < 10) {
			carry = 0;
			number[i] = tmp + '0';
			break;
		} else {
			carry = 1;
			number[i] = tmp % 10 + '0';
		}
 	}

	if (carry == 0)
		return false;

	return true;
}
```

再则就是打印出字符串（不含前面的'0'），代码如下：

```c++
void PrintNumber(char *number) {
	if (number == NULL)
		return;

	char *p = number;
	while (*p == '0') 
		p++;

	std::cout << p << "\t";
}
```

## 解法二：把问题转换为数字排列的解法，递归让代码更简洁

换一种思路，如果我们在数字前面补0的话，就会发现n位所有十进制数其实就是n个从0到9的全排列。

也就是说，我们把数字的每一位都从0到9排列一遍，就得到了所有的十进制数。只是在我们打印的时候，数字排在前面的0不打印出来。

详细代码如下：

```c++
void Print1ToMaxOfNDigitsRecursively(char *number, int length, int index) {
	if (length - 1 == index) {
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; i++) {
		number[index + 1] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}

void Print1ToMaxOfNDigits_3(int n) {
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	number[n] = '\0';

	for (int i = 0; i < 10; i++) {
		number[0] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}

	delete []number;
}
```

# 测试用例

* 功能测试（输入1/2/3）
* 特殊输入测试（输入-1/0）

# 扩展

**题目**：定义一个函数，在该函数中可以实现任意两个整数的加法。

**思路**：由于没有限定两个数的大小范围，我们也要把它当做大数问题来处理。注意：如果输入的数字中有负数，我们应该怎么去处理？？？

# 面试小提示

**字符串是一个简单、有效的表示大数的方法。**