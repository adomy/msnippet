#include <iostream>

int NumberOfOne(int n) {
	int count = 0;
	while (n) {
		if (n & 1)
			count++;

		n = n >> 1;
	}

	return count;
}

int NumberOfOne2(int n) {
	int count = 0;
	unsigned int flag = 1;
	while (flag) {
		if (n & flag)
			count++;

		flag = flag << 1;
	}

	return count;
}

int NumberOfOne3(int n) {
	int count = 0;
	while (n) {
		count++;
		n = (n - 1) & n;
	}

	return count;
}

int main() {
	int number;
	std::cin >> number;
	std::cout << "Count of 1 = " << NumberOfOne(number) << std::endl;
	return 0;
}