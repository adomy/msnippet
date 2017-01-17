[TOC]

# 题目

**内容**：输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。

二叉树节点的定义如下：

``` c++
struct BinaryTreeNode {
  	int m_nValue;
  	BinaryTreeNode *m_pLeft;
  	BinaryTreeNode *m_pRight;
};
```

# 思路

当用前序遍历的方式访问到某一节点时，我们把该节点添加到路径上，并累加该节点的值。如果该节点为叶节点且路径中所有节点值的和刚好等于输入的整数，则当前的路径符合要求，我们把它打印出来。如果当前节点不是叶节点，则继续访问它的子节点。当前节点访问结束后，递归函数将自动回到它的父节点。因此，我们在函数退出之前要在路径上删除当前节点并减去当前节点的值，以确保返回父节点时路径刚好是从根节点到父节点的路径。

详细代码如下：

``` c++
void FindPath(BinaryTreeNode *root, int target, std::vector<int> &path, std::vector<std::vector<int> > &paths) {
	if (root == NULL)
		return;

	path.push_back(root->m_nValue);

	// 到达叶子节点同时满足条件，则打印所有
	if (root->m_pLeft == NULL && root->m_pRight == NULL && root->m_nValue == target) 
		paths.push_back(path);

	// 如果不是叶节点，则遍历它的子节点
	if (root->m_pLeft)
		FindPath(root->m_pLeft, target - root->m_nValue, path, paths);

	if (root->m_pRight)
		FindPath(root->m_pRight, target - root->m_nValue, path, paths);

	// 在返回到父节点之前，在路径上删除当前节点
	path.pop_back();
}

void FindPathInTree(BinaryTreeNode *root, int target, std::vector<std::vector<int> > &paths) {
	if (root == NULL)
		return;

	std::vector<int> path;
	FindPath(root, target, path, paths);
}

```



# 测试用例

* 功能测试（二叉树有一条、多条符合条件的路径，二叉树中没有符合条件的路径）；
* 特殊输入测试。



