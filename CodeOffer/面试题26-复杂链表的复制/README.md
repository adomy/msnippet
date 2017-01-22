[TOC]



# 题目

**内容**：请实现函数ComplexListNode *Clone(ComplexListNode *pHead)复制一个复杂链表。在复杂链表中，每个节点除了有一个m_pNext指针指向下一个节点外，还有一个m_pSibling指向链表中的任意节点或者NULL。

节点定义：

``` c++
struct ComplextListNode {
  	int m_nValue;
  	ComplexListNode *m_pNext;
  	ComplexListNode *m_pSibling;
};
```



# 思路

## 原始思路

听到这个问题后，很多应聘者的第一反应是**把复制过程分成两步，第一步是复制原始链表的每一个节点，并用m_pNext链接起来；第二步是设置每个节点的m_pSibling指针**。

对于一个含有n个节点的链表，由于定位每个节点的m_pSibling都需要从链表头节点开始经过$O(n)$步才能找到，因此这种方法的总时间复杂度是$O(n^2)$。

## 优化思路一

由于上述方法的时间主要花费在定位节点的m_pSibling上面，我们试着在这方面去做优化。

我们还是分为两步：

* 第一步：复制原始链表上的每个节点N创建N'，然后把这些创建出来的节点用m_pNext链接起来。同时，我们把<N, N'>的配对信息放到一个哈希表中。
* 第二步：设置复制链表上每个节点的m_pSibling。如果在原始链表中节点N的m_pSibling指向节点S，那么，在复制链表中，对应的N'应该指向S'。由于有了哈希表，我们可以用O(1)的时间根据S找到S'。

第二种方法相当于用空间换时间。对于有n个节点的链表，我们需要大小为$O(n)$的哈希表，也就是说我们用$O(n)$的空间消耗，把时间复杂度的$O(n^2)$降低到$O(n)$。

详细代码：

``` c++
ComplexListNode *Clone1(ComplexListNode *pHead) {
	if (pHead == NULL)
		return NULL;

	std::map<ComplexListNode *, ComplexListNode *> oldNewNodeMap;
	
	ComplexListNode *newHead = new ComplexListNode;
	newHead->m_nValue = pHead->m_nValue;
	newHead->m_pNext = NULL;
	newHead->m_pSibling = pHead->m_pSibling;
	oldNewNodeMap[pHead] = newHead;

	ComplexListNode *prevNode = newHead;
	ComplexListNode *oldNextNode = pHead->m_pNext;
	while (oldNextNode) {
		ComplexListNode *newNode = new ComplexListNode;
		newNode->m_nValue = oldNextNode->m_nValue;
		newNode->m_pNext = NULL;
		newNode->m_pSibling = oldNextNode->m_pSibling;

		if (prevNode)
			prevNode->m_pNext = newNode;

		oldNewNodeMap[oldNextNode] = newNode;

		oldNextNode = oldNextNode->m_pNext;
	}

	ComplexListNode *newNextNode = newHead;
	while (newNextNode) {
		ComplexListNode *factSiblingNode = oldNewNodeMap[newNextNode->m_pSibling];
		newNextNode->m_pSibling = factSiblingNode;
		newNextNode = newNextNode->m_pNext;
	}

	return newHead;
}
```



## 优化思路二

我们再换一种思路，在不用辅助空间的情况下实现$O(n)$的时间效率。

* 第一步：根据原始链表的每个节点N创建对应的N'。这一次，我们将N'链接在N的后面。
* 第二步：设置复制出来的节点的m_pSibling。假设原始链表上的N'的m_pSibling指向节点S，那么其对应复制出来的N'是N的m_pNext指向的节点，同样，S'也是S的m_pNext指向的节点。
* 第三步，将该长链表拆分成两个链表：把奇数位置的节点用m_pNext链接起来就是原始链表；把偶数位置连接起来就是复制出来的链表。

详细代码：

``` c++
ComplexListNode *Clone2(ComplexListNode *pHead) {
	if (pHead == NULL)
		return NULL;

	ComplexListNode *pNode = pHead;
	while (pNode) {
		ComplexListNode *pCloned = new ComplexListNode;
		pCloned->m_nValue = pNode->m_nValue;
		pCloned->m_pNext = pNode->m_pNext;
		pCloned->m_pSibling = NULL;

		pNode->m_pNext = pCloned;
		pNode = pCloned->m_pNext;
	}

	ComplexListNode *pNode2 = pHead;
	while (pNode2) {
		ComplexListNode *pCloned2 = pNode2->m_pNext;

		if (pNode2->m_pSibling)
			pCloned2->m_pSibling = pNode2->m_pSibling->m_pNext;

		pNode2 = pCloned2->m_pNext;
	}

	ComplexListNode *pNode3 = pHead;
	ComplexListNode *pNewHead = pNode3->m_pNext;
	ComplexListNode *pNewNode = pNewHead;
	pNode3->m_pNext = pNewHead->m_pNext;
	pNode3 = pNode3->m_pNext;

	while (pNode3) {
		pNewNode->m_pNext = pNode3->m_pNext;
		pNewNode = pNewNode->m_pNext;
		pNode3->m_pNext = pNewNode->m_pNext;
		pNode3 = pNode3->m_pNext;
	}
	
	return pNewHead;
}
```

# 测试用例

* 功能测试（包括节点中的m_pSibling指向节点自身，两个节点的m_pSibling形成环状结构，链表中只有一个节点）。
* 特殊输入测试。