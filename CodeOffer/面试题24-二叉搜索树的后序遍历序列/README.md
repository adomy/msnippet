[TOC]

# 题目

**内容**：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则返回true，否则返回false。假设输入的数组的任意两个数字都互不相同。

# 思路

在后序遍历得到的序列中，最后一个数字是树的根节点的值。数组中前面的数字可以分为两部分：**第一部分是左子树节点的值，它们都比根节点的值小；第二部分是右子树节点的值，它们都比根节点的值大**。

我们用同样的方法确定与数组每一部分对应的子树的结构。这其实是一个**递归**的过程。

详细代码如下：

``` c++
bool VerifySequenceOfBST(int sequence[], int length) {
	if (sequence == NULL || length <= 0)
		return false;

	int rooti = length - 1;
	int leftLen = 0;

	for (int i = rooti - 1; i >= 0; i--) {
		if (sequence[i] < sequence[rooti]) {
			leftLen = i + 1;
			break;
		}
	}

	for (int i = leftLen - 1; i >= 0; i--) {
		if (sequence[i] >= sequence[rooti])
			return false;
	}

	bool left = true;
	if (leftLen > 0)
		left = VerifySequenceOfBST(sequence, leftLen);

	bool right = true;
	if (length - leftLen - 1 > 0)
		right = VerifySequenceOfBST(sequence + leftLen, length - leftLen - 1);

	return (left && right);
}
```

# 测试用例

* 功能测试（输入的后序遍历的序列对应一棵二叉树，包括完全二叉树、所有节点都没有左右子树的二叉树、只有一个节点的二叉树；输入的后续遍历序列没有对应一棵二叉树）。
* 特殊输入测试。

# 扩展

**相关题目**：输入一个整数数组，判断该数组是不是某二叉搜索树的前序遍历的结果。

**提示**：这和前面的后序遍历很类似，只是在前序遍历得到的序列中，第一个数字是根节点的值。

# 举一反三

如果面试题是要求处理一棵二叉树的遍历序列，我们可以先找到二叉树的根节点，再基于根节点把整棵树的遍历序列拆分成左子树对应的子序列和右子树对应的子序列，接下来再递归地处理这两个子序列。