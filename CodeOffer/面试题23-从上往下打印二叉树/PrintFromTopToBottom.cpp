#include <iostream>
#include <queue>

struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

void PrintFromTopToBottom(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::queue<BinaryTreeNode *> q;
	q.push(root);

	while (!q.empty()) {
		BinaryTreeNode *node = q.front();
		q.pop();

		std::cout << node->m_nValue << " ";

		if (node->m_pLeft)
			q.push(node->m_pLeft);

		if (node->m_pRight)
			q.push(node->m_pRight);
	}
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

	PrintFromTopToBottom(tree1);

	return 0;
}