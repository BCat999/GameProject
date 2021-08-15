#include <iostream>
#include <stdio.h>
using namespace std;



long long factorial(int& n, long long& y) {
	if (n == 0) cout << n << "!= 1";
	if (n <= 2) cout << n << "!= " << n;
	else {
		for (int i = 2; i <= n; i++)
			y = y * i;
	}
	return y;
}

int main() {

	int x;
	long long y = 1;

	do {
		cout << "Enter an integer(<20): ";
		cin >> x;
	} while (x < 0 || x>20);

	cout << x << "!= " << factorial(x, y);

	return 0;
}