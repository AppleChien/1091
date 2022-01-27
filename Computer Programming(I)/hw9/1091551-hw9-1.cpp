#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(char(*identifiers)[32], int numIdentifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char(*identifiers)[32], int pos);

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
	char(*program)[100] = new char[500][100];
	int numLines = 0;

	// reads in a C++ program from a cpp file, and put it to the array program
	load(program, numLines);

	char(*identifiers)[32] = new char[500][32];
	int numIdentifiers = 0;

	for (int i = 0; i < numLines; i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		if (strcmp(program[i], "") != 0)
			extractIdentifiers(program[i], identifiers, numIdentifiers);
		// extracts all identifiers from program[ i ], and put them into the array identifiers
	}

	// stores all non-keyword strings in the array identifiers into a text file
	store(identifiers, numIdentifiers);

	system("pause");
}

void load(char(*program)[100], int& numLines)
{
	ifstream inClientFile("test.cpp", ios::in);
	if (!inClientFile) {
		cout << "False to open" << endl;
		exit(1);
	}
	int i = 0;
	while (inClientFile.getline(program[i], 100,'\n'))
	{
		numLines++;
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
	for (begin = 0; sourceLine[begin] != '\0'; begin++)//找第一個雙引號
		if (sourceLine[begin] == '\"')
			break;
	for (j = length - 1; j > begin; j--)//找第二個雙引號
		if (sourceLine[j] == '\"')
			break;

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
			if (sourceLine[begin] == '\'')//找單引號
				break;
		if (sourceLine[begin] == '\0')//找到最後還是沒有出現單引號
			return;
		if (begin + 2 >= length || sourceLine[begin + 2] != '\'') {

			cout << "\' does not match!\n";
			return;
		}
		for (int i = begin; i < begin + 3; i++)//字元內容填入空格
			sourceLine[i] = ' ';
	}
}

void extractIdentifiers(char line[], char identifiers[][32], int& numIdentifiers)
{//因為是二維陣列不會爆掉=>可以先存再刪
	int count = 0;
	for (int i = 0; line[i] != '\0'; i++) {

		if (line[i] == '_' || line[i] != ' ' && isalnum(line[i])) {
			//如果line[i]是底線或是字元或是數字 就存入identifiers[][]
			identifiers[numIdentifiers][count] = line[i];
			count++;
		}
		else {
			identifiers[numIdentifiers][count] = '\0';//在最後加上'\0'
			if (duplicate(identifiers, numIdentifiers) || keyword(identifiers[numIdentifiers])) {
				//如果重複或是等於keywords 就用空白字元刪除
				for (int j = 0; identifiers[numIdentifiers][j] != '\0'; j++)//還沒讀到'\0'就繼續j++
					identifiers[numIdentifiers][j] = ' ';
			}
			else {
				//不重複也不是keywords,numIdentifiers就++
				numIdentifiers++;
			}
			count = 0;
		}
	}

}
//put the array identifiers into "identifiers.txt
//compare with ketwords[][20]
//store non-keywors and no repeat
void store(char(*identifiers)[32], int numIdentifiers)
{
	ofstream outClientFile("identifiers1.txt", ios::out);

	if (!outClientFile) {

		cerr << "File could not be opened" << endl;
		exit(1);
	}
	else {
		for (int i = 0; i < numIdentifiers; i++) {
			if (isalpha(identifiers[i][0])) {//判斷第0位是不是英文字母
				outClientFile << identifiers[i] << endl;
			}
		}
	}
}

bool keyword(char str[])//str[]是否跟keyword相同
{
	const int numKeywords = sizeof(keywords) / 20;//62*20
	for (int i = 0; i < numKeywords; i++)
		if (strcmp(keywords[i], str) == 0)
			return true;
	//strcmp:比較兩字串 若返回值為0則兩字串相同
	return false;
}

bool duplicate(char(*identifiers)[32], int pos)
{
	for (int i = 0; i < pos; i++)
		if (strcmp(identifiers[i], identifiers[pos]) == 0)
			return true;
	//strcmp:比較兩字串 若返回值為0則兩字串相同
	return false;
}