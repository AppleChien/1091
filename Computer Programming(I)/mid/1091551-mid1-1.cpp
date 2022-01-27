// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

// outputs the specified polynomial
void output(int coefficient[], int exponent[], int size);

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms(int coefficient[], int size);

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int size);

// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], int exponent1[], int size1,
	int coefficient2[], int exponent2[], int size2);

// a recursive function that returns true if and only if polynomial1 == polynomial2
// provided that size1 == size2
bool recursiveEqual(int coefficient1[], int exponent1[],
	int coefficient2[], int exponent2[], int last);

// polynomial1 = -polynomial2
void minus(int coefficient1[], int exponent1[], int& size1,
	int coefficient2[], int exponent2[], int size2);

// addend += adder
void addition(int addendCoef[], int addendExpon[], int& addendSize,
	int adderCoef[], int adderExpon[], int adderSize);

// minuend -= subtrahend
void subtraction(int minuendCoef[], int minuendExpon[], int& minuendSize,
	int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize);

// product = multiplicand * multiplier
void multiplication(int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
	int multiplierCoef[], int multiplierExpon[], int multiplierSize,
	int productCoef[], int productExpon[], int& productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(int dividendCoef[], int dividendExpon[], int dividendSize,
	int divisorCoef[], int divisorExpon[], int divisorSize,
	int quotientCoef[], int quotientExpon[], int& quotientSize,
	int remainderCoef[], int remainderExpon[], int& remainderSize);

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
	ifstream inFile("Polynomials.dat", ios::in | ios::binary);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	int numErrors = numTestCases;
	for (int i = 0; i < numTestCases; i++)
	{
		int dividendCoef[arraySize] = {};
		int dividendExpon[arraySize] = {};
		int divisorCoef[arraySize] = {};
		int divisorExpon[arraySize] = {};

		// input dividend and divisor from the file Polynomials.dat
		inFile.read(reinterpret_cast<char*>(dividendCoef), 80);
		inFile.read(reinterpret_cast<char*>(dividendExpon), 80);
		inFile.read(reinterpret_cast<char*>(divisorCoef), 80);
		inFile.read(reinterpret_cast<char*>(divisorExpon), 80);

		int dividendSize = arraySize;
		while (dividendSize > 0 && dividendCoef[dividendSize - 1] == 0)
			dividendSize--;

		int divisorSize = arraySize;
		while (divisorSize > 0 && divisorCoef[divisorSize - 1] == 0)
			divisorSize--;

		int quotientCoef[arraySize] = {};
		int quotientExpon[arraySize] = {};
		int remainderCoef[arraySize] = {};
		int remainderExpon[arraySize] = {};
		int quotientSize = 0;
		int remainderSize = 0;

		cout << "dividend:  ";
		output(dividendCoef, dividendExpon, dividendSize);

		cout << " divisor:  ";
		output(divisorCoef, divisorExpon, divisorSize);

		// quotient = dividend / divisor; remainder = dividend % divisor
		// thus, dividend == divisor * quotient + remainder
		division(dividendCoef, dividendExpon, dividendSize,
			divisorCoef, divisorExpon, divisorSize,
			quotientCoef, quotientExpon, quotientSize,
			remainderCoef, remainderExpon, remainderSize);

		cout << "quotient:  ";
		output(quotientCoef, quotientExpon, quotientSize);
		cout << endl;

		if (zeroTerms(quotientCoef, quotientSize))
			cout << "quotient has at least a zero term!\n";

		int bufferCoef[arraySize] = {};
		int bufferExpon[arraySize] = {};
		int bufferSize = 0;

		// buffer = divisor * quotient
		multiplication(divisorCoef, divisorExpon, divisorSize,
			quotientCoef, quotientExpon, quotientSize,
			bufferCoef, bufferExpon, bufferSize);

		if (zeroTerms(bufferCoef, bufferSize))
			cout << "buffer has at least a zero term!\n";

		// buffer = buffer + remainder = divisor * quotient + remainder
		addition(bufferCoef, bufferExpon, bufferSize,
			remainderCoef, remainderExpon, remainderSize);

		if (zeroTerms(bufferCoef, bufferSize))
			cout << "buffer has at least a zero term!\n";

		// if buffer != dividend, an error occurred!
		if (equal(bufferCoef, bufferExpon, bufferSize,
			dividendCoef, dividendExpon, dividendSize))
			numErrors--;
	}

	inFile.close();

	cout << "There are " << numErrors << " errors!\n\n";

	system("pause");
}

// outputs the specified polynomial
void output(int coefficient[], int exponent[], int size)
{
	// the specified polynomial is zero polynomial
	if (isZero(size))
		cout << 0;
	else
	{
		if (coefficient[0] < 0)
			cout << "-" << -coefficient[0];
		else if (coefficient[0] > 0)
			cout << coefficient[0];

		if (exponent[0] > 0)
		{
			if (exponent[0] == 1)
				cout << "x";
			else
				cout << "x^" << exponent[0];
		}

		for (int i = 1; i < size; i++)
		{
			if (coefficient[i] < 0)
				cout << " - " << -coefficient[i];
			else if (coefficient[i] > 0)
				cout << " + " << coefficient[i];

			if (exponent[i] > 0)
			{
				if (exponent[i] == 1)
					cout << "x";
				else
					cout << "x^" << exponent[i];
			}
		}
	}

	cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool zeroTerms(int coefficient[], int size)
{
	if (!isZero(size))
		for (int i = 0; i < size; i++)
			if (coefficient[i] == 0)
				return true;

	return false;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int size)
{
	return (size == 0);
}

// returns true if and only if polynomial1 == polynomial2
bool equal(int coefficient1[], int exponent1[], int size1,
	int coefficient2[], int exponent2[], int size2)
{
	if (size1 == size2) {
		for (int i = size1 - 1; i >= 0; i--) {
			if (coefficient1[i] == coefficient2[i] && exponent1[i] == exponent2[i]) {
				return true;
			}
			else {
				return false;
			}

		}
	}
	else {
		return false;
	}
}

// polynomial1 = -polynomial2
void minus(int coefficient1[], int exponent1[], int& size1,
	int coefficient2[], int exponent2[], int size2)
{
	size1 = size2;
	for (int i = 0; i < size1; i++)
	{
		coefficient1[i] = -coefficient2[i];
		exponent1[i] = exponent2[i];
	}
}

// addend += adder
void addition(int addendCoef[], int addendExpon[], int& addendSize,
	int adderCoef[], int adderExpon[], int adderSize)
{
	int sumCoef[arraySize] = {};
	int sumExpon[arraySize] = {};
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < addendSize && j < adderSize) {
		if (addendExpon[i] > adderExpon[j]) {
			sumCoef[k] = addendCoef[i];
			sumExpon[k] = addendExpon[i];
			i++;
			k++;
		}
		if (addendExpon[i] < adderExpon[j]) {
			sumCoef[k] = adderCoef[j];
			sumExpon[k] = adderExpon[j];
			j++;
			k++;
		}
		if (addendExpon[i] == adderExpon[j]) {
			if (adderCoef[j] + addendCoef[i] != 0) {
				sumCoef[k] = adderCoef[j] + addendCoef[i];
				sumExpon[k] = adderExpon[j];
				k++;
			}
			i++;
			j++;
			
		}
	}

	while (i < addendSize)
	{
		sumCoef[k] = addendCoef[i];
		sumExpon[k] = addendExpon[i];
		i++;
		k++;

	}

	while (j < adderSize)
	{

		sumCoef[k] = adderCoef[j];
		sumExpon[k] = adderExpon[j];
		j++;
		k++;

	}

	addendSize = k; 
	while (k >= 0) { 
		addendCoef[k] = sumCoef[k]; 
		addendExpon[k] = sumExpon[k];
		k--;
	}
}

// minuend -= subtrahend
void subtraction(int minuendCoef[], int minuendExpon[], int& minuendSize,
	int subtrahendCoef[], int subtrahendExpon[], int subtrahendSize)
{
	// buffer = 0
	int bufferCoef[arraySize] = {};
	int bufferExpon[arraySize] = {};
	int bufferSize = 0;

	// buffer = -subtrahend
	minus(bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize);

	// minuend = minuend + buffer = minuend - subtrahend
	addition(minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize);

	if (minuendSize > 0 && minuendCoef[0] == 0)
		cout << "Leading zeroes in minuend not allowed1!\n";
}

// product = multiplicand * multiplier
void multiplication(int multiplicandCoef[], int multiplicandExpon[], int multiplicandSize,
	int multiplierCoef[], int multiplierExpon[], int multiplierSize,
	int productCoef[], int productExpon[], int& productSize)
{
	// product = 0;
	productSize = 0;

	int bufferCoef[arraySize] = {};
	int bufferExpon[arraySize] = {};
	int bufferSize = multiplicandSize;
	if (multiplicandSize != 0 && multiplierSize != 0) {
		for (int i = 0; i <= multiplierSize - 1; i++) {
			for (int j = 0; j <= multiplicandSize - 1; j++) {
				bufferCoef[j] = multiplicandCoef[j] * multiplierCoef[i];
				bufferExpon[j] = multiplicandExpon[j] + multiplierExpon[i];

			}
			addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
		}
	}


	if (productSize > 0 && productCoef[0] == 0)
		cout << "Leading zeroes in product not allowed2!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(int dividendCoef[], int dividendExpon[], int dividendSize,
	int divisorCoef[], int divisorExpon[], int divisorSize,
	int quotientCoef[], int quotientExpon[], int& quotientSize,
	int remainderCoef[], int remainderExpon[], int& remainderSize)
{
	// remainder = dividend
	remainderSize = dividendSize;
	for (int i = 0; i < remainderSize; i++)
	{
		remainderCoef[i] = dividendCoef[i];
		remainderExpon[i] = dividendExpon[i];
	}

	int monomialCoef[1] = {};
	int monomialExpon[1] = {};
	int monomialSize = 1;
	int bufferCoef[arraySize] = {};
	int bufferExpon[arraySize] = {};
	int bufferSize = dividendSize;
	quotientSize = 0;
	while (remainderSize != 0 && remainderExpon[0] >= divisorExpon[0])
	{
		quotientCoef[quotientSize] = remainderCoef[0] / divisorCoef[0];
		quotientExpon[quotientSize] = remainderExpon[0] - divisorExpon[0];
		monomialCoef[0] = quotientCoef[quotientSize];
		monomialExpon[0] = quotientExpon[quotientSize];
		multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, monomialSize, bufferCoef, bufferExpon, bufferSize);
		subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
		quotientSize++;
	}

	if (quotientSize > 0 && quotientCoef[0] == 0)
		cout << "Leading zeroes in quotient not allowed3!\n";

	if (remainderSize > 0 && remainderCoef[0] == 0)
		cout << "Leading zeroes in remainder not allowed4!\n";
}