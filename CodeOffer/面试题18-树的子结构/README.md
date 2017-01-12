[TOC]

# 题目

**内容**：输入两棵二叉树A和B，判断B是不是A的子结构。

二叉树定义如下：

``` c++
struct BinaryTreeNode {
  	int m_nValue;
  	BinaryTreeNode *m_pLeft;
  	BinaryTreeNode *m_pRight;
};
```

# 思路

要查找树A中是否存在和树B结构一样的子树，我们可以分成两步：**第一步**在树A中找到和B的根节点的值一样的节点R；**第二步**再判断树A中以R为根节点的子树是不是包含和树B一样的结构。

第一步在树A中查找与根节点的值一样的节点，这实际上是树的遍历。

```c++
bool HasSubtree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
	bool result = false;

	if (pRoot1 != NULL && pRoot2 != NULL) {
		if (pRoot1->m_nValue == pRoot2->m_nValue)
			result = DoesTree1HaveTree2(pRoot1, pRoot2);

		if (!result)
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);

		if (!result)
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
	}

	return result;
}
```

第二步是判断树A中以R为根节点的子树是不是和树B具有相同的结构。同样，可以用递归的思路来考虑。

```c++
bool DoesTree1HaveTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
	if (pRoot2 == NULL)
		return true;

	if (pRoot1 == NULL)
		return false;

	if (pRoot1->m_nValue != pRoot2->m_nValue)
		return false;

	return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}
```

注意：二叉树相关的代码有大量的指针操作，每一次使用指针的时候，我们都要问自己这个指针有没有可能是NULL，如果是NULL该怎么处理。

# 测试用例 

* 功能测试（树A和树B都是普通的二叉树，树B是或者不是树A的子结构）；
* 特殊输入测试。