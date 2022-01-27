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

const int numTestCases = 22;
const int arraySize = 200;

// HugeInt class definition
class HugeInt
{
public:
   // enable user to input a positive huge integer
   void input( istream &inFile );

   // outputs elems[ hugeInt.size - 1 .. 0 ]
   void output( ostream &outFile );

   // a recursive function that outputs elems[ last .. 0 ]
   void recursiveOutput( ostream &outFile, int last );

   // returns true if and only if the specified huge integer is zero
   bool isZero();

   // return true if and only if current object == hugeInt2
   bool equal( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveEqual( HugeInt &hugeInt2, int last );

   // return true if and only if current object < hugeInt2
   bool less( HugeInt &hugeInt2 );

   // a recursive function that returns true if and only if
   // elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
   // provided that size == hugeInt2.size
   bool recursiveLess( HugeInt &hugeInt2, int last );

   // request the current object to reduce its array to fit its size
   void shrink_to_fit();

   // sum = current object + adder
   void addition( HugeInt &adder, HugeInt &sum );

   // difference = current object - subtrahend
   // provided that the current object is greater than or equal to the subtrahend
   void subtraction( HugeInt &subtrahend, HugeInt &difference );

   // product = current object * multiplier
   void multiplication( HugeInt &multiplier, HugeInt &product );

   // quotient = current object / divisor; remainder = current object % divisor
   // provided that the divisor is not equal to 0
   void division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );

   // left = current object; assignment
   void assign( HugeInt &left );

   // current object /= 10
   void divideByTen();

   void reset();

   int size = 1; // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ]();  // used to store a nonnegative integer, one digit per element
}; // end class HugeInt


// enable user to input a positive huge integer
void HugeInt::input( istream &inFile )
{
   char numericString[ 200 ];

   inFile >> numericString;

   size = strlen( numericString );
   delete[] elems;
   elems = new int[ size ];
   for( int i = 0; i < size; i++ )
      elems[ i ] = numericString[ size - i - 1 ] - '0';
}

// output the specified huge integer
void HugeInt::output( ostream &outFile )
{
   recursiveOutput( outFile, size - 1 );
   outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void HugeInt::recursiveOutput( ostream &outFile, int last )
{
    if (last < 0) {
        return;
    }
    outFile << elems[last];
    recursiveOutput(outFile , last - 1);
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero()
{
   if( size == 1 && elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if current object == hugeInt2
bool HugeInt::equal( HugeInt &hugeInt2 )
{
   if( size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveEqual( HugeInt &hugeInt2, int last )
{
    if (last < 0) {
        return true;
    }
    if (elems[last] == hugeInt2.elems[last]) {
        return recursiveEqual(hugeInt2, last - 1);
    }
    else {
        return false;
    }
}

// returns true if and only if current object < hugeInt2
bool HugeInt::less( HugeInt &hugeInt2 )
{
   if( size < hugeInt2.size )
      return true;
   if( size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt2, size - 1 );
}

// a recursive function that returns true if and only if
// elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that size == hugeInt2.size
bool HugeInt::recursiveLess( HugeInt &hugeInt2, int last )
{
    if (hugeInt2.elems[last] > elems[last]) {
        return true;
    }
    if (hugeInt2.elems[last] < elems[last]) {
        return false;
    }
    if (last == 0) {
        return false;
    }
    return recursiveLess(hugeInt2, last - 1);
}
 
// request the current object to reduce its array to fit its size
void HugeInt::shrink_to_fit()
{
   int *buffer = new int[ size ];
   for( int i = 0; i < size; i++ )
      buffer[ i ] = elems[ i ];
   delete [] elems;
   elems = buffer;
}

// sum = current object + adder
void HugeInt::addition( HugeInt &adder, HugeInt &sum )
{
   sum.size = ( size >= adder.size ) ? size + 1 : adder.size + 1;

   delete[] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < size; i++ )
      sum.elems[ i ] = elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
   {
      sum.size--;
      sum.shrink_to_fit();
   }
}

// difference = current object - subtrahend
// provided that the current object is greater than or equal to the subtrahend
void HugeInt::subtraction( HugeInt &subtrahend, HugeInt &difference )
{
    difference.size = (size >= subtrahend.size) ?size : subtrahend.size;
    delete[] difference.elems;
    difference.elems = new int[difference.size]();

    if (equal(subtrahend)) {
        difference.reset();
        return;
    }

    for (int i = 0; i < size; i++)
        difference.elems[i] = elems[i];
    for (int i = 0; i < subtrahend.size; i++)
        difference.elems[i] -= subtrahend.elems[i];

    for (int i = 0; i < difference.size - 1; i++) {
        if (difference.elems[i] < 0) // carrying
        {
            difference.elems[i] += 10;
            difference.elems[i + 1]--;
        }
    }

    for (int a = difference.size - 1;a >= 0;a--) {
        if (difference.elems[a] == 0) {
            difference.size--;
            difference.shrink_to_fit();
        }
        else {
            break;
        }
    }
}

// product = current object * multiplier
void HugeInt::multiplication( HugeInt &multiplier, HugeInt &product )
{
    product.size = size + multiplier.size;
    delete[] product.elems;
    product.elems = new int[product.size]();


    for (int i = 0; i < multiplier.size; i++) {
        for (int j = 0; j < size; j++) {
            product.elems[i + j] += elems[j] * multiplier.elems[i];
        }
    }

    for (int a = 0; a < product.size - 1; a++) {
        while (product.elems[a] > 9) // carrying
        {
            product.elems[a] -= 10;
            product.elems[a + 1] ++;
        }
    }

    for (int a = product.size - 1;a >= 0;a--) {
        if (product.elems[product.size - 1] == 0) {
            if (a == 0 && product.elems[a] == 0) {
                product.reset();
                break;
            }
            product.size--;
            product.shrink_to_fit();
        }
    }
}

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInt::division( HugeInt &divisor, HugeInt &quotient, HugeInt &remainder )
{
    quotient.size = 1;
    delete[] quotient.elems;
    quotient.elems = new int[quotient.size]();
    remainder.size = size;
    delete[] remainder.elems;
    remainder.elems = new int[remainder.size]();
   if(isZero() )
   {
      quotient.reset();
      remainder.reset();
      return;
   }
   if (equal(divisor))   //如果被除式等於除式
   {
       quotient.elems[0] = 1;
       remainder.reset();
       return;
   }
   //remainder = dividend
   assign(remainder);
   HugeInt buffer, temp;
   buffer.size = size;
   temp.size = size;
   delete[] buffer.elems;
   buffer.elems = new int[size]();
   delete[] temp.elems;
   temp.elems = new int[size]();
   int k;
   //dividend < divisor
   if (less(divisor)) //如果被除式小於除式
   {
       quotient.reset();
   }
   else
   {
       //buffer = divisor shift left by n positions
       int n = size - divisor.size;
       for (int i = divisor.size - 1; i >= 0; i--) //buffer移位
           buffer.elems[i + n] = divisor.elems[i];

       //dividend < buffer
       quotient.size = n;
       if (less(buffer))
           buffer.divideByTen();
       else{
           quotient.size++;
           quotient.shrink_to_fit();
       }
       delete[] quotient.elems;
       quotient.elems = new int[quotient.size]();

       for (k = quotient.size - 1; k >= 0; k--)
       {//如果buffer<=remainder
          while (buffer.less(remainder) || buffer.equal(remainder))//buffer <= remainder
           {
               remainder.subtraction(buffer, temp);  //temp = remainder - buffer
               temp.assign( remainder );//remainder = temp
               //remainder.size = temp.size;
               quotient.elems[k]++;
               if (remainder.isZero())  //如果remainder=0
                   return;
           }
           buffer.divideByTen();  //buffer/10 
       }
   }
   delete[] buffer.elems;
   delete[] temp.elems;
   

}

// left = current object; assignment
void HugeInt::assign( HugeInt &left )
{
   left.size = size;
   delete[] left.elems;
   left.elems = new int[ left.size ];
   for( int i = 0; i < left.size; i++ )
      left.elems[ i ] = elems[ i ];
}

// current object /= 10
void HugeInt::divideByTen()
{
   if( size == 1 )
      elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         elems[ i - 1 ] = elems[ i ];

      size--;
      elems[ size ] = 0;
      shrink_to_fit();
   }
}

void HugeInt::reset()
{
   size = 1;
   delete[] elems;
   elems = new int[ 1 ]();
}


void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
                                HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   hugeInt1.output( outFile );
   hugeInt2.output( outFile );

   hugeInt1.addition( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   hugeInt3.output( outFile );
   hugeInt3.reset();

   if( hugeInt1.less( hugeInt2 ) )
   {
      outFile << '-';
      hugeInt2.subtraction( hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      hugeInt3.output( outFile );
   }
   else
   {
      hugeInt1.subtraction( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      hugeInt3.output( outFile );
   }
   hugeInt3.reset();

   hugeInt1.multiplication( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   hugeInt3.output( outFile );
   hugeInt3.reset();

   if( hugeInt2.isZero() )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
      hugeInt1.division( hugeInt2, hugeInt3, hugeInt4 );
      hugeInt3.output( outFile );
      hugeInt4.output( outFile );
      hugeInt3.reset();
      hugeInt4.reset();
   }

   outFile << endl;
}

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "D:\\school_hw\\Big1.1\\程式設計\\MyHW\\20201110\\Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "D:\\school_hw\\Big1.1\\程式設計\\MyHW\\20201110\\Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      hugeInt1.input( inFile );
      hugeInt2.input( inFile );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      hugeInt1.reset();
      hugeInt2.reset();
   }

   delete[] hugeInt1.elems;
   delete[] hugeInt2.elems;
   delete[] hugeInt3.elems;
   delete[] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}