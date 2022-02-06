// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size );

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 );

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 );

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize );

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int dividendCoef[], int dividendExpon[], int dividendSize,
               int divisorCoef[], int divisorExpon[], int divisorSize,
               int quotientCoef[], int quotientExpon[], int &quotientSize,
               int remainderCoef[], int remainderExpon[], int &remainderSize );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int dividendCoef[ arraySize ] = {};
      int dividendExpon[ arraySize ] = {};
      int divisorCoef[ arraySize ] = {};
      int divisorExpon[ arraySize ] = {};

      // input dividend and divisor from the file Polynomials.dat
      inFile.read( reinterpret_cast< char * >( dividendCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( dividendExpon ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorCoef ), 80 );
      inFile.read( reinterpret_cast< char * >( divisorExpon ), 80 );

      int dividendSize = arraySize;
      while( dividendSize > 1 && dividendCoef[ dividendSize - 1 ] == 0 )
         dividendSize--;

      int divisorSize = arraySize;
      while( divisorSize > 1 && divisorCoef[ divisorSize - 1 ] == 0 )
         divisorSize--;

      int quotientCoef[ arraySize ] = {};
      int quotientExpon[ arraySize ] = {};
      int remainderCoef[ arraySize ] = {};
      int remainderExpon[ arraySize ] = {};
      int quotientSize = 1;
      int remainderSize = 1;

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividendCoef, dividendExpon, dividendSize,
                divisorCoef, divisorExpon, divisorSize,
                quotientCoef, quotientExpon, quotientSize,
                remainderCoef, remainderExpon, remainderSize );

      if( zeroTerms( quotientCoef, quotientSize ) )
         cout << "quotient has at least a zero term!\n";

      int bufferCoef[ arraySize ] = {};
      int bufferExpon[ arraySize ] = {};
      int bufferSize = 1;

      // buffer = divisor * quotient
      multiplication( divisorCoef, divisorExpon, divisorSize,
                      quotientCoef, quotientExpon, quotientSize,
                      bufferCoef, bufferExpon, bufferSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term1!\n";

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( bufferCoef, bufferExpon, bufferSize,
                remainderCoef, remainderExpon, remainderSize );

      if( zeroTerms( bufferCoef, bufferSize ) )
         cout << "buffer has at least a zero term2!\n";

      // if buffer != dividend, an error occurred!
      if( equal( bufferCoef, bufferExpon, bufferSize,
                 dividendCoef, dividendExpon, dividendSize ) )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n";

   system( "pause" );
}

// outputs the specified polynomial
void output( int coefficient[], int exponent[], int size )
{
   // the specified polynomial is zero polynomial
   if( isZero( coefficient, size ) )
      cout << 0;
   else
   {
      if( coefficient[ size - 1 ] < 0 )
         cout << "-" << -coefficient[ size - 1 ];
      else if( coefficient[ size - 1 ] > 0 )
         cout << coefficient[ size - 1 ];

      if( exponent[ size - 1 ] > 0 )
      {
         if( exponent[ size - 1 ] == 1 )
            cout << "x";
         else
            cout << "x^" << exponent[ size - 1 ];
      }

      for( int i = size - 2; i >= 0; i-- )
      {
         if( coefficient[ i ] < 0 )
            cout << " - " << -coefficient[ i ];
         else if( coefficient[ i ] > 0 )
            cout << " + " << coefficient[ i ];

         if( exponent[ i ] > 0 )
         {
            if( exponent[ i ] == 1 )
               cout << "x";
            else
               cout << "x^" << exponent[ i ];
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms( int coefficient[], int size )
{
   if( !isZero( coefficient, size ) )
      for( int i = 0; i < size; i++ )
         if( coefficient[ i ] == 0 )
            return true;

   return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int coefficient[], int size )
{
   if( size == 1 && coefficient[ 0 ] == 0 )
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int coefficient1[], int exponent1[], int size1,
            int coefficient2[], int exponent2[], int size2 )
{
    /*if (size1 == size2) {//判斷size是否相同
        for (int i = 0;i <= size1;i++) {//size由低至高遞增
            if (coefficient1[i] == coefficient2[i]) {//判斷係數是否相同
                if (exponent1[i] == exponent2[i]) {//判斷次方是否相同
                    continue;//回到迴圈開頭繼續判斷       
                }
                else
                    return false;//若不同則回傳否
            }
            else
                return false;//若不同則回傳否
        }
        return true;//若判斷到最後皆相同則回傳對
    }
    else
     return false;//若不同則回傳否*/
    if (size1 != size2)
    {
        return false;
    }
    for (int i = 0; i < size1; i++)
    {
        // returns false if coeffient or exponent is different.
        if (coefficient1[i] != coefficient2[i] || exponent1[i] != exponent2[i])
            return false;
    }
    return true;
    
}

// polynomial1 = -polynomial2
void minus( int coefficient1[], int exponent1[], int &size1,
            int coefficient2[], int exponent2[], int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      coefficient1[ i ] = -coefficient2[ i ];
      exponent1[ i ] = exponent2[ i ];
   }
}

// addend += adder
void addition( int addendCoef[], int addendExpon[], int &addendSize,
               int adderCoef[], int adderExpon[], int adderSize )
{
   // if( adder == 0 )
   if( isZero( adderCoef, adderSize ) )
      return;

   // if( addend == 0 )
   if( isZero( addendCoef, addendSize ) )
   {
      // addend = adder
      addendSize = adderSize;
      for( int i = 0; i < addendSize; i++ )
      {
         addendCoef[ i ] = adderCoef[ i ];
         addendExpon[ i ] = adderExpon[ i ];
      }
      return;
   }

   // buffer = 0
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = 1;

   // buffer = -adder
   minus( bufferCoef, bufferExpon, bufferSize, adderCoef, adderExpon, adderSize );

   // if( addend == -adder )
   if( equal( addendCoef, addendExpon, addendSize, bufferCoef, bufferExpon, bufferSize ) )
   {
      addendSize = 1;     // addend = 0;
      addendCoef[ 0 ] = 0;
      addendExpon[ 0 ] = 0;
      return;
   }

   int sumCoef[ arraySize ] = {};
   int sumExpon[ arraySize ] = {};
   int i = 0;
   int j = 0;
   int k = 0;
   while( i < addendSize && j < adderSize )
   {
             
         if (addendExpon[i] < adderExpon[j]) {//若被加數陣列位置次方小於加數陣列位置次方
              sumCoef[k] = addendCoef[i];//被加數位置的值放進總和位置
              sumExpon[k] = addendExpon[i];//被加數最高次方陣列位置放進總和最高次方陣列位置
              i++;
              k++;
             //若被加數陣列位置已經到最後一項但加數陣列位置還沒到最後一項
         }
          else if (addendExpon[i] > adderExpon[j]) {//若加數陣列位置次方小於被加數陣列位置次方
              sumCoef[k] = adderCoef[j];//若被加數陣列位置次方小於加數次方
              sumExpon[k] = adderExpon[j];//加數最高次方陣列位置放進總和最高次方陣列位置
              j++;
              k++;
              //若加數陣列位置已經到最後一項但被加數陣列位置還沒到最後一項
          }
          else if (addendExpon[i]==adderExpon[j]) {//若被加數陣列位置次方等於加數陣列位置次方
             if (addendCoef[i] + adderCoef[j] != 0) {
                 sumCoef[k] = addendCoef[i] + adderCoef[j];//被加數和加數的總和加回總和
                 sumExpon[k] = addendExpon[i];//被加數和加數的總和最高次方陣列位置放進總和最高次方陣列位置  
                 k++;
             }
             i++;
             j++;
          }
   }
   while (i < addendSize)//加數比被加數多項
   {
       sumCoef[k] = addendCoef[i];//剩下的放到總和
       sumExpon[k] = addendExpon[i];//剩下的放到總和
       i++;
       k++;

   }
   while (j < adderSize)//被加數比加數多項
   {
       sumCoef[k] = adderCoef[j];//剩下的放到總和
       sumExpon[k] = adderExpon[j];//剩下的放到總和
       j++;
       k++;

   }
   
   
   addendSize = k;
   for( int i = 0; i < addendSize; i++ ) // addend = sum
   {
      addendCoef[ i ] = sumCoef[ i ];
      addendExpon[ i ] = sumExpon[ i ];
   }
}

// minuend -= subtrahend
void subtraction( int minuendCoef[], int minuendExpon[], int &minuendSize,
                  int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize )
{
   // minuend == subtrahend
   if( equal( minuendCoef, minuendExpon, minuendSize, subtrahendCoef, subtrahendExpon, subtrahendSize ) )
   {
      minuendSize = 1;     // minuend = 0;
      minuendCoef[ 0 ] = 0;
      minuendExpon[ 0 ] = 0;
      return;
   }

   // buffer = 0
   int bufferCoef[ arraySize ] = {};
   int bufferExpon[ arraySize ] = {};
   int bufferSize = 1;

   // buffer = -subtrahend
   minus( bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize );

   if( minuendSize > 1 && minuendCoef[ minuendSize - 1 ] == 0 )
      cout << "Leading zeroes not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication( int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
                     int multiplierCoef[], int multiplierExpon[], int multiplierSize,
                     int productCoef[], int productExpon[], int &productSize )
{
   // product = 0;
   productSize = 1;
   productCoef[ 0 ] = 0;
   productExpon[ 0 ] = 0;

   // if( multiplicand != 0 && multiplier != 0 )
   if( !isZero( multiplicandCoef, multiplicandSize ) &&
       !isZero( multiplierCoef, multiplierSize ) )
   {
       
       int bufferCoef[arraySize] = {};
       int bufferExpon[arraySize] = {};
       int bufferSize = multiplicandSize;
       for (int i = 0;i < multiplierSize;i++) {//乘數陣列位置由低至高遞增
           for (int j = 0;j < multiplicandSize;j++) {//被乘數陣列位置由低至高遞增
               
               bufferCoef[j] = multiplicandCoef[j] * multiplierCoef[i];//被乘數和乘數之積的係數存至buffer係數
               bufferExpon[j] = multiplicandExpon[j] + multiplierExpon[i];//被乘數和乘數之和的次方存至buffer次方
               
           }
           addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
           //呼叫加法將product和buffer相加
       }
   }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int dividendCoef[], int dividendExpon[], int dividendSize,
               int divisorCoef[], int divisorExpon[], int divisorSize,
               int quotientCoef[], int quotientExpon[], int &quotientSize,
               int remainderCoef[], int remainderExpon[], int &remainderSize )
{
   // if( dividend == 0 )
   if( isZero( dividendCoef, dividendSize ) )
   {
      // quotient = 0
      quotientSize = 1;
      quotientCoef[ 0 ] = 0;
      quotientExpon[ 0 ] = 0;

      // remainder = 0
      remainderSize = 1;
      remainderCoef[ 0 ] = 0;
      remainderExpon[ 0 ] = 0;
      return;
   }

   // remainder = dividend
   remainderSize = dividendSize;
   for( int i = 0; i < remainderSize; i++ )//被除式次方由低至高遞增
   {
      remainderCoef[ i ] = dividendCoef[ i ];
      remainderExpon[ i ] = dividendExpon[ i ];
   }
   //商式陣列大小等於(被除式陣列大小減1)-(除式陣列大小減1)+1
   quotientSize = dividendExpon[ dividendSize - 1 ] - divisorExpon[ divisorSize - 1 ] + 1;
   
   for( int i = quotientSize - 1; i >= 0; i--)
   {   //若被除式最高次方等於0或是被除式次方小於除式次方(要除之前都先判斷好)
       /*if (remainderCoef[remainderSize-1] == 0 ||
           remainderExpon[remainderSize - 1] < divisorExpon[divisorSize - 1])
       {
           for (int j = 0;j < i;j++) {//從最後一項開始右移
               for (int k = 0;k <= quotientSize - 1;k++) {
                   quotientCoef[k] = quotientCoef[k + j];
                   quotientExpon[k] = quotientExpon[k + j];
                   
               }
               quotientSize--;//每移1次size減1
           }
           break;//若判斷完則結束迴圈
       }*/
       //商式的值等於被除式的值除以除式的值
       quotientCoef[i] = remainderCoef[remainderSize - 1] / divisorCoef[divisorSize - 1];
       //商式的次方等於被除式的次方減掉除式的次方
       quotientExpon[i] = remainderExpon[remainderSize - 1 ] -divisorExpon[divisorSize - 1];
      
       //monomial = quotient[i]
       int monomialSize=1;
       int monomialCoef[1] = {};
       int monomialExpon[1] = {};
       monomialCoef[0] = quotientCoef[i];//將商式係數的值暫存到monomial
       monomialExpon[0] = quotientExpon[i];//將商式次方的值暫存到monomial

       //buffer = divisor * monomial;將除式跟商的積暫存到buffer
       int bufferCoef[arraySize] = {};
       int bufferExpon[arraySize] = {};
       int bufferSize = divisorSize;
       multiplication(divisorCoef, divisorExpon, divisorSize, 
           monomialCoef, monomialExpon, monomialSize,bufferCoef,bufferExpon,bufferSize);
       // remainder -= buffer;remainder減buuffer的值存回remainder
       subtraction(remainderCoef, remainderExpon, remainderSize,bufferCoef,bufferExpon,bufferSize);

       //若被除式最高次方等於0或是被除式次方小於除式次方    
       if (remainderCoef[remainderSize - 1] == 0 || remainderExpon[remainderSize - 1] < divisorExpon[divisorSize - 1])
       {
           
           for (int j = i; j > 0; j--)//商式往右移i次
           {
               for (int k = j; k < quotientSize; k++)//從商式最低項開始右移
               {
                   quotientCoef[k - 1] = quotientCoef[k];
                   quotientExpon[k - 1] = quotientExpon[k];
               }
               quotientSize--;//右移之後商式大小減1
               quotientCoef[quotientSize] = 0;//右移之後商式最高次方係數=0
               quotientExpon[quotientSize] = 0;//右移之後商式最高次方=0
           }

           break;//若判斷完則結束迴圈
       }
           
   }
}
