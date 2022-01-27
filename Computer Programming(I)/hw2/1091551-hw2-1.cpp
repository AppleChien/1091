#include <iostream>
using namespace std;
void binary(int num) {
	if (num>1)               
		binary(num/2);
	cout << num % 2;
}
void octal(int num) {
	if (num > 7)
		octal(num / 8);
	cout << num % 8;
}

int main() {
	int number;
	cout << "Enter a positive decimal integer of at most 8 digits:";
	cin >> number;
	cout << "The binary equivalent of " << number << " is ";
	binary(number);
	cout << endl;
	cout << "The octal equivalent of " << number << " is ";
	octal(number);
	cout << endl;
	
	

	
	return 0;
}