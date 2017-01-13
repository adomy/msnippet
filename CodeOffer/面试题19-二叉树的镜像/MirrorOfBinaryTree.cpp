#include <iostream>
#include <queue>

struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

void MirrorRecursively(BinaryTreeNode *pNode) {
	if (pNode == NULL)
		return;

	if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
		return;

	BinaryTreeNode *tmp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = tmp;

	MirrorRecursively(pNode->m_pLeft);
	MirrorRecursively(pNode->m_pRight);
}

void printBfs(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::queue<BinaryTreeNode *> node_queue;
	node_queue.push(root);

	while (!node_queue.empty()) {
		BinaryTreeNode *node = node_queue.front();
		node_queue.pop();
		std::cout << node->m_nValue << " ";
		if (node->m_pLeft)
			node_queue.push(node->m_pLeft);
		if (node->m_pRight)
			node_queue.push(node->m_pRight);
	}

	std::cout << std::endl;
}

int main() {
	BinaryTreeNode *tree1;

	// 构造第一棵树
	BinaryTreeNode *root1 = new BinaryTreeNode;
	root1->m_nValue = 8;
	root1->m_pRight = NULL;
	root1->m_pLeft = NULL;

	BinaryTreeNode *l21 = new BinaryTreeNode;
	l21->m_nValue = 8;
	l21->m_pLeft = NULL;
	l21->m_pRight = NULL;

	root1->m_pLeft = l21;

	BinaryTreeNode *r21 = new BinaryTreeNode;
	r21->m_nValue = 7;
	r21->m_pLeft = NULL;
	r21->m_pRight = NULL;

	root1->m_pRight = r21;

	BinaryTreeNode *l31 = new BinaryTreeNode;
	l31->m_nValue = 9;
	l31->m_pLeft = NULL;
	l31->m_pRight = NULL;

	l21->m_pLeft = l31;

	BinaryTreeNode *l32 = new BinaryTreeNode;
	l32->m_nValue = 2;
	l32->m_pLeft = NULL;
	l32->m_pRight = NULL;

	l21->m_pRight = l32;

	BinaryTreeNode *l41 = new BinaryTreeNode;
	l41->m_nValue = 4;
	l41->m_pLeft = NULL;
	l41->m_pRight = NULL;

	tree1 = root1;

	printBfs(tree1);

	MirrorRecursively(tree1);

	printBfs(tree1);

	return 0;
}