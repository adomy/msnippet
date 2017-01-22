#include <iostream>
#include <map>

struct ComplexListNode {
	int m_nValue;
	ComplexListNode *m_pNext;
	ComplexListNode *m_pSibling;
};

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

int main() {
	//...
}