[TOC]

# 题目

**内容**：给定单向链表的头节点和一个节点指针，定义一个函数在O(1)时间删除该节点。

链表节点与函数定义如下：

```c++
struct ListNode {
  	int m_nValue;
  	struct ListNode *m_pNext;
};

void DeleteNode(ListNode **pListHead, ListNode *pToBeDeleted);
```

# 思路

## 解法一：O(n)时间复杂度

最常规的做法：从链表的头节点开始，顺序遍历查找要删除的节点，并在链表中删除该节点。

详细代码如下：

```c++
void DeleteNode1(ListNode **pListHead, ListNode *pToBeDeleted) {
	if (*pListHead == NULL || pToBeDeleted == NULL)
		return;

	if (*pListHead == pToBeDeleted) {
		*pListHead = pToBeDeleted->m_pNext;
		delete pToBeDeleted;
		return;
	}

	ListNode *pNode = *pListHead;
	while (pNode->m_pNext != pToBeDeleted)
		pNode = pNode->m_pNext;

	pNode->m_pNext = pNode->m_pNext->m_pNext;
	delete pToBeDeleted;
}
```

## 解法二：O(1)时间复杂度

我们可以很方便地得到要删除的节点的下一个节点。我们可以把下一个节点的内容复制到需要删除的节点上覆盖原有的内容，再把下一个节点删除。这相当于把当前需要删除的节点删除了。

详细代码如下：

```c++
void DeleteNode2(ListNode **pListHead, ListNode *pToBeDeleted) {
	if (*pListHead == NULL || pToBeDeleted == NULL) 
		return;

	if (*pListHead == pToBeDeleted) {
		*pListHead = pToBeDeleted->m_pNext;
		delete pToBeDeleted;
      	*pListHead = NULL;
		return;
	}

	if (pToBeDeleted->m_pNext != NULL) {
		ListNode *delNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = delNext->m_nValue;
		pToBeDeleted->m_pNext = delNext->m_pNext;
		delete delNext;
		return;
	}

	if (pToBeDeleted->m_pNext == NULL) {
		ListNode *pNode = *pListHead;
		while (pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;

		pNode->m_pNext = NULL;
		delete pToBeDeleted;
		return;
	}
}
```

注意在上面的代码中，如果要删除的元素为尾部元素，则直接采用顺序遍历查找删除法进行元素删除。

时间复杂度计算：

对于n-1个非尾节点，其删除时间复杂度为O(1)；对于尾节点，其删除时间复杂度为O(n)。

故总时间复杂度为：$\frac{(n-1) \times O(1)+1 \times O(n)}{n}=O(1)$

# 测试用例

* 功能测试（从有多个节点的链表中间删除一个节点，从有多个节点的链表中删除头节点，从有多个节点的链表中删除尾节点，从只有一个节点的链表中删除唯一的节点）。
* 特殊输入测试。

