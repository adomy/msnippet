[TOC]

# 题目

**内容**：实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。

# 解法

## 解法一：自以为题目简单的解法

由于不需要考虑大数问题，这道题看起来很简单，可能不少应聘者看到题目30秒后就能写出如下代码：

``` c++
double Power(double base, int exponent) {
	double result = 1.0;
	for (int i = 1; i <= exponent; i++)
		result *= base;

	return result;
}
```

问题在于如何处理负指数和指数为0的情况。

## 解法二：全面又高效的解法

在考虑所有情况的前提下，通过以下公式优化：

$a^n=a^\frac{n-1}{2} \times a^\frac{n-1}{2} \times a, when \, n为奇数$

$a^n=a^\frac{n}{2} \times a^\frac{n}{2}, when \, n为偶数$

该公式提醒我们可以用递归的方式来优化。

故详细代码为：

```c++
double Power2(double base, int exponent) {
	if ((base - 0.0 > -0.0000001) && (base - 0.0 < 0.0000001))
		return 0;
	
  	// 若底数为0，指数为负数，这是非法的
  	/*
  	 相关处理......
  	 */
  
	int flag = 0;
	if (exponent < 0) {
		flag = 1;
		exponent = -exponent;
	}

	double result = PowerWithUnsignedExponent(base, exponent);

	return (flag == 1) ? (1.0 / result) : result; 
}

double PowerWithUnsignedExponent(double base, unsigned int exponent) {
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double tmp = PowerWithUnsignedExponent(base, exponent >> 1); //右移细节
	return tmp * tmp * ((exponent & 0x1 == 1) ? base : 1); //位与细节
}
```

# 测试用例

* 把底数和指数分别设为正数、负数和零。



