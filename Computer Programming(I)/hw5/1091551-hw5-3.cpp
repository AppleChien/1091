#include <iostream>
#include <iomanip>
using namespace std;

// returns 10 ^ i == the ith power of ten
int powerOfTen( int i );

// prints all quirksome number from 0 to i
void quirksomeSquares( int i );

int power;
int n; // number of digits
int main()
{
   while( cin >> n )
   {
      power = powerOfTen( n / 2 );
     // cout << power << endl;
      // power = 10 ^ ( n / 2 ) == the ( n / 2 )th power of ten

      // print all quirksome number of n digits
      // power * power == 10 ^ n == the nth power of ten
      
      quirksomeSquares( power * power - 1 );
   }
}

// returns 10 ^ i == the ith power of ten
int powerOfTen( int i )
{
    int power = 10;
    if (i > 0 && i<=8) {
        power =power* powerOfTen(i - 1);
        return power;
    }
    else if(i==0)
        return 1;
}

// print all quirksome number from 0 to i
void quirksomeSquares(int i)
{
     
    if (i > 0)
        quirksomeSquares(i - 1);
    int sum = i / power + i % power;
    if (sum * sum == i)
        cout << setw(n) << setfill('0') << i << endl;


 }
