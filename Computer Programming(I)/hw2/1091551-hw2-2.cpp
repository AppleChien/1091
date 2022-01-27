#include <iostream>
using namespace std;
int sum ;
void add(int number) {
	int a = number / 10000000;
	int b = number / 1000000 - 10 * a;
	int c = number / 100000 - 100 * a - 10 * b;
	int d = number / 10000 - 1000 * a - 100 * b - 10 * c;
	int e = number / 1000 - 10000 * a - 1000 * b - 100 * c - 10 * d;
	int f = number / 100 - 100000 * a - 10000 * b - 1000 * c - 100 * d - 10 * e;
	int g = number / 10 - 1000000 * a - 100000 * b - 10000 * c - 1000 * d - 100 * e - 10 * f;
	int h = number % 10;
	sum = a + b + c + d + e + f + g + h;

}


int main() {
	int number;
	
	cout << "Enter a positive integer of at most 8 digits:";
	cin >> number;
	add(number);
	cout << "The sum of all digits of " << number << " is " << sum << endl;

	

	return 0;
}