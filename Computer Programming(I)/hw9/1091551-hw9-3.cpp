#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< char* >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the vector identifiers
void extractIdentifiers(char sourceLine[], vector< char* >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< char* >& identifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< char* >& identifiers, int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
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
	vector< char* > program;

	// reads in a C++ program from a cpp file, and put it to the vector program
	load(program);

	vector< char* > identifiers;
	for (size_t i = 0; i < program.size(); i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		if (strcmp(program[i], "") != 0)
			extractIdentifiers(program[i], identifiers);
		// extracts all identifiers from program[ i ], and put them into the vector identifiers
	}

	// stores all non-keyword strings in the vector identifiers into a text file
	store(identifiers);

	system("pause");
}

void load(vector< char* >& program)
{
	ifstream inClientFile("test.cpp", ifstream::in);
	char a[500][100];
	int i = 0;
	if (!inClientFile) {
		cout << "File could not be opened" << endl;
		exit(0);
	}
	while (!inClientFile.eof()) //如果還沒到最後
	{
		inClientFile.getline(a[i], 100, '\n'); //將檔案的字串輸入到a陣列中
		program.push_back(a[i]); //program增加一格指向a陣列
		i++;
	}
}

void delComment(char sourceLine[])//刪除註解
{
	for (int i = 0; sourceLine[i + 1] != '\0'; i++)
		if ((sourceLine[i] == '/' || sourceLine[i + 1] == '/'))
		{
			sourceLine[i] = '\0';
			return;
		}
}

void delStrConsts(char sourceLine[])//刪除雙引號字串
{
	int length = strlen(sourceLine);
	int begin = 0;
	int j = length - 1;
	for (begin = 0; sourceLine[begin] != '\0'; begin++) {//找第一個雙引號
		if (sourceLine[begin] == '\"')
			break;
	}
	for (j = length - 1; j > begin; j--) {//找第二個雙引號
		if (sourceLine[j] == '\"')
			break;
	}

	if (sourceLine[begin] == '\0')
		return;
	for (int i = begin; i < length; i++) {//字串內容填入空格
		sourceLine[i] = ' ';
	}

}

void delCharConsts(char sourceLine[])//刪除字元
{
	int length = strlen(sourceLine);
	int begin = -3;
	while (true)
	{
		for (begin += 3; sourceLine[begin] != '\0'; begin++)
			if (sourceLine[begin] == '\'')
				break;

		if (sourceLine[begin] == '\0')
			return;

		if (begin + 2 >= length || sourceLine[begin + 2] != '\'')
		{
			cout << "\' does not match!\n";
			return;
		}

		for (int i = begin; i < begin + 3; i++)
			sourceLine[i] = ' ';
	}

}

void extractIdentifiers(char sourceLine[], vector< char* >& identifiers)
{
	static int j = 0;   //static:即使跳出function也不怕標記的位置消失
	static char b[500][32];

	for (int i = 0; i <= strlen(sourceLine) - 1; i++)
	{
		if ((isalpha(sourceLine[i])) || (sourceLine[i] == '_'))  //開頭遇到是字母或_
		{
			int k = 0;
			b[j][k] = sourceLine[i]; //把字存到b陣列
			i++;
			k++;
			while ((isalnum(sourceLine[i])) || (sourceLine[i] == '_')) //一直找 直到不是字母或數字或_
			{
				b[j][k] = sourceLine[i]; //把字存到b陣列
				i++;
				k++;
			}
			b[j][k] = '\0';  //在最後存入\0表示這串字串結束
			identifiers.push_back(b[j]); //把identifier指向這串字
			j++;
		}
	}
}

void store(vector< char* >& identifiers)
{
	ofstream outClientFile("identifiers3.txt", ios::out);
	if (!outClientFile) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	for (int i = 0; i <= identifiers.size() - 1; i++)
		if ((!keyword(identifiers[i])) && (!duplicate(identifiers, i))) //如果不是keyword也沒重複
			outClientFile << identifiers[i] << endl;   //輸出到檔案
}

bool keyword(char str[])
{
	const int numKeywords = sizeof(keywords) / 20;
	for (int i = 0; i < numKeywords; i++)
		if (strcmp(keywords[i], str) == 0)
			return true;
	//strcmp:比較兩字串 若返回值為0則兩字串相同
	return false;
}

bool duplicate(vector< char* >& identifiers, int pos)
{
	for (int i = 0; i < pos; i++)
		if (strcmp(identifiers[i], identifiers[pos]) == 0)
			return true;
	//strcmp:比較兩字串 若返回值為0則兩字串相同
	return false;
}