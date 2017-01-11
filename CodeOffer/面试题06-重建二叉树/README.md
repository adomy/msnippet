[TOC]

# 引言

二叉树的遍历方式：

* 前序遍历：先访问根节点，再访问左子节点，最后访问右子节点。
* 中序遍历：先访问左子节点，再访问根节点，最后访问右子节点。
* 后序遍历：先访问左子节点，再访问右子节点，最后访问根节点。
* 宽度优先遍历：先访问树的第一层节点，再访问树的第二层节点......一直访问到最下面一层节点。

# 题目

**内容**：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假如输入的前序遍历和中序遍历的结果中都不含重复的数字。

例如，输入前序遍历序列{1, 2, 4, 7, 3, 5, 6, 8}和中序遍历序列{4, 7, 2, 1, 5, 3, 8, 6}，则重建出如下所示的树，并输出该树的根节点。

​                   1

​       2                    3 

   4                  5            6

​       7                           8

二叉树节点的定义如下：

``` c++
struct BinaryTreeNode {
	int m_nValue;
  	BinaryTreeNode *m_pLeft;
  	BinaryTreeNode *m_pRight;
};
```

在具体解决问题之前，我们首先回顾一下如何实现前面我们所提及的四种遍历方式：

## 前序遍历

核心代码：

``` c++
void printPreorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::cout << root->m_nValue << " ";

	printPreorder(root->m_pLeft);

	printPreorder(root->m_pRight);
}
```

## 中序遍历

核心代码：

``` c++
void printInorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	printInorder(root->m_pLeft);

	std::cout << root->m_nValue << " ";

	printInorder(root->m_pRight);
}
```

## 后序遍历

核心代码：

``` c++
void printPostorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	printPostorder(root->m_pLeft);

	printPostorder(root->m_pRight);

	std::cout << root->m_nValue << " ";
}
```

## 宽度优先遍历

核心代码：

``` c++
void printBfs(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::queue<BinaryTreeNode *> node_queue;
	node_queue.push(root);

	while (!node_queue.empty()) {
		BinaryTreeNode *node = node_queue.front();
		node_queue.pop();
      
		std::cout << node->m_nValue << " ";
      
		if (node->m_pLeft)
			node_queue.push(node->m_pLeft);
		if (node->m_pRight)
			node_queue.push(node->m_pRight);
	}

	std::cout << std::endl;
}

```

# 思路

**发现**：

* 在二叉树的前序遍历序列中，第一个数字总是树的根节点的值。
* 中序遍历序列中，根节点的值在序列的中间，左子树的节点的值位于根节点的值的左边，而右子树的节点的值位于根节点的值的右边。因此，我们需要扫描中序遍历序列，才能找到根节点的值。

**核心**：

核心就在于找到该树对应的左子树和右子树的前序遍历序列和中序遍历序列。同样地，我们可以用同样的方法去分别构建左右子树。也就是说，接下来的事情可以用递归的方法去完成。

详细代码如下：

```c++
BinaryTreeNode* constructBinaryTree(int *preorder, int *inorder, int length) {
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	BinaryTreeNode *left_tree = NULL;
	BinaryTreeNode *right_tree = NULL;

	int root_key = preorder[0];
	BinaryTreeNode *root = new BinaryTreeNode;
	root->m_nValue = root_key;

	int left_tree_size = 0;
	while (inorder[left_tree_size] != root_key)
		left_tree_size++;

	int right_tree_size = length - left_tree_size - 1;

	if (left_tree_size > 0 )
		left_tree = constructBinaryTree(preorder + 1, inorder, left_tree_size);

	if (right_tree_size > 0) 
		right_tree = constructBinaryTree(preorder + left_tree_size + 1, inorder + left_tree_size + 1, right_tree_size);

	root->m_pLeft = left_tree;
	root->m_pRight = right_tree;

	return root;
}
```

在源码文件中，我们也将《剑指offer》的书中代码贴出来了：

``` c++
BinaryTreeNode *constructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder) {
	int rootValue = startPreorder[0];
	BinaryTreeNode *root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;

	if (startPreorder == endPreorder) {
		if (startInorder == endInorder && *startPreorder == *startInorder)
			return root;
	}

	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0) {
		root->m_pLeft = constructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	} 

	if (leftLength < endPreorder - startPreorder) {
		root->m_pRight = constructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;
}


BinaryTreeNode *constructBinaryTree2(int *preorder, int *inorder, int length) {
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	return constructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}
```

# 测试用例

* 普通二叉树（完全二叉树、不完全二叉树）
* 特殊二叉树（所有节点都没有右子节点的二叉树，所有节点都没有左子节点的二叉树，只有一个节点的二叉树）
* 特殊输入测试