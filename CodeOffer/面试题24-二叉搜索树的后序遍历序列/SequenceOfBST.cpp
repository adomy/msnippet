#include <iostream>

bool VerifySequenceOfBST(int sequence[], int length) {
	if (sequence == NULL || length <= 0)
		return false;

	int rooti = length - 1;
	int leftLen = 0;

	for (int i = rooti - 1; i >= 0; i--) {
		if (sequence[i] < sequence[rooti]) {
			leftLen = i + 1;
			break;
		}
	}

	for (int i = leftLen - 1; i >= 0; i--) {
		if (sequence[i] >= sequence[rooti])
			return false;
	}

	bool left = true;
	if (leftLen > 0)
		left = VerifySequenceOfBST(sequence, leftLen);

	bool right = true;
	if (length - leftLen - 1 > 0)
		right = VerifySequenceOfBST(sequence + leftLen, length - leftLen - 1);

	return (left && right);
}


int main() {
	int seq[] = {5, 7, 6, 9, 11, 10, 8};
	int seq2[] = {7, 4, 6, 5};
	std::cout << VerifySequenceOfBST(seq, 7) << std::endl;
	std::cout << VerifySequenceOfBST(seq2, 4) << std::endl;

	return 0;
}