#include <stdio.h>
#include <iostream>

void swap1(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void swap2(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}
int main() {
	int a, b;
	std::cout << "nhap a: ";
	std::cin >> a;
	std::cout << "nhap b: ";
	std::cin >> b;

	swap1(&a, &b);
	//swap2(a, b);

	std::cout << "a = " << a << " b = " << b;
}
