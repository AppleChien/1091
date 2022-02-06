#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// enable user to input a positive huge integer
void input( istream &inFile, vector< int > &hugeInt );

// performs addition, subtraction, multiplication, division and modulus
void perform( ostream &outFile, vector< int > &hugeInt1, vector< int > &hugeInt2 );

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output( ostream &outFile, vector< int > &hugeInt );

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput( ostream &outFile, vector< int > &hugeInt, size_t last );

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > &hugeInt );

// returns true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > &hugeInt1, vector< int > &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual( vector< int > &hugeInt1, vector< int > &hugeInt2, size_t last );

// returns true if and only if hugeInt1 < hugeInt2
bool less( vector< int > &hugeInt1, vector< int > &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess( vector< int > &hugeInt1, vector< int > &hugeInt2, size_t last );

// returns addend + adder
vector< int > addition( vector< int > &addend, vector< int > &adder );

// returns minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
vector< int > subtraction( vector< int > &minuend, vector< int > &subtrahend );

// returns multiplicand * multiplier
vector< int > multiplication( vector< int > &multiplicand, vector< int > &multiplier );

// returns dividend / divisor
// provided that the divisor is not equal to 0
vector< int > division( vector< int > &dividend, vector< int > &divisor );

// returns dividend % divisor
// provided that the divisor is not equal to 0
vector< int > modulus( vector< int > &dividend, vector< int > &divisor );

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt );

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i < numTestCases; i++ )
   {
      vector< int > hugeInt1;
      vector< int > hugeInt2;
      input( inFile, hugeInt1 );
      input( inFile, hugeInt2 );
      perform( cout, hugeInt1, hugeInt2 );
      perform( outFile, hugeInt1, hugeInt2 );
   }

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, vector< int > &hugeInt )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   hugeInt.resize( strlen( numericString ) );
   for( size_t i = 0; i < hugeInt.size(); i++ )
      hugeInt[ hugeInt.size() - i - 1 ] = numericString[ i ] - '0';
}

// performs addition, subtraction, multiplication and division
void perform( ostream &outFile, vector< int > &hugeInt1, vector< int > &hugeInt2 )
{
   output( outFile, hugeInt1 );
   output( outFile, hugeInt2 );

   vector< int > hugeInt3 = addition( hugeInt1, hugeInt2 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( outFile, hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      outFile << '-';
      hugeInt3 = subtraction( hugeInt2, hugeInt1 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( outFile, hugeInt3 );
   }
   else
   {
      hugeInt3 = subtraction( hugeInt1, hugeInt2 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( outFile, hugeInt3 );
   }

   hugeInt3 = multiplication( hugeInt1, hugeInt2 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( outFile, hugeInt3 );

   if( isZero( hugeInt2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      hugeInt3 = division( hugeInt1, hugeInt2 ); // hugeInt3 = hugeInt1 / hugeInt2
      output( outFile, hugeInt3 );

      hugeInt3 = modulus( hugeInt1, hugeInt2 ); // hugeInt3 = hugeInt1 % hugeInt2
      output( outFile, hugeInt3 );
   }

   outFile << endl;
}

// outputs hugeInt[ hugeInt.size() - 1 .. 0 ]
void output( ostream &outFile, vector< int > &hugeInt )
{
   recursiveOutput( outFile, hugeInt, hugeInt.size() - 1 );
   outFile << endl;
}

// a recursive function that outputs hugeInt[ last .. 0 ]
void recursiveOutput( ostream &outFile, vector< int > &hugeInt, size_t last )
{
    outFile << hugeInt[ last ];
    if( last > 0 )
    recursiveOutput( outFile, hugeInt, last - 1 );
}

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > &hugeInt )
{
   for( size_t i = 0; i < hugeInt.size(); i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// returns true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > &hugeInt1, vector< int > &hugeInt2 )
{
   if( hugeInt1.size() != hugeInt2.size() )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size() - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] == hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveEqual( vector< int > &hugeInt1, vector< int > &hugeInt2, size_t last )
{
    if (last == 0 && hugeInt1[last] == hugeInt2[last]) {
        return true;
    }
    if (hugeInt1[last] == hugeInt2[last]) {
        return recursiveEqual(hugeInt1, hugeInt2, last - 1);
    }
    else {
        return false;
    }
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( vector< int > &hugeInt1, vector< int > &hugeInt2 )
{
   if( hugeInt1.size() < hugeInt2.size() )
      return true;
   if( hugeInt1.size() > hugeInt2.size() )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size() - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1[ 0 .. last ] < hugeInt2[ 0 .. last ]
// provided that hugeInt1.size() == hugeInt2.size()
bool recursiveLess( vector< int > &hugeInt1, vector< int > &hugeInt2, size_t last )
{
    if( hugeInt2[ last ] > hugeInt1[ last ] ) {
        return true;
    }
    if( hugeInt2[ last ] < hugeInt1[ last ] ) {
        return false;
    }
    if( last == 0 ) {
        return false;
    }
    return recursiveLess( hugeInt1, hugeInt2, last - 1 );
}

// returns addend + adder
vector< int > addition( vector< int > &addend, vector< int > &adder )
{
   size_t sumSize = ( addend.size() >= adder.size() ) ? addend.size() + 1 : adder.size() + 1;
   vector< int > sum( sumSize );

   for( size_t i = 0; i < addend.size(); i++ )
      sum[ i ] = addend[ i ];

   for( size_t i = 0; i < adder.size(); i++ )
      sum[ i ] += adder[ i ];

   for( size_t i = 0; i < sum.size() - 1; i++ )
      if( sum[ i ] > 9 ) // determine whether to carry a 1
      {
         sum[ i ] -= 10; // reduce to 0-9
         sum[ i + 1 ]++;
      }

   if( sum[ sum.size() - 1 ] == 0 )
      sum.pop_back();

   return sum;
}

// returns minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
vector< int > subtraction( vector< int > &minuend, vector< int > &subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      vector< int > zero( 1 );
      return zero;
   }

   size_t differenceSize = (minuend.size() >= subtrahend.size()) ? minuend.size() : subtrahend.size();
   vector< int > difference(differenceSize);

   for (size_t i = 0; i < minuend.size(); i++)
       difference[i] = minuend[i];

   for (size_t i = 0; i < subtrahend.size(); i++)
       difference[i] -= subtrahend[i];

   for (size_t i = 0; i < difference.size(); i++)
       if (difference[i] < 0) // determine whether to carry a 1
       {
           difference[i] += 10; // reduce to 0-9
           difference[i + 1]--;
       }

   for (int a = difference.size() - 1; a >= 0; a--) {
       if (difference[a] == 0) {
           difference.pop_back();
       }
       else {
           return difference;
       }
   }
   /*if (difference[difference.size() - 1] == 0)
       difference.pop_back();*/

   return difference;
   
}

// returns multiplicand * multiplier
vector< int > multiplication( vector< int > &multiplicand, vector< int > &multiplier )
{
   if( isZero( multiplicand ) || isZero( multiplier ) )
   {
      vector< int > zero( 1 );
      return zero;
   }

   vector< int > product( multiplicand.size() + multiplier.size() );

   for( size_t i = 0; i < multiplier.size(); i++ ) {
       for( size_t j = 0; j < multiplicand.size(); j++ ) {
           product[ i + j ] += multiplicand[ j ] * multiplier[ i ];
       }
   }

   for( size_t a = 0; a < product.size() - 1; a++ ) {
       while( product[ a ] > 9 ) // carrying
       {
           product[ a ] -= 10;
           product[ a + 1 ] ++;
       }
   }

   /*for( size_t a = product.size() - 1; a >= 0; a-- ) {
       if( product[ product.size() - 1 ] == 0 ) {
           if( a == 0 && product[ a ] == 0 ) {
               product.size() == 1;
               product[ a ] == 0;
               return product;
           }
           product.pop_back();
       }
   }*/
   if(product[product.size() - 1]==0)
       product.pop_back();

   return product;
}

// returns dividend / divisor
// provided that the divisor is not equal to 0
vector< int > division( vector< int > &dividend, vector< int > &divisor )
{ 
   if( isZero( dividend ) || less( dividend, divisor ) )
   {
      vector< int > zero( 1 );
      return zero;
   }

   vector< int > remainder( dividend );
   vector< int > buffer( dividend.size() );

   for( size_t i = dividend.size()-divisor.size() ,j=0  ; j< divisor.size(); i++,j++ ) //buffer移位
       buffer[ i ] = divisor[ j ];

   int quotientSize = static_cast<int>(dividend.size() - divisor.size());
   if( less( dividend, buffer ) )
       divideByTen(buffer);
   else {
       quotientSize++;
   }
   vector< int > quotient(quotientSize);
   for (size_t i = 0;i < quotient.size();i++)
       quotient[i] = 0; //quotient每一位都放入0
   for( int k = quotientSize - 1; k >= 0; k-- )
   {//如果buffer<=remainder
       while( less(buffer, remainder ) || equal(buffer, remainder ) )//buffer <= remainder
       {
           remainder = subtraction( remainder,buffer );  //remainder = remainder - buffer
           quotient[ k ]++;
           if( isZero(remainder) )  //如果remainder=0
               return quotient;
       }
       divideByTen(buffer);  //buffer/10 
   }

   return quotient;
}

// returns dividend % divisor
// provided that the divisor is not equal to 0
vector< int > modulus( vector< int > &dividend, vector< int > &divisor )
{
   vector< int > quotient = division( dividend, divisor );      // quotient = dividend / divisor
   vector< int > product = multiplication( quotient, divisor ); // product = quotient * divisor
   vector< int > remainder = subtraction( dividend, product );  // remainder = dividend - product
   return remainder;
}

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt )
{
   if( hugeInt.size() == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( size_t i = 1; i < hugeInt.size(); i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];
      hugeInt[ hugeInt.size() - 1 ] = 0;
      hugeInt.pop_back();
   }
}
