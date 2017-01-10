#include <iostream>
#include <stack>

typedef struct ListNode {
	int m_nKey;
	struct ListNode *m_pNext;
} ListNode;

void backPrintList1(ListNode *pHead) {
	if (pHead != NULL) {
		if (pHead->m_pNext)
			backPrintList1(pHead->m_pNext);
			
		std::cout << pHead->m_nKey << std::endl;
	}
}

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

int main() {
	ListNode *pHead = new ListNode;
	pHead->m_nKey = 12;

	ListNode *prev = pHead;
	int i = 0;
	for (i = 0; i < 10; i++) {
		ListNode *pNode = new ListNode;
		pNode->m_nKey = i * i;
		pNode->m_pNext = NULL;

		prev->m_pNext = pNode;
		prev = pNode;
	}

	backPrintList2(pHead);

	return 0;
}