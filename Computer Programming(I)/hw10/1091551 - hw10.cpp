#include <iostream>
#include <fstream>
using namespace::std;

struct Member
{
	char email[40];
	char password[24];
	char IDNumber[12];
	char name[12];
	char phone[12];
};

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers);

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger(int begin, int end);

void login(Member memberDetails[], int numMembers);

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber);

void accountInfor(Member memberDetails[], int numMembers, int recordNumber);

void newMember(Member memberDetails[], int& numMembers);

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers);

// returns true if there is a member whose email is equal to newEmail
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers);

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers);

int main()
{
	Member memberDetails[100] = { "", "", "", "", "" };
	int numMembers = 0;

	ifstream inMemberFile;
	ofstream outMemberFile;

	loadMemberInfo(inMemberFile, memberDetails, numMembers);

	cout << "Welcome to Vieshow Cinemas member system\n\n";

	int choice;

	while (true)
	{
		cout << "Enter your choice:" << endl;
		cout << "1. Sign In\n";
		cout << "2. New Member\n";
		cout << "3. Sign Out\n? ";

		choice = inputAnInteger(1, 3);
		cout << endl;

		switch (choice)
		{
		case 1:
			login(memberDetails, numMembers);
			break;

		case 2:
			newMember(memberDetails, numMembers);
			break;

		case 3:
			saveMemberInfo(outMemberFile, memberDetails, numMembers);
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

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers) {

	inMemberFile.open("MemberInfo.dat", ios::in | ios::binary);
	if (!inMemberFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	while (!inMemberFile.eof())//如果讀檔還沒結束
	{
		inMemberFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(memberDetails[numMembers]));
		numMembers++;
	}
	numMembers--;
	inMemberFile.seekg(0, ios::beg);//從開頭的byte開始讀檔
	inMemberFile.close();
}

int inputAnInteger(int begin, int end) {
	int n;
	cin >> n;
	for (int i = begin; i <= end; i++)
	{
		if (n == i)
			return i;
	}
	return -1;
}

void login(Member memberDetails[], int numMembers) {
	Member member;
	int recordNumber, choice, go = 1;
	while (go)
	{
		cout << "Enter email address:";
		cin >> member.email;
		cout << "Enter password:";
		cin >> member.password;

		for (int i = 0; i <= numMembers - 1; i++)
		{
			if ((strcmp(memberDetails[i].email, member.email) == 0) && (strcmp(memberDetails[i].password, member.password) == 0))
			{//如果帳號密碼相符
				recordNumber = i;
				go = 0;
				break;//跳出迴圈 接著做下面的while
			}
		}
		if (go == 1)//如果帳號密碼不相符
			cout << "\nSorry, unrecognized email or password.\n\n";
	}
	while (1)//如果帳密相符就跑出第二個表單
	{
		cout << "\nEnter your choice:" << endl;
		cout << "1. Account Information\n";
		cout << "2. Buy Tickets\n";
		cout << "3. End\n? ";

		choice = inputAnInteger(1, 3);

		switch (choice)
		{
		case 1:
			accountInfor(memberDetails, numMembers, recordNumber);
			break;

		case 2:
			break;

		case 3:
			return;

		default:
			cout << "Input Error!\n";
			break;
		}
	}
}

bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber) {

	for (int i = 0; i <= numMembers - 1; i++) {
		if ((strcmp(memberDetails[i].email, email) == 0) && (strcmp(memberDetails[i].password, password) == 0))
		{//如果帳密存在且相符
			recordNumber = i;//記到recordnumber
			return true;
		}
	}
	return false;
}

void accountInfor(Member memberDetails[], int numMembers, int recordNumber) {

	int choice;
	cout << "\n1.Name:" << memberDetails[recordNumber].name << endl;
	cout << "2.Email Address:" << memberDetails[recordNumber].email << endl;
	cout << "3.Phone Number:" << memberDetails[recordNumber].phone << endl;
	cout << "4.ID Number:" << memberDetails[recordNumber].IDNumber << endl;
	cout << "5.Password:" << memberDetails[recordNumber].password << endl;
	cout << "\nWhich one do you want to modify (0 – not modify)? ";//修改資料
	while (1)
	{
		cin >> choice;
		switch (choice)
		{
		case 0:
			return;
		case 1:
			cout << "Enter correct data :";
			cin >> memberDetails[recordNumber].name;
			cout << "\nSuccessful!\n";
			return;

		case 2:
			cout << "Enter correct data :";
			cin >> memberDetails[recordNumber].email;
			cout << "\nSuccessful!\n";
			return;

		case 3:
			cout << "Enter correct data :";
			cin >> memberDetails[recordNumber].phone;
			cout << "\nSuccessful!\n";
			return;

		case 4:
			cout << "Enter correct data :";
			cin >> memberDetails[recordNumber].IDNumber;
			cout << "\nSuccessful!\n";
			return;
		case 5:
			cout << "Enter correct data :";
			cin >> memberDetails[recordNumber].password;
			cout << "\nSuccessful!\n";
			return;
		default:
			cout << "\nInput Error! Please try again:";
			break;
		}
	}
}

void newMember(Member memberDetails[], int& numMembers) {

	Member newMember;
	cout << "Enter your ID number:";
	cin >> newMember.IDNumber;
	if (existingID(newMember.IDNumber, memberDetails, numMembers))
	{//如果IDnumber存在
		cout << "\nAn account already exists with the ID number!\n\n";
		return;
	}

	cout << "Enter your name:";
	cin >> newMember.name;

	cout << "Enter an email address:";
	cin >> newMember.email;
	if (existingEmail(newMember.email, memberDetails, numMembers))
	{//如果email存在
		cout << "An account already exists with the email address!\n";
		return;
	}

	cout << "Enter a password:";
	cin >> newMember.password;

	cout << "Enter your phone number:";
	cin >> newMember.phone;

	memberDetails[numMembers] = newMember;
	numMembers++;

	cout << "\nSuccessful!\n\n";
	return;
}

bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers) {
	for (int i = 0; i <= numMembers - 1; i++) {
		if ((strcmp(memberDetails[i].IDNumber, newIDNumber) == 0))
			return true;//如果IDnumber存在
	}
	return false;
}

bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers) {
	for (int i = 0; i <= numMembers - 1; i++) {
		if ((strcmp(memberDetails[i].email, newEmail) == 0))
			return true;//如果email存在
	}
	return false;
}

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers) {
	outMemberFile.open("MemberInfo.dat", ios::out | ios::binary);
	if (!outMemberFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i <= numMembers - 1; i++)
		outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(memberDetails[i]));
	outMemberFile.seekp(0, ios::beg);//從開頭的byte開始寫檔
	outMemberFile.close();
}