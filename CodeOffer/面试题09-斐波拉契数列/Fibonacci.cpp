#include <iostream>
#include <time.h>

#define MAXSIZE 1000

long long Fibonacci(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

long long f[MAXSIZE];

long long Fibonacci2(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	if (f[n] > 0)
		return f[n];

	int value = Fibonacci2(n - 1) + Fibonacci2(n - 2);
	f[n] = value;

	return value;
}

long long Fibonacci3(int n) {
	if (n <= 0)
		return 0;

	if (n == 1)
		return 1;

	long long first = 0;
	long long second = 1;
	long long nth = 0;

	for (int i = 2; i <= n; i++) {
		nth = first + second;

		first = second;
		second = nth;
	}

	return nth;
}

int main() {
	int n = 0;
	f[MAXSIZE] = {0};
	std::cin >> n;
	clock_t start = clock();
	std::cout << "Method 1 Result = " << Fibonacci(n) << std::endl;
	clock_t end_1 = clock();
	std::cout << "Time Consumed = " << end_1 - start << std::endl;

	std::cout << "Method 2 Result = " << Fibonacci2(n) << std::endl;
	clock_t end_2 = clock();
	std::cout << "Time Consumed = " << end_2 - end_1 << std::endl;

	std::cout << "Method 3 Result = " << Fibonacci3(n) << std::endl;
	clock_t end_3 = clock();
	std::cout << "Time Consumed = " << end_3 - end_2 << std::endl;
	return 0;
}