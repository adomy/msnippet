#include <iostream>

struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};


bool DoesTree1HaveTree2(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
	if (pRoot2 == NULL)
		return true;

	if (pRoot1 == NULL)
		return false;

	if (pRoot1->m_nValue != pRoot2->m_nValue)
		return false;

	return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) && DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool HasSubtree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2) {
	bool result = false;

	if (pRoot1 != NULL && pRoot2 != NULL) {
		if (pRoot1->m_nValue == pRoot2->m_nValue)
			result = DoesTree1HaveTree2(pRoot1, pRoot2);

		if (!result)
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);

		if (!result)
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
	}

	return result;
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

	BinaryTreeNode *tree2;

	// 构造第二棵树
	BinaryTreeNode *root2 = new BinaryTreeNode;
	root2->m_nValue = 8;
	root2->m_pLeft = NULL;
	root2->m_pRight = NULL;

	BinaryTreeNode *rl1 = new BinaryTreeNode;
	rl1->m_nValue = 9;
	rl1->m_pLeft = NULL;
	rl1->m_pRight = NULL;

	root2->m_pLeft = rl1;

	BinaryTreeNode *rr1 = new BinaryTreeNode;
	rr1->m_nValue = 2;
	rr1->m_pLeft = NULL;
	rr1->m_pRight = NULL;

	root2->m_pRight = rr1;

	tree2 = root2;

	std::cout << HasSubtree(tree1, tree2) << std::endl;

	return 0;
}