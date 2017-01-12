#include <iostream>

struct ListNode {
	int m_nValue;
	ListNode *m_pNext;
};

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
	ListNode *prev;
	ListNode *node;
	ListNode *tmp;
	ListNode *list1;
	list1 = new ListNode;
	list1->m_nValue = 1;
	list1->m_pNext = NULL;

	tmp = list1;
	prev = list1;
	for (int i = 3; i < 14; i = i + 2) {
		node = new ListNode;
		node->m_nValue = i;
		node->m_pNext = NULL;
		prev->m_pNext = node;
		prev = node;
	}

	PrintList(&list1);

	ListNode *list2;
	list2 = new ListNode;
	list2->m_nValue = 0;
	list2->m_pNext = NULL;

	tmp = list2;
	prev = list2;
	for (int i = 2; i < 14; i = i + 2) {
		node = new ListNode;
		node->m_nValue = i;
		node->m_pNext = NULL;
		prev->m_pNext = node;
		prev = node;
	}

	PrintList(&list2);

	ListNode *newlist = Merge2(list1, list2);
	PrintList(&newlist);

	return 0;
}