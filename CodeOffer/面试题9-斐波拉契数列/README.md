[TOC]

# 题目

**内容**：写一个函数，输入n，求斐波拉契（Fibonacci）数列的第n项。

$f(n) = 0, when\,n = 0$

$f(n) = 1, when \,n= 1$

$f(n) = f(n - 1) + f(n - 2), when\,n>1$

题目本身是没什么可以分析的。下面我们来看看几种解法。

# 解法

## 解法一：效率很低的解法，挑剔的面试官不会喜欢

直接贴代码：

``` c++
long long Fibonacci(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}
```

该方法存在许多冗余计算项，而且重复的节点树会随着n的增大而急剧增加，这意味着计算量会随着n的增大而急剧增大。事实上，用递归的方法计算的时间复杂度是以n的指数的方式递增的。

## 解法二：面试官期待的实用解法

避免重复计算就可以了。

两种方法：

* 用全局数组保存计算结果。

代码：

``` c++
long long f[MAXSIZE];

long long Fibonacci2(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	if (f[n] > 0)
		return f[n];

	int value = Fibonacci2(n - 1) + Fibonacci2(n - 2);
	f[n] = value;

	return value;
}
```



* 从下往上计算。

代码：

``` c++
long long Fibonacci3(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	long long first = 0;
	long long second = 1;
	long long nth = 0;

	for (int i = 2; i <= n; i++) {
		nth = first + second;

		first = second;
		second = nth;
	}

	return nth;
}
```

# 效率比较

测试执行时间。

``` c++
std::cin >> n;
	clock_t start = clock();
	std::cout << "Method 1 Result = " << Fibonacci(n) << std::endl;
	clock_t end_1 = clock();
	std::cout << "Time Consumed = " << end_1 - start << std::endl;

	std::cout << "Method 2 Result = " << Fibonacci2(n) << std::endl;
	clock_t end_2 = clock();
	std::cout << "Time Consumed = " << end_2 - end_1 << std::endl;

	std::cout << "Method 3 Result = " << Fibonacci3(n) << std::endl;
	clock_t end_3 = clock();
	std::cout << "Time Consumed = " << end_3 - end_2 << std::endl;
```

测试结果：

``` shell
zjl@zjl-jos:~/Test$ ./a.out 
25
Method 1 Result = 75025
Time Consumed = 2134
Method 2 Result = 75025
Time Consumed = 27
Method 3 Result = 75025
Time Consumed = 18

zjl@zjl-jos:~/Test$ ./a.out 
30
Method 1 Result = 832040
Time Consumed = 19742
Method 2 Result = 832040
Time Consumed = 17
Method 3 Result = 832040
Time Consumed = 12

zjl@zjl-jos:~/Test$ ./a.out 
42
Method 1 Result = 267914296
Time Consumed = 4335029
Method 2 Result = 267914296
Time Consumed = 11
Method 3 Result = 267914296
Time Consumed = 5
```

可见，解法一的效率极低。

# 扩展 

**题目二**：一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个n级的台阶总共有多少种跳法。

分析：$f(n) = f(n-1) + f(n-2)$

同斐波拉契数列。

**题目三**：我们可以用$2\times1$的小矩形横着或者竖着去覆盖更大的矩形。请问，用8个$2\times1$的小矩形无重叠得覆盖一个$2\times8$的大矩形，总共有多少种方法？

分析：小矩形可以选择横着放或者竖着放。

如果竖着放，则剩余$2\times7$矩形。如果横着放，2个$2\times1$小矩形叠着放，然后剩余$2\times6$矩形。

故有$f(n) = f(n-1) + f(n-2)$

同斐波拉契数列。