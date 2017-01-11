#include <iostream>
#include <queue>

typedef struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
} BinaryTreeNode; 

BinaryTreeNode* constructBinaryTree(int *preorder, int *inorder, int length) {
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	BinaryTreeNode *left_tree = NULL;
	BinaryTreeNode *right_tree = NULL;

	int root_key = preorder[0];
	BinaryTreeNode *root = new BinaryTreeNode;
	root->m_nValue = root_key;

	int left_tree_size = 0;
	while (inorder[left_tree_size] != root_key)
		left_tree_size++;

	int right_tree_size = length - left_tree_size - 1;

	if (left_tree_size > 0 )
		left_tree = constructBinaryTree(preorder + 1, inorder, left_tree_size);

	if (right_tree_size > 0) 
		right_tree = constructBinaryTree(preorder + left_tree_size + 1, inorder + left_tree_size + 1, right_tree_size);

	root->m_pLeft = left_tree;
	root->m_pRight = right_tree;

	return root;
}

BinaryTreeNode *constructCore(int *startPreorder, int *endPreorder, int *startInorder, int *endInorder) {
	int rootValue = startPreorder[0];
	BinaryTreeNode *root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	root->m_pLeft = root->m_pRight = NULL;

	if (startPreorder == endPreorder) {
		if (startInorder == endInorder && *startPreorder == *startInorder)
			return root;
	}

	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != rootValue)
		++rootInorder;

	int leftLength = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + leftLength;

	if (leftLength > 0) {
		root->m_pLeft = constructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
	} 

	if (leftLength < endPreorder - startPreorder) {
		root->m_pRight = constructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
	}

	return root;
}


BinaryTreeNode *constructBinaryTree2(int *preorder, int *inorder, int length) {
	if (preorder == NULL || inorder == NULL || length <= 0)
		return NULL;

	return constructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);
}

void printPreorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	std::cout << root->m_nValue << " ";

	printPreorder(root->m_pLeft);

	printPreorder(root->m_pRight);
}

void printInorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	printInorder(root->m_pLeft);

	std::cout << root->m_nValue << " ";

	printInorder(root->m_pRight);
}

void printPostorder(BinaryTreeNode *root) {
	if (root == NULL)
		return;

	printPostorder(root->m_pLeft);

	printPostorder(root->m_pRight);

	std::cout << root->m_nValue << " ";
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
	
	int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};
	int length = 8;
	
	/*
	int preorder[] = {10, 6, 4, 8, 14, 12, 16};
	int inorder[] = {4, 6, 8, 10, 12, 14, 16};
	int length = 7;
	*/

	BinaryTreeNode *root = constructBinaryTree2(preorder, inorder, length);

	std::cout << "Preorder = ";
	printPreorder(root);
	std::cout << "\nInorder = ";
	printInorder(root);
	std::cout << "\nPostorder = ";
	printPostorder(root);
	std::cout << "\nBFS = ";
	printBfs(root);
	std::cout << std::endl;

	return 0;
}