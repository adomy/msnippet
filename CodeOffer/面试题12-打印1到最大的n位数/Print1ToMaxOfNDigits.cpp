#include <iostream>
#include <cstring>

void Print1ToMaxOfNDigits_1(int n) {
	int number = 1;
	int i = 0;
	while (i < n) {
		number *= 10;
		i++;
	}

	for (i = 1; i < number; i++) {
		std::cout << i << "\t";
	}

	std::cout << std::endl;
}

bool IncrementNumber(char *number) {
	int length = std::strlen(number);

	int tmp = 0;
	int carry = 1; // 每次加一，通过Carry携带
	for (int i = length - 1; i >= 0; i--) {
		tmp = number[i] - '0' + carry;

		if (tmp < 10) {
			carry = 0;
			number[i] = tmp + '0';
			break;
		} else {
			carry = 1;
			number[i] = tmp % 10 + '0';
		}
 	}

	if (carry == 0)
		return false;

	return true;
}

void PrintNumber(char *number) {
	if (number == NULL)
		return;

	char *p = number;
	while (*p == '0') 
		p++;

	std::cout << p << "\t";
}
	

void Print1ToMaxOfNDigits_2(int n) {
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	std::memset(number, '0', n);
	number[n] = '\0';

	while (!IncrementNumber(number)) 
		PrintNumber(number);

	std::cout << std::endl;
	delete []number;
}

void Print1ToMaxOfNDigitsRecursively(char *number, int length, int index) {
	if (length - 1 == index) {
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; i++) {
		number[index + 1] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
	}
}

void Print1ToMaxOfNDigits_3(int n) {
	if (n <= 0)
		return;

	char *number = new char[n + 1];
	number[n] = '\0';

	for (int i = 0; i < 10; i++) {
		number[0] = '0' + i;
		Print1ToMaxOfNDigitsRecursively(number, n, 0);
	}

	delete []number;
}

int main() {
	int n;
	std::cin >> n;
	//Print1ToMaxOfNDigits_1(n);
	//Print1ToMaxOfNDigits_2(n);
	Print1ToMaxOfNDigits_3(n);
}