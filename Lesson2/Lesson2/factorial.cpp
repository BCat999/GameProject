#include <iostream>
#include <stdio.h>
using namespace std;

int x;
long long y=1;

void factorial(int n) {
	if (n <= 2) cout << n << "!= " << n;
	else {
		for (int i = 2; i <= x; i++)
			y = y * i;
		cout << n <<"!= "<< y;
	}
}

int main() {

	do {
		cout << "Enter an integer(<20): ";
		cin >> x;
	} while (x < 0 || x>20);
	
	if (x == 0) cout << "1";
	else factorial(x);

	return 0;
}