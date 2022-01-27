#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< string >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers(string& sourceLine, vector< string >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< string >& identifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< string >& identifiers, int pos);

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
	vector< string > program;

	// reads in a C++ program from a cpp file, and put it to the vector program
	load(program);

	vector< string > identifiers;
	string null;

	for (size_t i = 0; i < program.size(); i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		if (program[i] != null)
			extractIdentifiers(program[i], identifiers);
		// extracts all identifiers from program[ i ], and put them into the vector identifiers
	}

	// stores all non-keyword strings in the vector identifiers into a text file
	store(identifiers);

	system("pause");
}

void load(vector< string >& program)
{
	string a;
	ifstream inClientFile("test.cpp", ifstream::in);
	if (!inClientFile) {
		cout << "False to open" << endl;
		exit(1);
	}
	while (!inClientFile.eof()) //如果還沒到最後
	{
		getline(inClientFile, a);  //將輸入的字串放到a
		program.push_back(a);   //program增加一格，裡面放a
	}

}

void delComment(string& sourceLine)//刪除註解
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

void delStrConsts(string& sourceLine)//刪除雙引號字串
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

void delCharConsts(string& sourceLine)//刪除字元
{
	size_t length = sourceLine.size();
	unsigned int begin;
	while (true)
	{
		begin = sourceLine.find('\'', 0);

		if (begin == string::npos)
			return;

		if (begin + 2 >= length || sourceLine[begin + 2] != '\'')
		{
			cout << "\' does not match!\n";
			return;
		}

		sourceLine.erase(begin, 3);
	}

}

void extractIdentifiers(string& sourceLine, vector< string >& identifiers)
{
	int begin, end, length;
	string a;
	for (int i = 0; i <= sourceLine.size() - 1; i++) {
		if ((isalpha(sourceLine[i])) || (sourceLine[i] == '_'))  //遇到是字母或_
		{
			begin = i;  //標記第一個字母出現的位置
			i++;
			while ((isalnum(sourceLine[i])) || (sourceLine[i] == '_'))  //找不是字母數字或_的位置
				i++;

			end = i;
			length = end - begin;  //這串的長度
			a.assign(sourceLine, begin, length);   //把identifier放到a
			//assign(字串,從begin開始,最多length字元)
			identifiers.push_back(a);   //把a放到identifier陣列
		}

	}
}

void store(vector< string >& identifiers)
{
	ofstream outClientFile("identifiers4.txt", ios::out);
	if (!outClientFile) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	for (int i = 0; i <= identifiers.size() - 1; i++) {
		if ((!keyword(identifiers[i])) && (!duplicate(identifiers, i))) //如果不是keyword也沒重複
			outClientFile << identifiers[i] << endl;
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

bool duplicate(vector< string >& identifiers, int pos)
{
	for (int i = 0; i < pos; i++)
		if (identifiers[i] == identifiers[pos])
			return true;

	return false;
}