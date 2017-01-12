[TOC]

# 题目

**内容**：输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是按照递增顺序排列的。

例如，输入链表1$(1 \to 3 \to 5 \to 7)$和链表2$(2 \to 4 \to 6 \to 8)$。输出链表3$(1 \to 2 \to 3 \to 4 \to 5 \to 6 \to 7 \to 8)$。

链表节点定义如下：

```c++
struct ListNode {
  	int m_nValue;
  	ListNode *m_pNext;
};
```

# 思路

## 解法一

非递归方法：

``` c++
ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
	if (pHead1 == NULL)
		return pHead2;

	if (pHead2 == NULL)
		return pHead1;

	ListNode *newList = NULL;

	ListNode *fn = pHead1;
	ListNode *sn = pHead2;

	if (fn->m_nValue < sn->m_nValue) {
		newList = fn;
		fn = fn->m_pNext;
	} else {
		newList = sn;
		sn = sn->m_pNext;
	}

	ListNode *prev = newList;
	while (fn && sn) {
		if (fn->m_nValue < sn->m_nValue) {
			prev->m_pNext = fn;
			prev = fn;
			fn = fn->m_pNext;
		} else {
			prev->m_pNext = sn;
			prev = sn;
			sn = sn->m_pNext;
		}
	}

	if (fn)
		prev->m_pNext = fn;

	if (sn)
		prev->m_pNext = sn;

	return newList;
}
```

## 解法二

递归方法：

```c++
ListNode* Merge2(ListNode *pHead1, ListNode *pHead2) {
	if (pHead1 == NULL)
		return pHead2;

	if (pHead2 == NULL)
		return pHead1;

	ListNode *newList = NULL;

	if (pHead1->m_nValue < pHead2->m_nValue) {
		newList = pHead1;
		newList->m_pNext = Merge2(pHead1->m_pNext, pHead2);
	} else {
		newList = pHead2;
		newList->m_pNext = Merge2(pHead1, pHead2->m_pNext);
	}

	return newList;
}
```

# 测试用例

* 功能测试（输入的两个链表有多个节点，节点的值互不相同或者存在值相等的多个节点）；
* 特殊输入测试（两个链表的一个或者两个头节点为NULL、两个链表中只有一个节点）。