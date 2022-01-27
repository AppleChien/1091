#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct Movie
{
	int movieCode;
	char dates[12] = "";
	int numSessions;
	char sessionTimes[11][8] = { "" };
};

void loadMovieNames(char movieNames[][40], int& numMovies);
void loadMovies(Movie movies[], int& numRecords);
void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords);
int inputAnInteger(int begin, int end);

int main()
{
	char movieNames[30][40];
	int numMovies = 0;
	loadMovieNames(movieNames, numMovies);

	Movie movies[110];
	int numRecords = 0;
	loadMovies(movies, numRecords);

	buyTickets(movieNames, movies, numMovies, numRecords);

	system("pause");
}

void loadMovieNames(char movieNames[][40], int& numMovies)
{
	ifstream inFile("Movie Names.txt", ios::in);

	if (!inFile) {
		cerr << "File could not be opened";
		exit(1);
	}
	while (!inFile.eof()) {
		inFile.getline(movieNames[numMovies], 200);
		if (movieNames[numMovies][0] != '\0')
			cout << numMovies << ". " << movieNames[numMovies] << endl;
		numMovies++;
	}
	inFile.seekg(0, ios::beg);//從開頭的byte開始讀檔
	inFile.close();
}


void loadMovies(Movie movies[], int& numRecords)
{
	ifstream inFile("Session Times.dat", ios::in | ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	while (!inFile.eof())
	{
		inFile.read(reinterpret_cast<char*>(&movies[numRecords]), sizeof(Movie));
		numRecords++;
	}
	numRecords--;
	inFile.seekg(0, ios::beg);//從開頭的byte開始讀檔
	inFile.close();
}

void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords)
{//二元檔:要考慮真正的位置
	int last_choice_date_time = 0;//被選中的電影最後日期的場次真正位置(從頭開始數)
	int choice_date_quantity = 0;//被選中電影日期的session數量
	int choice;//選擇電影
	int choice_date;//選擇日期
	int date_now;//日期選好的那天真正的位置(從頭開始數)
	int choice_date_time;//選擇時間
//第一次:選擇電影
	cout << "Enter movie code(0 - 26): ";
	choice = inputAnInteger(0, 26);
	cout << endl;
	while (choice == -1)
	{
		cout << "Enter movie code(0 - 26): ";
		choice = inputAnInteger(0, 26);
		cout << endl;
	}

	int a = 0;
	for (int j = 0; j < numRecords; j++)//列出選的電影的日期
	{
		if (choice == movies[j].movieCode)
		{
			cout << a << ". " << movies[j].dates << endl;
			a++;
			choice_date_quantity++;
			last_choice_date_time = j;
		}
	}
//第二次:選擇日期
	cout << "Enter date code(0 - " << choice_date_quantity - 1 << "): ";
	choice_date = inputAnInteger(0, choice_date_quantity - 1);
	cout << endl;
	while (choice_date == -1)
	{
		cout << "Enter date code(0 - " << choice_date_quantity - 1 << "): ";
		choice_date = inputAnInteger(0, choice_date_quantity - 1);
		cout << endl;
	}

	date_now = last_choice_date_time - (choice_date_quantity - choice_date - 1);//當日時刻表真正的位置
	for (int a = 0; a < movies[date_now].numSessions; a++)
	{
		cout << a << ". " << movies[date_now].sessionTimes[a] << endl;
	}
//第三次:選擇時間
	cout << "Enter session time code (0 - " << movies[date_now].numSessions - 1 << "):";
	choice_date_time = inputAnInteger(0, movies[date_now].numSessions - 1);
	cout << endl;
	while (choice_date_time == -1)
	{
		cout << "Enter session time code (0 - " << movies[date_now].numSessions - 1 << "):";
		choice_date_time = inputAnInteger(0, movies[date_now].numSessions - 1);
		cout << endl;
	}
	//輸出最後選擇結果
	cout << movieNames[choice] << endl;
	cout << movies[date_now].dates << " " << movies[date_now].sessionTimes[choice_date_time] << endl;
}

int inputAnInteger(int begin, int end)
{
	char a[80];
	cin.getline(a, 80, '\n');//getline:就算有空白也會判斷成字串
	if (strlen(a) == 0)//根本沒輸入東西
		return -1;
	for (unsigned int i = 0;i < strlen(a);i++) {//判斷是否為數字:非英文字母而且沒有空白
		if (a[i] < '0' || a[i] > '9')
			return -1;
	}
	int number = atoi(a);//atoi:string轉成int
	if (number >= begin && number <= end)
		return number;
	else
		return -1;
}