[TOC]

# 题目

**内容**：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。

例如，序列1/2/3/4/5是某栈的压栈顺序，序列4/5/3/2/1是该压栈序列对应的一个弹出序列，但4/3/5/1/2就不可能是该压栈序列的弹出序列。

# 思路

解决这个问题很直观的想法就是**建立一个辅助栈**，把输入的第一个序列中的数字依次压入该辅助栈，并按照第二个序列的顺序依次从该栈中弹出数字。

总结入栈、出栈的过程，我们可以找出判断一个序列是不是栈的弹出序列的规律：如果下一个弹出的数字刚好是栈顶数字，那么直接弹出。如果下一个弹出的数字不在栈顶，我们把压栈序列中还没有入栈的数字压入辅助栈，直到把下一个需要弹出的数字压入栈顶为止。如果所有的数字都压入栈了仍然没有找到下一个弹出的数字，那么该序列就不可能是一个弹出序列。

详细代码如下：

``` c++
bool IsPopOrder(const int *pPush, const int *pPop, int nLength) {
	int pushi = 0;
	int popj = 0;
	std::stack<int> helpStack;
	while (popj < nLength) {
		if (helpStack.size() != 0 && helpStack.top() == pPop[popj]) {
			helpStack.pop();
			popj++;
			continue;
		}

		while (pushi < nLength && pPush[pushi] != pPop[popj]) {
			helpStack.push(pPush[pushi]);
			pushi++;
		}

		if (pPush[pushi] != pPop[popj])
			return false;

		pushi++;
		popj++;
	}

	return true;
}
```

