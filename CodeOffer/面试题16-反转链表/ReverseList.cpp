#include <iostream>

struct ListNode {
	int m_nKey;
	ListNode *m_pNext;
};

ListNode *ReverseList(ListNode *pHead) {
	if (pHead == NULL)
		return NULL;

	ListNode *prevNode = NULL;
	ListNode *nowNode = pHead;
	ListNode *nextNode = pHead;
	
	while (nextNode) {
		nowNode = nextNode;
		nextNode = nowNode->m_pNext;

		nowNode->m_pNext = prevNode;
		prevNode = nowNode;
	}

	return nowNode;
}

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

void PrintList(ListNode **pListHead) {
	ListNode *pNode = *pListHead;

	std::cout << "List Content = ";
	while (pNode) {
		std::cout << pNode->m_nKey << " ";
		pNode = pNode->m_pNext;
	}

	std::cout << std::endl;
}

int main() {
	ListNode *list;
	list = new ListNode;
	list->m_nKey = 1;
	list->m_pNext = NULL;

	ListNode *prev;
	ListNode *node;
	prev = list;
	for (int i = 2; i < 10; i++) {
		node = new ListNode;
		node->m_nKey = i;
		node->m_pNext = NULL;
		prev->m_pNext = node;
		prev = node;
	}

	PrintList(&list);

	//ListNode *newList = ReverseList(list);
	ListNode *newList = ReverseList2(list, NULL);
	PrintList(&newList);

	return 0;
}