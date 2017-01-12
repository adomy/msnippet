#include <iostream>

struct ListNode {
	int m_nValue;
	ListNode *m_pNext;
};

ListNode* FindKthToTail(ListNode *pListHead, int k) {
	if (pListHead == NULL || k <= 0)
		return NULL;

	ListNode *front = pListHead;
	ListNode *back = pListHead;

	int i = 1;
	while (i < k && front->m_pNext) {
		front = front->m_pNext;
		i++;
	} // 跳出循环的两个条件：i == k 或者 front->m_pNext == NULL.

	// 由于front->m_pNext导致的
	if (i < k)
		return NULL;

	while(front->m_pNext) {
		front = front->m_pNext;
		back = back->m_pNext;
	}

	return back;
}

void PrintList(ListNode **pListHead) {
	ListNode *pNode = *pListHead;

	std::cout << "List Content = ";
	while (pNode) {
		std::cout << pNode->m_nValue << " ";
		pNode = pNode->m_pNext;
	}

	std::cout << std::endl;
}

int main() {
	ListNode *list;
	list = new ListNode;
	list->m_nValue = 1;
	list->m_pNext = NULL;

	ListNode *prev;
	ListNode *node;
	prev = list;
	for (int i = 2; i < 10; i++) {
		node = new ListNode;
		node->m_nValue = i;
		node->m_pNext = NULL;
		prev->m_pNext = node;
		prev = node;
	}

	PrintList(&list);

	ListNode *pn = FindKthToTail(list, 9);
	if (pn == NULL)
		std::cout << "NULL" << std::endl;
	else 
		std::cout << pn->m_nValue << std::endl;
}