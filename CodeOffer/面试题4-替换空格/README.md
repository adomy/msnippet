[TOC]

# 题目

**内容**：请实现一个函数，把字符串中的每个空格替换成"%20"。例如，输入"We are happy"，则输出"We%20are%20happy"。

**应用背景**：在网络编程中，如果URL参数中含有特殊字符，如空格、'#'等，可能导致服务器无法获得正确的参数值。我们需要将这些特殊符号转换成服务器可以识别的字符。**转换的规则是在'%'后跟上ASCII码的两位十六进制的表示**。



# 思路

## 解法一：O(n^2)

最直观的做法就是**从头到尾扫描字符串，每一次碰到空格字符的时候做替换**。

具体代码如下：

``` c++
// length为字符数组string的总容量
void ReplaceBlank(char string[], int length) {
	int i;
	int j;
	int ns;
	for (i = 0; string[i] != '\0'; i++) {
		if (string[i] != ' ') 
			continue;

		ns = i;
		while (string[ns] != '\0') 
			ns++;

		ns += 3;

		if (ns > length) {
			std::cout << "overflow" << std::endl;
			return;
		}

		for (j = ns; j >= i + 2; j--)
			string[j] = string[j - 2];

		string[i] = '%';
		string[i + 1] = '2';
		string[i + 2] = '0';
	}
}
```

如上面的代码所示，由于是把1个字符替换成3个字符，我们必须要把空格后面所有的字符都后移2个字节，否则就有两个字符被覆盖了。

**性能分析**：假设字符串的长度是n。对于每个空格字符，需要移动后面O(n)个字符，因此对含有O(n)个空格字符的字符串而言总的时间效率是O(n^2)。

在前面的分析中，我们发现数组中很多字符都移动了很多次，能不能减少移动次数呢？答案是肯定的。

我们换一种思路，把从前向后替换成从后向前替换。

## 解法二：O(n)



我们可以先遍历一次字符串，这样就能统计出字符串中空格的总数，并可以由此计算出替换之后的字符串的总长度。

然后，我们从字符串的后面开始复制和替换。准备两个指针P1和P2，分别指向原始字符串的末尾和替换之后的字符串的末尾。接着向前移动指针P1，逐个把它指向的字符复制到P2指向的位置，直到碰到第一个空格为止。处理空格时，P1向前移动1格，在P2之前插入字符串'%20'。

详细代码为：

``` c++
void ReplaceBlank(char string[], int length) {
	int original_length = 0;
	int blank_number = 0;

	int i = 0;
	while (string[i] != '\0') {
		original_length++;

		if (string[i] == ' ')
			blank_number++;

		i++;
	}

	int new_length = original_length + 2 * blank_number;

	if (new_length > length) {
		std::cout << "overflow" << std::endl;
		return;
	}

	int k = original_length;
	int l = new_length;
	while (k >= 0 && l > k) {
		if (string[k] != ' ') {
			string[l] = string[k];
			k--;
			l--;
			continue;
		} 

		string[l--] = '0';
		string[l--] = '2';
		string[l--] = '%';

		k--;
	}
}
```

对于该解法，所有的字符都只复制和移动一次，因此算法效率为O(n)。

