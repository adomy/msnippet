#include <iostream>
#include <cstring>

// length为字符数组string的总容量
void ReplaceBlank1(char string[], int length) {
	int i, j;
	int ns; 
	for (i = 0; string[i] != '\0'; i++) {
		if (string[i] != ' ') 
			continue;

		ns = i;
		while (string[ns] != '\0') 
			ns++;

		ns += 3;

		if (ns > length) {
			std::cout << "overflow" << std::endl;
			return;
		}

		for (j = ns; j >= i + 2; j--)
			string[j] = string[j - 2];

		string[i] = '%';
		string[i + 1] = '2';
		string[i + 2] = '0';
	}
}

void ReplaceBlank2(char string[], int length) {
	int original_length = 0;
	int blank_number = 0;

	int i = 0;
	while (string[i] != '\0') {
		original_length++;

		if (string[i] == ' ')
			blank_number++;

		i++;
	}

	int new_length = original_length + 2 * blank_number;

	if (new_length > length) {
		std::cout << "overflow" << std::endl;
		return;
	}

	int k = original_length;
	int l = new_length;
	while (k >= 0 && l > k) {
		if (string[k] != ' ') {
			string[l] = string[k];
			k--;
			l--;
			continue;
		} 

		string[l--] = '0';
		string[l--] = '2';
		string[l--] = '%';

		k--;
	}
}

int main() {
	char string[100] = "We are happy! ";
	ReplaceBlank2(string, 100);
	std::cout << string << std::endl;
	return 0;
}