// Determine whether a number is a palindrome.
#include <iostream>
using namespace std; 

int main()
{
   int number;// user input number*a
   
   
   cout << "Enter a 5-digit number: "; // prompt for a number
   cin >> number; // get number
   int a, b, c, d, e;
   a = number / 10000;
   b = number / 1000-10*a;
   c = number / 100-100*a-10*b;
   d = number / 10-1000*a-100*b-10*c;
   e = number-10000*a-1000*b-100*c-10*d;
   
   if (a==e&&b==d)
	   cout << number<<" is a palindrome!!!" << endl;
   else
	   cout << number<<" is not a palindrome." << endl;




   system( "pause" );
} // end main