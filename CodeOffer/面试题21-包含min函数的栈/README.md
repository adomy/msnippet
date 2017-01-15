[TOC]

# 题目

**内容**：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数。在该栈中，调用min、pop以及push的时间复杂度都是O(1)。

# 思路

## 坑

**第一反应**：每次压入一个新元素进栈时，将栈里的所有元素排序，让最小的元素位于栈顶，这样能在O(1)时间得到最小元素了。但这种思路不能保证最后压入栈的元素能够最先出栈，因此这个数据结构已经不是栈了。

**第二反应**：在栈里添加一个成员变量用于存放最小的元素。每次压入一个新元素进栈的时候，如果该元素比当前最小元素还要小，则更新最小元素。面试官听到这种思路后就会问：如果当前最小的元素被弹出栈了，如何得到下一个最小的元素呢？

因此，仅仅添加一个成员变量存放最小元素是不够的，也就是说当最小元素被弹出栈的时候，我们希望能够得到次小元素。因此，在压入这个最小元素之前，我们要把次小元素保存起来。

## 解法

利用辅助栈。

在主栈中压入数据时，同时将当前最小值压入辅助栈；主栈弹出数据时，同时弹出辅助栈顶部元素。

具体代码如下：

``` c++
template <typename T>
class StackWithMin {
public:
	StackWithMin() {
	}

	~StackWithMin() {
	}

	void push(const T &val) {
		m_data.push(val);

		if (m_min.size() == 0 || val < m_min.top())
			m_min.push(val);
		else
			m_min.push(m_min.top());
	}

	void pop() {
		m_data.pop();
		m_min.pop();
	}

	const T &min() {
		return m_min.top();
	}
private:
	std::stack<T> m_data;
	std::stack<T> m_min;
};
```





