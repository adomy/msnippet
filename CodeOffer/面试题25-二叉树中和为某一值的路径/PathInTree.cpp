#include <iostream>
#include <vector>

struct BinaryTreeNode {
	int m_nValue;
	BinaryTreeNode *m_pLeft;
	BinaryTreeNode *m_pRight;
};

void FindPath(BinaryTreeNode *root, int target, std::vector<int> &path, std::vector<std::vector<int> > &paths) {
	if (root == NULL)
		return;

	path.push_back(root->m_nValue);

	// 到达叶子节点同时满足条件，则打印所有
	if (root->m_pLeft == NULL && root->m_pRight == NULL && root->m_nValue == target) 
		paths.push_back(path);

	// 如果不是叶节点，则遍历它的子节点
	if (root->m_pLeft)
		FindPath(root->m_pLeft, target - root->m_nValue, path, paths);

	if (root->m_pRight)
		FindPath(root->m_pRight, target - root->m_nValue, path, paths);

	// 在返回到父节点之前，在路径上删除当前节点
	path.pop_back();
}

void FindPathInTree(BinaryTreeNode *root, int target, std::vector<std::vector<int> > &paths) {
	if (root == NULL)
		return;

	std::vector<int> path;
	FindPath(root, target, path, paths);
}

int main() {
	BinaryTreeNode *root = new BinaryTreeNode;
	root->m_nValue = 10;
	root->m_pLeft = NULL;
	root->m_pRight = NULL;

	BinaryTreeNode *l1 = new BinaryTreeNode;
	l1->m_nValue = 5;
	l1->m_pLeft = NULL;
	l1->m_pRight = NULL;

	root->m_pLeft = l1;

	BinaryTreeNode *l21 = new BinaryTreeNode;
	l21->m_nValue = 4;
	l21->m_pLeft = NULL;
	l21->m_pRight = NULL;

	l1->m_pLeft = l21;

	BinaryTreeNode *l22 = new BinaryTreeNode;
	l22->m_nValue = 7;
	l22->m_pLeft = NULL;
	l22->m_pRight = NULL;

	l1->m_pRight = l22;

	BinaryTreeNode *r1 = new BinaryTreeNode;
	r1->m_nValue = 12;
	r1->m_pLeft = NULL;
	r1->m_pRight = NULL;

	root->m_pRight = r1;

	std::vector<std::vector<int> > paths;
	FindPathInTree(root, 22, paths);

	for (int i = 0; i < paths.size(); i++) {
		for (int j = 0; j < paths[i].size(); j++)
			std::cout << paths[i][j] << " ";

		std::cout << std::endl;
	}

	return 0;
}