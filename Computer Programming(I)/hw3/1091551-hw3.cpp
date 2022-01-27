// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output( int polynomial[], int degree );

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int polynomial[], int degree );

// returns true if and only if polynomial1 == polynomial2
bool equal( int polynomial1[], int polynomial2[], int degree1, int degree2 );

// polynomial1 = -polynomial2
void minus( int polynomial1[], int polynomial2[], int &degree1, int degree2 );

// addend += adder
void addition( int addend[], int adder[], int &addendDegree, int adderDegree );

// minuend -= subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendDegree, int subtrahendDegree );

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandDegree, int multiplierDegree, int &productDegree );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendDegree, int divisorDegree, int &quotientDegree, int &remainderDegree );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "D:\\school_hw\\Big1.1\\�{���]�p\\MyHW\\20200929\\Polynomials.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened "<< endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int dividend[ arraySize ] = {};
      int divisor[ arraySize ] = {};

      // input dividend and divisor from the file Polynomials.dat
      inFile.read( reinterpret_cast< char * >( dividend ), 80 );
      inFile.read( reinterpret_cast< char * >( divisor ), 80 );

      int dividendDegree = arraySize - 1;
      while( dividendDegree > 0 && dividend[ dividendDegree ] == 0 )
         dividendDegree--;

      int divisorDegree = arraySize - 1;
      while( divisorDegree > 0 && divisor[ divisorDegree ] == 0 )
         divisorDegree--;

      cout << "dividend:  ";
      output( dividend, dividendDegree );
      cout << "divisor:  ";
      output( divisor, divisorDegree );

      int quotient[ arraySize ] = {};
      int remainder[ arraySize ] = {};
      int quotientDegree = 0;
      int remainderDegree = 0;

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividend, divisor, quotient, remainder,
                dividendDegree, divisorDegree, quotientDegree, remainderDegree );

      if( quotientDegree != 0 && quotient[ quotientDegree ] == 0 )
         cout << "Leading zeroes not allowed1!\n";

      int buffer[ arraySize ] = {};
      int bufferDegree = 1;

      // buffer = divisor * quotient
      multiplication( divisor, quotient, buffer, divisorDegree, quotientDegree, bufferDegree );

      if( bufferDegree != 0 && buffer[ bufferDegree ] == 0 )
         cout << "Leading zeroes not allowed2!\n";

      // buffer = buffer + remainder = divisor * quotient + remainder
      addition( buffer, remainder, bufferDegree, remainderDegree );

      if( bufferDegree != 0 && buffer[ bufferDegree ] == 0 )
         cout << "Leading zeroes not allowed3!\n";

      // if buffer != dividend, an error occurred!
      if( equal( buffer, dividend, bufferDegree, dividendDegree ) )
         numErrors--;
   }

   inFile.close();

   cout << "\nThere are " << numErrors << " errors.\n\n";

   system( "pause" );
}

// outputs the specified polynomial
void output( int polynomial[], int degree )
{
   if( isZero( polynomial, degree ) ) // zero polynomial
      cout << 0;
   else
   {
      if( degree == 0 ) // constant polynomial
      {
         if( polynomial[ 0 ] < 0 )
            cout << "-" << -polynomial[ 0 ];
         else if( polynomial[ 0 ] > 0 )
            cout << polynomial[ 0 ];
      }
      else
      {
         if( degree == 1 ) // polynomial of degree 1
         {
            if( polynomial[ 1 ] < 0 )
               cout << "-" << -polynomial[ 1 ] << "x";
            else if( polynomial[ 1 ] > 0 )
               cout << polynomial[ 1 ] << "x";
         }
         else // polynomial of degree at least 2
         {
            // display the leading term
            if( polynomial[ degree ] < 0 )
               cout << "-" << -polynomial[ degree ] << "x^" << degree;
            else if( polynomial[ degree ] > 0 )
               cout << polynomial[ degree ] << "x^" << degree;

            // display all other terms
            for( int i = degree - 1; i > 1; i-- )
               if( polynomial[ i ] < 0 )
                  cout << " - " << -polynomial[ i ] << "x^" << i;
               else if( polynomial[ i ] > 0 )
                  cout << " + " << polynomial[ i ] << "x^" << i;

            // display the term of degree 1
            if( polynomial[ 1 ] < 0 )
               cout << " - " << -polynomial[ 1 ] << "x";
            else if( polynomial[ 1 ] > 0 )
               cout << " + " << polynomial[ 1 ] << "x";
         }

         // display the constant term
         if( polynomial[ 0 ] < 0 )
            cout << " - " << -polynomial[ 0 ];
         else if( polynomial[ 0 ] > 0 )
            cout << " + " << polynomial[ 0 ];
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero( int polynomial[], int degree )
{  // leading term is 0
   if( degree == 0 && polynomial[ 0 ] == 0 )
      return true;
   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int polynomial1[], int polynomial2[], int degree1, int degree2 )
{//equal���~�I�b��P�_�T�{�u�����y�k���~(check = true;//�T�{�O�u)
    bool check = false;
    if (degree1 == degree2) {//���p��ӬۦP�}�C��m
        for (int i = 0;i <= degree1;i++) {//�q�̧C�}�C��m���W
            if (polynomial1[i] == polynomial2[i])//���p�Q�����P�����}�C��m�P�ȬۦP
                check = true;//�T�{�O�u
            else
                return false;//�_�h�O��
        }
    }
    if (check)//���p�T�{����
        return true;//�^�Ǭ��u
    else
        return false;//�_�h�^�Ǭ���
}

// polynomial1 = -polynomial2
void minus( int polynomial1[], int polynomial2[], int &degree1, int degree2 )
{
   degree1 = degree2;//�Q��Ƹ��ƪ��̰��}�C��m�ۦP
   for( int i = 0; i <= degree1; i++ )//�Q��ƪ��̧C�}�C��m���W
      polynomial1[ i ] = -polynomial2[ i ];//�Q��ƻP��ƪ��`�t��
}

// addend += adder
void addition( int addend[], int adder[], int &addendDegree, int adderDegree )
{
    for (int i=0;i <= addendDegree;i++) {//�Q�[�ƪ��̧C�}�C��m���W
        addend[i] += adder[i];//�Q�[�ƻP�[�ƪ��`�M��
    }
}

// minuend -= subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendDegree, int subtrahendDegree )
{
   int buffer[ arraySize ] = {};
   int bufferDegree = 0;

   // buffer = -subtrahend
   minus( buffer, subtrahend, bufferDegree, subtrahendDegree );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuend, buffer, minuendDegree, bufferDegree );

   if( minuendDegree != 0 && minuend[ minuendDegree ] == 0 )
      cout << "Leading zeroes not allowed!\n";
}

// product = multiplicand * multiplier

void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandDegree, int multiplierDegree, int &productDegree )
{
    productDegree = 0;
    for (int i = 0;i <= multiplicandDegree;i++) {//�Q���ƪ��̧C�}�C��m���W      
        for (int j = 0;j <= multiplierDegree;j++){ //���ƪ��̧C�}�C��m���W
            product[j + i] += multiplicand[i] * multiplier[j];//�n���}�C��m�����`�M��
            productDegree = i + j;//�n���}�C��m
            
        }
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendDegree, int divisorDegree, int &quotientDegree, int &remainderDegree )
{
   if( isZero( dividend, dividendDegree ) )
   {
      quotientDegree = 0;//�]�Ӫ��̰��}�C��m��0
      quotient[ 0 ] = 0;//�]�Ӫ��}�C��m0���Ȭ�0

      remainderDegree = 0;//�]�@�ӼȦs���̰��}�C��m��0
      remainder[ 0 ] = 0;//�]�Ȧs���}�C��m0���Ȭ�0
      return;
   }
   for (int i = 0;i <= dividendDegree;i++)//�Q���ƪ��}�C�̧C��m���W
       remainder[i] = dividend[i];//�N�Q���ư}�C���Ȧs��Ȧs�}�C��
   remainderDegree = dividendDegree;//�Q�������̰��}�C��m����Ȧs���̰��}�C��m
   
   quotientDegree = dividendDegree - divisorDegree;//�Ӧ����̰��}�C��m����Q�������̰��}�C��m������̰��}�C��m

   int x = remainderDegree;
   for (int i = dividendDegree - divisorDegree;i >= 0;i--,x--) {//�Ӫ��}�C�̰���m����
       quotient[i] = remainder[x] / divisor[divisorDegree];//�Ӫ��ȵ���Q���ƪ��Ȱ��H�������̰����誺��
       for (int j = 0;divisorDegree + j >= 0;j--) {//�������}�C�̰���m����
           remainder[x + j] -= divisor[divisorDegree + j] * quotient[i];//�Q����������Ӫ���
       }
       
   }
   
       
   
   
   
   
}