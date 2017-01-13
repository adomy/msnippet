[TOC]

# 题目

**内容**：请完成一个函数，输入一个二叉树，该函数输出它的镜像。

二叉树节点的定义如下：

```c++
struct BinaryTreeNode {
  	int m_nValue;
  	BinaryTreeNode *m_pLeft;
  	BinaryTreeNode *m_pRight;
};
```

# 思路

求解一棵树的镜像的过程：我们先前序遍历这棵树的每个节点，如果遍历到的节点有子节点，就交换它的两个子节点。当交换完所有非叶子节点的左右子节点之后，就得到了树的镜像。

详细代码：

``` c++
void MirrorRecursively(BinaryTreeNode *pNode) {
	if (pNode == NULL)
		return;

	if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
		return;

	BinaryTreeNode *tmp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = tmp;

	MirrorRecursively(pNode->m_pLeft);
	MirrorRecursively(pNode->m_pRight);
}
```

# 测试用例

* 功能测试（普通的二叉树，二叉树的所有节点都没有左子树或者右子树，只有一个节点的二叉树）；
* 特殊输入测试。