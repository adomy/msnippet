[TOC]

# 题目

**内容**：定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

链表节点定义如下：

``` c++
struct ListNode {
  	int m_nKey;
  	ListNode *m_pNext;
};
```

# 思路

动手之前先仔细分析和设计。

直接上代码：

``` c++
ListNode *ReverseList(ListNode *pHead) {
	if (pHead == NULL)
		return NULL;

	ListNode *prevNode = NULL;
	ListNode *nowNode = NULL;
	ListNode *nextNode = pHead;
	
	while (nextNode) {
		nowNode = nextNode;
		nextNode = nowNode->m_pNext;

		nowNode->m_pNext = prevNode;
		prevNode = nowNode;
	}

	return nowNode;
}
```

三种问题：

* 输入的链表头指针为NULL或整个链表只有一个节点时，程序立即崩溃。
* 反转后的链表出现断裂。
* 返回的反转之后的头节点不是原始链表的尾节点。

**应聘者如何才能及时发现并纠正代码中的问题，以确保不犯错误呢？一个很好的办法就是提前想好测试用例**。

# 测试用例

* 功能测试（输入的链表含有多个节点，链表中只有一个节点）；
* 特殊输入测试。

# 扩展

**题目**：使用递归实现反转链表的功能。

详细代码：

``` c++
ListNode *ReverseList2(ListNode *pHead, ListNode *pPrev) {
	if (pHead->m_pNext == NULL) {
		pHead->m_pNext = pPrev;
		pPrev->m_pNext = NULL;
		return pHead;
	}

	ListNode *tmp = ReverseList2(pHead->m_pNext, pHead);
	pHead->m_pNext = pPrev;
	return tmp;
}
```

认真理解该段代码！！！