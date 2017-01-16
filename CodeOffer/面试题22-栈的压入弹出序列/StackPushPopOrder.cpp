#include <iostream>
#include <stack>

bool IsPopOrder(const int *pPush, const int *pPop, int nLength) {
	int pushi = 0;
	int popj = 0;
	std::stack<int> helpStack;
	while (popj < nLength) {
		if (helpStack.size() != 0 && helpStack.top() == pPop[popj]) {
			helpStack.pop();
			popj++;
			continue;
		}

		while (pushi < nLength && pPush[pushi] != pPop[popj]) {
			helpStack.push(pPush[pushi]);
			pushi++;
		}

		if (pPush[pushi] != pPop[popj])
			return false;

		pushi++;
		popj++;
	}

	return true;
}

int main() {
	int len = 5;
	int in[] = {1, 2, 3, 4, 5};
	int out[] = {4, 5, 3, 2, 1};
	int out2[] = {4, 3, 2, 1, 5};

	std::cout << IsPopOrder(in, out, len) << std::endl;
	std::cout << IsPopOrder(in, out2, len) << std::endl;

	return 0;
}