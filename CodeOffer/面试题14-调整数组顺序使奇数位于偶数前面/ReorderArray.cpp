#include <iostream>

typedef bool (*FUNC)(int);

void swap(int &first, int &second) {
	int tmp = first;
	first = second;
	second = tmp;
}

bool isEven(int i) {
  	return i % 2 == 0;
}

void ReorderArray(int *number, int length, FUNC func) {
	if (number == NULL || length == 0)
		return;

	int head = 0;
	int tail = length - 1;

	while (head < tail) {
		while (head < tail && !func(number[head])) // odd
			head++;

		while (head < tail && func(number[tail])) // even
			tail--;

		if (head < tail)
			swap(number[head], number[tail]);
	}
}

int main() {
	int nums[] = {3, 4, 2, 7, 61, 15, 32, 48};
	int len = 8;

	ReorderArray(nums, len, isEven);

	for (int i = 0; i < len; i++)
		std::cout << nums[i] << " ";

	std::cout << std::endl;

	return 0;
}