[TOC]

# 题目

**内容**：从上往下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

二叉树的节点定义如下：

``` c++
struct BinaryTreeNode {
  	int m_nValue;
  	BinaryTreeNode *m_pLeft;
  	BinaryTreeNode *m_pRight;
};
```

# 思路

很简单，使用BFS的方法。

``` c++
void PrintFromTopToBottom(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::queue<BinaryTreeNode *> q;
	q.push(root);

	while (!q.empty()) {
		BinaryTreeNode *node = q.front();
		q.pop();

		std::cout << node->m_nValue << " ";

		if (node->m_pLeft)
			q.push(node->m_pLeft);

		if (node->m_pRight)
			q.push(node->m_pRight);
	}
}
```

