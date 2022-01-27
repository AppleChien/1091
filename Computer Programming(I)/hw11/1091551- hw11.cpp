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
	inFile.seekg(0, ios::beg);//�q�}�Y��byte�}�lŪ��
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
	inFile.seekg(0, ios::beg);//�q�}�Y��byte�}�lŪ��
	inFile.close();
}

void buyTickets(char movieNames[][40], Movie movies[], int numMovies, int numRecords)
{//�G����:�n�Ҽ{�u������m
	int last_choice_date_time = 0;//�Q�襤���q�v�̫����������u����m(�q�Y�}�l��)
	int choice_date_quantity = 0;//�Q�襤�q�v�����session�ƶq
	int choice;//��ܹq�v
	int choice_date;//��ܤ��
	int date_now;//�����n�����ѯu������m(�q�Y�}�l��)
	int choice_date_time;//��ܮɶ�
//�Ĥ@��:��ܹq�v
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
	for (int j = 0; j < numRecords; j++)//�C�X�諸�q�v�����
	{
		if (choice == movies[j].movieCode)
		{
			cout << a << ". " << movies[j].dates << endl;
			a++;
			choice_date_quantity++;
			last_choice_date_time = j;
		}
	}
//�ĤG��:��ܤ��
	cout << "Enter date code(0 - " << choice_date_quantity - 1 << "): ";
	choice_date = inputAnInteger(0, choice_date_quantity - 1);
	cout << endl;
	while (choice_date == -1)
	{
		cout << "Enter date code(0 - " << choice_date_quantity - 1 << "): ";
		choice_date = inputAnInteger(0, choice_date_quantity - 1);
		cout << endl;
	}

	date_now = last_choice_date_time - (choice_date_quantity - choice_date - 1);//���ɨ��u������m
	for (int a = 0; a < movies[date_now].numSessions; a++)
	{
		cout << a << ". " << movies[date_now].sessionTimes[a] << endl;
	}
//�ĤT��:��ܮɶ�
	cout << "Enter session time code (0 - " << movies[date_now].numSessions - 1 << "):";
	choice_date_time = inputAnInteger(0, movies[date_now].numSessions - 1);
	cout << endl;
	while (choice_date_time == -1)
	{
		cout << "Enter session time code (0 - " << movies[date_now].numSessions - 1 << "):";
		choice_date_time = inputAnInteger(0, movies[date_now].numSessions - 1);
		cout << endl;
	}
	//��X�̫��ܵ��G
	cout << movieNames[choice] << endl;
	cout << movies[date_now].dates << " " << movies[date_now].sessionTimes[choice_date_time] << endl;
}

int inputAnInteger(int begin, int end)
{
	char a[80];
	cin.getline(a, 80, '\n');//getline:�N�⦳�ťդ]�|�P�_���r��
	if (strlen(a) == 0)//�ڥ��S��J�F��
		return -1;
	for (unsigned int i = 0;i < strlen(a);i++) {//�P�_�O�_���Ʀr:�D�^��r���ӥB�S���ť�
		if (a[i] < '0' || a[i] > '9')
			return -1;
	}
	int number = atoi(a);//atoi:string�নint
	if (number >= begin && number <= end)
		return number;
	else
		return -1;
}