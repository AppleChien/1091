#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(string& sourceLine, string* identifiers, int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
							"continue", "default", "define","do", "double",
							"else", "enum", "extern", "float", "for",
							"goto", "if", "int", "long", "register",
							"return", "short", "signed", "sizeof",
							"static", "struct", "switch", "typedef",
							"union", "unsigned", "void", "volatile",
							"while", "bool", "catch", "class",
							"const_cast", "delete", "dynamic_cast",
							"explicit", "false", "friend", "inline",
							"mutable", "namespace", "new", "operator",
							"private", "protected", "public",
							"reinterpret_cast", "static_cast", "template",
							"this", "throw", "true", "try", "typeid",
							"typename", "using", "virtual", "include" };


int main()
{
	string* program = new string[500];
	int numLines = 0;

	// reads in a C++ program from a cpp file, and put it to the array program
	load(program, numLines);

	string* identifiers = new string[500];
	string null;
	int numIdentifiers = 0;

	for (int i = 0; i < numLines; i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		if (program[i] != null)
			extractIdentifiers(program[i], identifiers, numIdentifiers);
		// extracts all identifiers from program[ i ], and put them into the array identifiers
	}

	// stores all non-keyword strings in the array identifiers into a text file
	store(identifiers, numIdentifiers);

	system("pause");
}

void load(string* program, int& numLines)
{
	ifstream inClientFile("test.cpp", ios::in);
	if (!inClientFile) {
		cout << "False to open" << endl;
		exit(1);
	}
	while (getline(inClientFile, program[numLines]))
	{
		numLines++;
	}

}

void delComment(string& sourceLine)//?R??????
{
	unsigned len = sourceLine.size();
	if (len > 1)
		for (unsigned int i = 0; i < len - 1; i++)
			if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
			{
				sourceLine.erase(i, len);
				break;
			}
}

void delStrConsts(string& sourceLine)//?R?????????r??
{
	for (int begin = 0; sourceLine[begin] != '\0'; begin++) {
		if (sourceLine[begin] == '\"')
		{
			int count = 1;
			while (sourceLine[begin + count] != '\"')
				count++;
			sourceLine.erase(begin, count);
		}
	}
}

void delCharConsts(string& sourceLine)//?R???r??
{
	size_t length = sourceLine.size();
	unsigned int begin;
	while (true)
	{
		begin = sourceLine.find('\'', 0);

		if (begin == string::npos)//?P?_?O?_??????????
			return;

		if (begin + 2 >= length || sourceLine[begin + 2] != '\'')
		{
			cout << "\' does not match!\n";
			return;
		}

		sourceLine.erase(begin, 3);
	}

}

void extractIdentifiers(string& sourceLine, string* identifiers, int& numIdentifiers)
{//?b?o???s?iidentifiers?|?z???A?]??string?O?@???}?C => ???R?A?s
	for (int i = 0; sourceLine[i] != '\0'; i++)
	{
		if (!isalnum(sourceLine[i]) && sourceLine[i] != '_')
			continue; //?p?G???O?r??or???ror???u ?N???L?M???~????
		else
		{
			for (; sourceLine[i] != ' ' && isalnum(sourceLine[i]) && sourceLine[i] != '\0' || sourceLine[i] == '_'; i++)
				identifiers[numIdentifiers] += sourceLine[i];
			if (!keyword(identifiers[numIdentifiers]) && !duplicate(identifiers, numIdentifiers) && !isdigit(identifiers[numIdentifiers][0]))
				numIdentifiers++; //???Okeyword?]?S???????]???O???r
			else
				identifiers[numIdentifiers].erase(identifiers[numIdentifiers].begin(), identifiers[numIdentifiers].end());
		}
	}
}

void store(string* identifiers, int numIdentifiers)
{
	ofstream outClientFile("identifiers2.txt", ios::out);
	if (!outClientFile) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	else {
		for (int i = 0; i < numIdentifiers; i++) {
			if (isalpha(identifiers[i][0])) {//?P?_??0???O???O?^???r??
				outClientFile << identifiers[i] << endl;
			}
		}
	}
}

bool keyword(string str)
{
	const int numKeywords = sizeof(keywords) / 20;
	for (int i = 0; i < numKeywords; i++)
		if (keywords[i] == str)
			return true;

	return false;
}

bool duplicate(string* identifiers, int pos)
{
	for (int i = 0; i < pos; i++)
		if (identifiers[i] == identifiers[pos])
			return true;

	return false;
}