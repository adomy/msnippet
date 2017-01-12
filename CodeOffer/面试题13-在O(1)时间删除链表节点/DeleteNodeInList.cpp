#include <iostream>

struct ListNode {
	int m_nValue;
	ListNode *m_pNext;
};

void DeleteNode1(ListNode **pListHead, ListNode *pToBeDeleted) {
	if (*pListHead == NULL || pToBeDeleted == NULL)
		return;

	if (*pListHead == pToBeDeleted) {
		*pListHead = pToBeDeleted->m_pNext;
		delete pToBeDeleted;
		*pListHead == NULL;
		return;
	}

	ListNode *pNode = *pListHead;
	while (pNode->m_pNext != pToBeDeleted)
		pNode = pNode->m_pNext;

	pNode->m_pNext = pNode->m_pNext->m_pNext;
	delete pToBeDeleted;
}

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
	ListNode *tmp = list;
	prev = list;
	for (int i = 2; i < 10; i++) {
		node = new ListNode;
		node->m_nValue = i;
		node->m_pNext = NULL;
		prev->m_pNext = node;
		prev = node;

		if (i == 9)
			tmp = node;
	}

	PrintList(&list);
	DeleteNode2(&list, tmp);
	PrintList(&list);
}