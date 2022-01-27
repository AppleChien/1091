#include <iostream>
#include <iomanip>
#include <fstream>
#include<string>
using namespace::std;

int apple;//設定apple是為了執行不要重複執行(超爛的方法)

struct MemberRecord
{
	char email[40];
	char password[24];
	char IDNumber[12];
	char name[12];
	char phone[12];
};

struct Movie
{
	int movieCode;
	int prices[4]; // prices[0]:adult, prices[1]:concession, prices[2]:disability, prices[3]:elderly
	bool dates[9]; // dates[i] is true if and only if the movie is available on i-th date
	bool sessionTimes[17]; // sessionTimes[i] is true if and only if the movie is available on i-th session
	bool occupiedSeats[9][17][8][12]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

struct BookingInfo
{
	char email[40];
	int movieCode;
	int dateCode;
	int sessionTimeCode;
	int numTickets[4]; // numTickets[0]: the number of adult tickets,
						 // numTickets[1]: the number of concession tickets,
						 // numTickets[2]: the number of disability tickets,
						 // numTickets[3]: the number of elderly tickets
	char seletedSeats[24][4]; // seleted seats for the user with the specified email
};

char hours[17][8] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
						  "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00", "01:00" };

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers);
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings);
void loadMovies(Movie movies[], int& numMovies);
void loadMovieNames(char movieNames[][60], int numMovies);
void loadAvailableDates(char availableDates[][12], int& numDates);

int inputAnInteger(int begin, int end);
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
	BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates);
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber);
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
	int numMovies, char availableDates[][12], int numDates, char email[]);
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]);

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
	char availableDates[][12], int numDates);
void display(Movie movies[], BookingInfo bookingHistory);
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
	char movieNames[][60], char availableDates[][12], char email[]);

void newMember(MemberRecord memberDetails[], int& numMembers);
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers);
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers);

void saveMemberInfo(MemberRecord memberDetails[], int numMembers);
void saveMovies(Movie movies[], int numMovies);
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings);

int main()
{
	MemberRecord memberDetails[100] = {};
	int numMembers = 0;
	loadMemberInfo(memberDetails, numMembers);

	BookingInfo bookingHistories[1000] = {};
	int numBookings = 0;
	loadBookingHistories(bookingHistories, numBookings);

	Movie movies[30] = {};
	int numMovies = 0;
	loadMovies(movies, numMovies);

	char movieNames[30][60] = {};
	loadMovieNames(movieNames, numMovies);

	char availableDates[10][12];
	int numDates = 0;
	loadAvailableDates(availableDates, numDates);

	cout << "Welcome to Vieshow Cinemas Taipei QSquare system\n";

	int choice = 0;

	while (true)
	{
		cout << "\n1. Sign In\n";
		cout << "2. New Member\n";
		cout << "3. End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			signIn(memberDetails, numMembers, movies, movieNames, numMovies,
				bookingHistories, numBookings, availableDates, numDates);
			break;

		case 2:
			newMember(memberDetails, numMembers);
			break;

		case 3:
			saveMemberInfo(memberDetails, numMembers);
			saveMovies(movies, numMovies);
			saveBookingHistories(bookingHistories, numBookings);
			cout << "Thank you...\n\n";
			system("pause");
			return 0;

		default:
			cout << "Input Error!\n\n";
			break;
		}
	}

	system("pause");
}

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers)
{
	ifstream inMemberInfoFile;

	inMemberInfoFile.open("Member Info.dat", ios::binary);

	if (!inMemberInfoFile){
		cerr << "False to open MemberInfo" << endl;
		exit(1);
	}

	while (!inMemberInfoFile.eof())
	{
		inMemberInfoFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(MemberRecord));

		numMembers++;
	}
	numMembers--;

	inMemberInfoFile.close();
}

void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings)
{
	ifstream inBookingHistoriesFile;

	inBookingHistoriesFile.open("Booking Histories.dat", ios::binary);

	if (!inBookingHistoriesFile){
		cerr << "False to open BookingHistories" << endl;
		exit(1);
	}

	while (!inBookingHistoriesFile.eof())
	{
		inBookingHistoriesFile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(BookingInfo));

		numBookings++;
	}
	numBookings--;

	inBookingHistoriesFile.close();
}

void loadMovies(Movie movies[], int& numMovies)
{
	ifstream inMoviesFile;

	inMoviesFile.open("Movies.dat", ios::binary);

	if (!inMoviesFile){
		cerr << "False to open Movies" << endl;
		exit(1);
	}

	while (!inMoviesFile.eof())
	{
		inMoviesFile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(Movie));

		numMovies++;
	}
	numMovies--;

	inMoviesFile.close();
}

void loadMovieNames(char movieNames[][60], int numMovies)
{
	ifstream inMovieNamesFile;

	inMovieNamesFile.open("Movie Names.txt", ios::in);

	if (!inMovieNamesFile){
		cerr << "False to open MovieNamesInfo" << endl;
		exit(1);
	}

	int i = 0;
	while (!inMovieNamesFile.eof())
	{
		inMovieNamesFile.getline(movieNames[i], 60);
		i++;//這裡不能用numMovies++
	}
	i--;

	inMovieNamesFile.close();
}

void loadAvailableDates(char availableDates[][12], int& numDates)
{
	ifstream inAvailableDatesFile;

	inAvailableDatesFile.open("Available Dates.txt", ios::in);

	if (!inAvailableDatesFile){
		cerr << "False to open AvailableDates" << endl;
		exit(1);
	}

	while (!inAvailableDatesFile.eof())
	{
		inAvailableDatesFile.getline(availableDates[numDates], 12);
		numDates++;
	}
	numDates--;

	inAvailableDatesFile.close();
}

int inputAnInteger(int begin, int end)
{
	char string[10];
	if (apple == 1)//cin完後getline前要ignore
		cin.ignore();
	cin.getline(string, 10, '\n');//getline:就算有空白也會判斷成字串
	apple = 0;//歸零

	if (strlen(string) == 0)//根本沒輸入東西
		return -1;

	for (unsigned int i = 0; i < strlen(string); i++){//判斷是否為數字:非英文字母而且沒有空白
		if (string[i] < '0' || string[i] > '9'){
			return -1;
		}
	}

	int import = atoi(string);//atoi:string轉成int

	if (import >= begin && import <= end)
		return import;
	else
		return -1;
}

void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
	BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates)
{
	int recordNumber = 1;//當前的那個人

	while (true)
	{
		cout << "Enter email address : ";
		cin >> memberDetails[numMembers].email;
		apple = 1;

		cout << "Enter password : ";
		cin >> memberDetails[numMembers].password;
		apple = 1;

		if (!(illegal(memberDetails[numMembers].email, memberDetails[numMembers].password, memberDetails, numMembers, recordNumber)))
			break;   //如果輸入正確帳密 執行下面的while
		else
			cout << "\nSorry, unrecognized email or password.\n\n";//輸入之帳密不存在 再執行一次while
	}

	while (true)//登入進來了
	{
		cout << "\n1. Account Information\n";
		cout << "2. Buy Tickets\n";
		cout << "3. My Bookings\n";
		cout << "4. Sign Out\n\n";

		int choice;
		do cout << "Enter your choice(1~4):";
		while ((choice = inputAnInteger(1, 4)) == -1);
		cout << endl;

		switch (choice)//choice==false會重複執行while
		{
		case 1://Account Information
			accountInfor(memberDetails, numMembers, recordNumber);
			break;

		case 2://Buy Ticket
			buyTickets(bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, memberDetails[numMembers].email);
			break;

		case 3:// My Bookings
			displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, memberDetails[numMembers].email);
			break;

		case 4://Sign Out
			return;

		default://條件都沒有符合以上數值
			cout << "Input Error!\n\n";
			break;
		}
	}
}

bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber)
{
	for (int i = 0; i < numMembers; i++){//檢查email與password符不符合
		if ((strcmp(memberDetails[i].email, email) == 0) && (strcmp(memberDetails[i].password, password) == 0)){//email與password正確
			recordNumber = i;
			return false;
		}
	}
	return true;//這個放在for裡面會有問題
}

void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber)
{
	cout << "1. Name: " << memberDetails[recordNumber].name << endl;
	cout << "2. Email Address: " << memberDetails[recordNumber].email << endl;
	cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
	cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
	cout << "5. Password: " << memberDetails[recordNumber].password << endl << endl;

	cout << "Which one do you want to modify (0 – not modify)?" << endl;

	while (true)
	{
		int choice;
		choice = inputAnInteger(0, 5);
		switch (choice)
		{
		case 0:
			return;

		case 1://Name
			cout << "Enter correct data: ";
			cin >> memberDetails[recordNumber].name;
			apple = 1;
			cout << "\nSuccessful!\n";
			return;

		case 2://Email Address
			cout << "Enter correct data: ";
			cin >> memberDetails[recordNumber].email;
			apple = 1;
			cout << "\nSuccessful!\n";
			return;

		case 3://Phone Number
			cout << "Enter correct data: ";
			cin >> memberDetails[recordNumber].phone;
			apple = 1;
			cout << "\nSuccessful!\n";
			return;

		case 4://ID Number
			cout << "Enter correct data: ";
			cin >> memberDetails[recordNumber].IDNumber;
			apple = 1;
			cout << "\nSuccessful!\n";
			return;

		case 5://Password
			cout << "Enter correct data: ";
			cin >> memberDetails[recordNumber].password;
			apple = 1;
			cout << "\nSuccessful!\n";
			return;

		default:
			cout << "Input Error!Please try again: \n\n";
			break;
		}
	}
}

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
	int numMovies, char availableDates[][12], int numDates, char email[])
{
	for (int i = 0; i < sizeof(email); i++){
		bookingHistories[numBookings].email[i] = email[i];
	}

	displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates);//灰色那段

	while (true)//movie code
	{
		cout << "\nEnter movie code (0 - 11): ";
		int choice;
		choice = inputAnInteger(0, 11);
		if (choice != (-1)){
			bookingHistories[numBookings].movieCode = choice;
			break;
		}
	}

	while (true)//date code
	{
		cout << "\nEnter date code (0 - 8): ";
		int choice;
		choice = inputAnInteger(0, 8);
		if (choice != (-1)){
			if (movies[bookingHistories[numBookings].movieCode].dates[choice] == 1){
				//檢查有沒有那一天(沒有是0 有是1)
				bookingHistories[numBookings].dateCode = choice;
				break;
			}
		}
	}

	while (true)//session time code
	{
		cout << "\nEnter session time code (0 - 16): ";
		int choice;
		choice = inputAnInteger(0, 16);
		if (choice != (-1)){
			if (movies[bookingHistories[numBookings].movieCode].sessionTimes[choice] == 1){
				//檢查是否存在該場次(沒有是0 有是1)
				bookingHistories[numBookings].sessionTimeCode = choice;
				break;
			}
		}
	}

	cout << "Movie: " << movieNames[bookingHistories[numBookings].movieCode] << endl;
	cout << "Date: " << availableDates[bookingHistories[numBookings].dateCode] << endl;
	cout << "Show Time: " << hours[bookingHistories[numBookings].sessionTimeCode] << endl;

	cout << "Price: Adult-" << movies[bookingHistories[numBookings].movieCode].prices[0]
		<< ", Concession-" << movies[bookingHistories[numBookings].movieCode].prices[1]
		<< ", Disability-" << movies[bookingHistories[numBookings].movieCode].prices[2]
		<< ", Elderly-" << movies[bookingHistories[numBookings].movieCode].prices[3] << endl;

	bookingHistories[numBookings].numTickets[0] = 0;//Adult
	bookingHistories[numBookings].numTickets[1] = 0;// Concession
	bookingHistories[numBookings].numTickets[2] = 0;//Disability
	bookingHistories[numBookings].numTickets[3] = 0;//Elderly

	while ((bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] + bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3]) == 0)
	{//如果根本沒買票
		while (true)//Adult
		{
			cout << "\nEnter the number of adult tickets (0 - 6): ";
			int choice;
			choice = inputAnInteger(0, 6);
			if (choice != (-1)){
				bookingHistories[numBookings].numTickets[0] = choice;
				break;
			}
		}

		while (true)// Concession
		{
			cout << "\nEnter the number of concession tickets (0 - 6): ";
			int choice;
			choice = inputAnInteger(0, 6);
			if (choice != (-1)){
				bookingHistories[numBookings].numTickets[1] = choice;
				break;
			}
		}

		while (true)//Disability
		{
			cout << "\nEnter the number of disability tickets (0 - 6): ";
			int choice;
			choice = inputAnInteger(0, 6);
			if (choice != (-1)){
				bookingHistories[numBookings].numTickets[2] = choice;
				break;
			}
		}

		while (true)//Elderly
		{
			cout << "\nEnter the number of elderly tickets (0 - 6): ";
			int choice;
			choice = inputAnInteger(0, 6);
			if (choice != (-1)){
				bookingHistories[numBookings].numTickets[3] = choice;
				break;
			}
		}
	}

	display(movies, bookingHistories[numBookings]);//黃色那段
	selectSeats(bookingHistories, numBookings, movies);//綠色那段
	numBookings++;//訂完票
}

void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[])
{
	cout << "  A B C D E F G H I J K L" << endl;
	for (int j = 0; j < 8; j++){
		cout << j << " ";
		for (int i = 0; i < 12; i++){
			cout << movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][j][i] << " ";
		}
		cout << endl;
	}

	int total_tickets = bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1]
		+ bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3];

	cout << "\nSelect " << total_tickets << " seats (e.g. 0A):" << endl;

	for (int a = 0;a < total_tickets;a++) {
		cout << "?";

		cin >> bookingHistories[numBookings].seletedSeats[a];


		apple = 1;
		int x = bookingHistories[numBookings].seletedSeats[a][0] - 48, y = bookingHistories[numBookings].seletedSeats[a][1] - 65;
		//0的ASCII是48 A的ASCII是65
		if ((x < 0 || x > 7) || (y < 0 || y > 11)){
			cout << "\nInput error please try again!\n";
			return;
		}

		else if (movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode]
			[bookingHistories[numBookings].sessionTimeCode][x][y] == false){//位置沒有人
			movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode]
				[bookingHistories[numBookings].sessionTimeCode][x][y] = true;
		}
		else if (movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode]
			[bookingHistories[numBookings].sessionTimeCode][x][y] == true){//位置已有人
			cout << "\nThis seat bas been occupied. Please select another seat.\n";
			a--;
			continue;
		}
	}

	cout << "\nSuccessful!" << endl;
}

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
	char availableDates[][12], int numDates)
{
	for (int i = 0; i < numMovies; i++){

		cout << i << ". Movie: " << movieNames[i] << endl;

		cout << "   Date:  ";
		for (int j = 0; j < numDates; j++){
			if (movies[i].dates[j] == 1){//如果那天有電影
				cout << j << ". " << availableDates[j] << ", ";
			}
		}
		cout << endl;

		cout << "   Session Time:  ";
		for (int a = 0; a < 17; a++){
			if (movies[i].sessionTimes[a] == 1){//如果那天有該場次
				cout << a << ". " << hours[a] << ", ";
			}
		}
		cout << endl;
	}
}

void display(Movie movies[], BookingInfo bookingHistory)
{
	int total = 0;
	cout << "\n             No. of Tickets  Price  Subtotal\n";

	if (bookingHistory.numTickets[0] != 0){//Adult
		cout << "Adult ticket              " << bookingHistory.numTickets[0] << "    " << movies[bookingHistory.movieCode].prices[0] << "    " << bookingHistory.numTickets[0] * movies[bookingHistory.movieCode].prices[0] << endl;
		total += bookingHistory.numTickets[0] * movies[bookingHistory.movieCode].prices[0];
	}

	if (bookingHistory.numTickets[1] != 0){//Concession
		cout << "Concession ticket         " << bookingHistory.numTickets[1] << "    " << movies[bookingHistory.movieCode].prices[1] << "    " << bookingHistory.numTickets[1] * movies[bookingHistory.movieCode].prices[1] << endl;
		total += bookingHistory.numTickets[1] * movies[bookingHistory.movieCode].prices[1];
	}

	if (bookingHistory.numTickets[2] != 0){//Disability
		cout << "Disability ticket         " << bookingHistory.numTickets[2] << "    " << movies[bookingHistory.movieCode].prices[2] << "    " << bookingHistory.numTickets[2] * movies[bookingHistory.movieCode].prices[2] << endl;
		total += bookingHistory.numTickets[2] * movies[bookingHistory.movieCode].prices[2];
	}

	if (bookingHistory.numTickets[3] != 0){//Elderly
		cout << "Elderly ticket            " << bookingHistory.numTickets[3] << "    " << movies[bookingHistory.movieCode].prices[3] << "    " << bookingHistory.numTickets[3] * movies[bookingHistory.movieCode].prices[3] << endl;
		total += bookingHistory.numTickets[3] * movies[bookingHistory.movieCode].prices[3];
	}

	cout << "\nTotal Amount For Tickets: " << total << "\n\n";
}

void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
	char movieNames[][60], char availableDates[][12], char email[])
{
	int judge = 0;
	int member_location = 0;
	int count_tickets = 0;
	for (int i = 0; i < numBookings; i++){
		if (strcmp(email, bookingHistories[i].email) == 0){//如果訂票存在
			judge = 1;
			member_location = i;
			break;
		}
	}

	if (judge == 0){//如果沒有訂票紀錄
		cout << "\nNo bookings!\n" << endl;
		return;
	}

	count_tickets = bookingHistories[member_location].numTickets[0] + bookingHistories[member_location].numTickets[1] +
		bookingHistories[member_location].numTickets[2] + bookingHistories[member_location].numTickets[3];

	cout << "Booking History:\n\n";
	cout << "Movie: " << movieNames[bookingHistories[member_location].movieCode] << endl;
	cout << "Date: " << availableDates[bookingHistories[member_location].dateCode] << endl;
	cout << "Show Time: " << hours[bookingHistories[member_location].sessionTimeCode] << endl;
	cout << "Seats: ";
	for (int a = 0;a < count_tickets;a++) {
		cout << bookingHistories[member_location].seletedSeats[a] << " ";//印出所有選的位置
	}
	display(movies, bookingHistories[member_location]);//黃色那段
}

void newMember(MemberRecord memberDetails[], int& numMembers)
{
	cout << "Enter your ID number: ";
	cin >> memberDetails[numMembers].IDNumber;
	apple = 1;
	if (existingID(memberDetails[numMembers].IDNumber, memberDetails, numMembers)){
		cout << "\nAn account already exists with the ID number!\n" << endl;
		return;
	}

	cout << "Enter your name:";
	cin >> memberDetails[numMembers].name;
	apple = 1;

	while (true)
	{
		cout << "Enter an email address: ";
		cin >> memberDetails[numMembers].email;
		apple = 1;
		if (existingEmail(memberDetails[numMembers].email, memberDetails, numMembers)){
			cout << "\nAn account already exists with the email!\n\n";
		}
		else
			break;
	}

	cout << "Enter a password: ";
	cin >> memberDetails[numMembers].password;
	apple = 1;

	cout << "Enter your phone number: ";
	cin >> memberDetails[numMembers].phone;
	apple = 1;

	numMembers++;//成功存取=>成員數加一
	cout << "\nSuccessful!\n" << endl;
}

bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers)
{
	for (int i = 0; i < numMembers; i++){
		if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0)
			return true;
	}
	return false;
}

bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers)
{
	for (int i = 0; i < numMembers; i++){
		if (strcmp(newEmail, memberDetails[i].email) == 0)
			return true;
	}
	return false;
}

void saveMemberInfo(MemberRecord memberDetails[], int numMembers)
{
	ofstream outMemberFile;

	outMemberFile.open("Member Info.dat", ios::binary);

	if (!outMemberFile){
		cout << "File could not be opened saveMemberInfo" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numMembers; i++){
		outMemberFile.write(reinterpret_cast<char*>(&memberDetails[i]), sizeof(memberDetails[i]));
	}
	outMemberFile.close();
}

void saveMovies(Movie movies[], int numMovies)
{
	ofstream outMoviesFile;

	outMoviesFile.open("Movies.dat", ios::binary);

	if (!outMoviesFile){
		cout << "File could not be opened saveMovies" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numMovies; i++){
		outMoviesFile.write(reinterpret_cast<char*>(&movies[i]), sizeof(movies[i]));
	}
	outMoviesFile.close();
}

void saveBookingHistories(BookingInfo bookingHistories[], int numBookings)
{
	ofstream outBookingFile;

	outBookingFile.open("Booking Histories.dat", ios::binary);

	if (!outBookingFile){
		cout << "File could not be opened saveBookingHistories" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < numBookings; i++){
		outBookingFile.write(reinterpret_cast<char*>(&bookingHistories[i]), sizeof(bookingHistories[i]));
	}
	outBookingFile.close();
}