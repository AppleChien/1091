#include <iostream>
using namespace std;

// computes and returns 1 * 1 + 2 * 2 + ... + n * n
int sumSquare( int n );

int main()
{
   int n;
   cin >> n;
   
   while( n > 0 )
   {  
      cout << sumSquare(n) << endl;
      cin >> n;
  
   }
   
   system( "pause" );
}

int sumSquare( int n )
{
    if (n == 1)
        return 1;
    else if (n <= 100 && n>0) {
        return n * n + sumSquare(n - 1);
    }
    
}