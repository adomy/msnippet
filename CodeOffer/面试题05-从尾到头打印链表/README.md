[TOC]

# 题目

**内容**：输入一个链表的头节点，从尾到头反过来打印每个节点的值。

链表节点定义如下：

``` c++
struct ListNode {
 	int m_nKey;
  	ListNode *m_pNext;
};
```

**面试小提示**：在面试中如果我们打算修改输入的数据，最好先问面试官是不是允许做修改。

# 思路

通常打印是一个只读操作，我们不希望打印时修改内容。

对于从尾到头打印链表，我们首先想到的是通过栈来实现。其代码如下：

``` c++
void backPrintList2(ListNode *pHead) {
	std::stack<ListNode *> nodeStack;

	if (pHead)
		nodeStack.push(pHead);

	while (pHead->m_pNext) {
		pHead = pHead->m_pNext;
		nodeStack.push(pHead);
	}

	while (!nodeStack.empty()) {
		pHead = nodeStack.top();
		nodeStack.pop();
		std::cout << pHead->m_nKey << std::endl;
	}
}
```

通常，能通过栈实现的操作，一般可以通过递归实现。其代码如下：

``` c++
void backPrintList1(ListNode *pHead) {
	if (pHead != NULL) {
		if (pHead->m_pNext)
			backPrintList1(pHead->m_pNext);
			
		std::cout << pHead->m_nKey << std::endl;
	}
}
```

基于递归的代码看起来很简洁，但有个问题：当链表非常长的时候，就会导致函数调用的层次很深，从而有可能导致函数调用栈溢出。**显式用栈基于循环实现的代码的鲁棒性要好一些**。



# 测试用例

* 功能测试（输入的链表有多个节点，输入的链表只有一个节点）。
* 特殊输入测试。

