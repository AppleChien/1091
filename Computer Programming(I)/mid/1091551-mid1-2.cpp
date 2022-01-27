#include <iostream>
using namespace std;

int oddSum(int a, int b)
{
	if (a > b) 
		return 0; 
	else {
		if (a >= b) 
			return a; 
		if (a < b) 
			return oddSum(a + 2, b) + a; 

	}

}

int main()
{
	int n, a, b;
	int sum = 0;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> a;
		cin >> b;
	
		if (a % 2 == 0) {
			a = a + 1;
		}

		cout << "Case " << i << ": " << oddSum(a, b) << endl;
		
	}
}