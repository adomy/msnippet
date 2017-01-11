#include <iostream>

double Power(double base, int exponent) {
	double result = 1.0;
	for (int i = 1; i <= exponent; i++)
		result *= base;

	return result;
}

double PowerWithUnsignedExponent(double base, int exponent) {
	if (exponent == 0)
		return 1;
	if (exponent == 1)
		return base;

	double tmp = PowerWithUnsignedExponent(base, exponent >> 1);
	return tmp * tmp * ((exponent & 0x1 == 1) ? base : 1);
}

double Power2(double base, int exponent) {
	if ((base - 0.0 > -0.0000001) && (base - 0.0 < 0.0000001))
		return 0;

	// 若底数为0，指数为负数，这是非法的
  	/*
  	 相关处理......
  	 */

	int flag = 0;
	if (exponent < 0) {
		flag = 1;
		exponent = -exponent;
	}

	double result = PowerWithUnsignedExponent(base, exponent);

	return (flag == 1) ? (1.0 / result) : result; 
}

int main() {
	double base;
	int exponent;
	std::cin >> base >> exponent;
	std::cout << Power(base, exponent) << std::endl; //错误示例
	std::cout << Power2(base, exponent) << std::endl;

	return 0;
}