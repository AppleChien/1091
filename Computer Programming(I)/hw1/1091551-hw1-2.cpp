#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int number; // integer read from user

   cout << "Enter a five-digit integer: "; // prompt
   cin >> number; // read integer from user
   int a, b, c, d, e;
   a = number / 10000;
   b = number / 1000 - 10 * a;
   c = number / 100 - 100 * a - 10 * b;
   d = number / 10 - 1000 * a - 100 * b - 10 * c;
   e = number - 10000 * a - 1000 * b - 100 * c - 10 * d;
   cout << a << " " << b << " " << c << " " << d << " " << e << endl;


   system( "pause" );
} // end main