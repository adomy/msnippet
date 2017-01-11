#include <iostream>
#include <exception>

int MinNumberInRotatedArray(int *numbers, int length) {
	if (numbers == NULL || length <= 0)
		throw new std::exception("Invalid parameters.");

	int low_i = 0;
	int high_i = length - 1;
	int mid_i = 0;

	while (low_i < high_i) {
		if (numbers[low_i] < numbers[high_i])
			return numbers[low_i];

		if (numbers[low_i] == numbers[high_i]) {
			int min = numbers[low_i];
			for (int i = low_i + 1; i <= high_i; i++) {
				if (min > numbers[i])
					min = numbers[i];
			}

			return min;
		}

		mid_i = (low_i + high_i) / 2;

		if (numbers[mid_i] >= numbers[high_i])
			low_i = mid_i + 1;
		else
			high_i = mid_i;
	}

	return numbers[low_i];
}

int main() {
	//int numbers[] = {3, 4, 5, 1, 2};
	int numbers[] = {1, 2, 3, 4, 5};
	//int numbers[] = {1, 0, 1, 1, 1};

	int min = MinNumberInRotatedArray(numbers, 5);

	std::cout << "Min Value= " << min << std::endl;

	return 0;
}