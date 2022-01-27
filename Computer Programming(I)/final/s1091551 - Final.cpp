#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
using namespace::std;

struct Date
{
   int year = 2000;
   int month = 0;
   int day = 0;
};

struct Reservation
{
   char phoneNumber[ 12 ] = ""; // phone number
   char name[ 8 ] = "";         // name
   Date date = Date();          // reservation date
   int time = 0;                // reservation time¡G1 for 11:30, 2 for 13:30,
                                //                   3 for 17:45, 4 for 19:45
   int partySize = 0;           // the number of customers for a reservation
   int menu = 0;                // 1 for NT$ 1080, 2 for NT$ 1680, 3 for NT$ 2280
};

struct AvailSeats
{
   Date date = Date(); // a date
   int numAvailSeats[ 5 ] = {};
}; // numAvailSeats[ 1 ]: the number of seats available for lunch #1 (11:30 ~ 13:30)
   // numAvailSeats[ 2 ]: the number of seats available for lunch #2 (13:30 ~ 15:30)
   // numAvailSeats[ 3 ]: the number of seats available for dinner #1 (17:45 ~ 19:45)
   // numAvailSeats[ 4 ]: the number of seats available for dinner #2 (19:45 ~ 21:45)

const int totalNumSeats = 15;

// array of days per month
int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// loads reservations from the file Reservations.dat
void loadReservations( vector< Reservation > &reservations );

// loads availSeats from the file AvailSeats.dat
void loadAvailSeats( vector< AvailSeats > &availSeats );

// initialize availSeats
void initializeAvailSeats( vector< AvailSeats > &availSeats );

// returns true if and only if date1 is earlier than date2
bool earlier( const Date &date1, const Date &date2 );

// returns date1 - date2, i.e., the number of days between date1 and date2
int difference( const Date &date1, const Date &date2 );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// make a reservation
void makeReservation( vector< Reservation > &reservations,
                      vector< AvailSeats > &availSeats );

// compute the current date
void computeCurrentDate( Date &currentDate );

// returns true if and only if the specified year is a leap year
bool leapYear( int year );

// input reservation date
void inputDate( vector< AvailSeats > &availSeats, Date &date,
                const Date &currentDate, int partySize );

// returns currentDate + numDays
Date addition( const Date &currentDate, int numDays );

// returns true if and only if there are at least n seats available for date,
// where n = requiredSeats
bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int requiredSeats );

// returns true if availSeats[ i ].numAvailSeats[ timeCode ] >= requiredSeats,
// where availSeats[ i ].date == date
bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int timeCode, int requiredSeats );

// returns a nonnegative integer i if availSeats[ i ].date == date,
// returns -1 otherwise.
int findAvailSeat( const vector< AvailSeats > &availSeats, Date date );

// choose a reservation time
void inputTimeCode( const vector< AvailSeats > &availSeats, const Date date,
                    int &timeCode, int partySize );

// displays partySize, date and time in reservation
void displayReservationInfo( const Reservation &reservation );

// availSeats[ i ].numAvailSeats[ timeCode ] -= requiredSeats,
// where availSeats[ i ].date == date
void decreaseAvailSeats( vector< AvailSeats > &availSeats, const Date date,
                         int timeCode, int requiredSeats );

// input a phoneNumber,
// then displays partySize, date and time in all reservations for phoneNumber
void viewReservation( const vector< Reservation > &reservations );

// returns true if and only if there is an i such that
// reservations[ i ].phoneNumber == phoneNumber
bool exist( const vector< Reservation > &reservations, char phoneNumber[] );

// displays partySize, date and time in all reservations for phoneNumber
void displayReservationInfo( const vector< Reservation > &reservations,
                             char phoneNumber[] );

// stores reservations into the file Reservations.dat
void storeReservations( vector< Reservation > &reservations );

// stores availSeats into the file AvailSeats.dat
void storeAvailSeats( vector< AvailSeats > &availSeats );

int main()
{
   cout << "Welcome to Zuo Zhe Zuo Sushi Wo Shou Si\n";

   vector< Reservation > reservations; // vector of all reservations
   vector< AvailSeats > availSeats;    // Vector of available seats

   loadReservations( reservations );
   initializeAvailSeats( availSeats );

   int choice;
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Make Reservation\n"
         << "2. Reservation Enquiry\n"
         << "3. End Program\n";

      do cout << "? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makeReservation( reservations, availSeats );
         break;
      case 2:
         viewReservation( reservations );
         break;
      case 3:
         cout << "\nThank you. Goodbye.\n\n";
         storeReservations( reservations );
         storeAvailSeats( availSeats );
         system( "pause" );
		 return 0;
      default:
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadReservations( vector< Reservation > &reservations )
{
	ifstream inreservation("Reservations.dat",ios::binary);
	if (!inreservation)
	{
		cout << "Reservations can not open";
		system("pause");
	}
	Reservation i;
	//inreservation.ignore();
	while(!inreservation.eof())
	{
		
		inreservation.read(reinterpret_cast< char *>(&i), sizeof(i));
		//cout << i.date.day ;
		if (i.date.year == 2000)
			continue;
		//cout << i.menu << i.name << i.partySize << i.phoneNumber << i.time;
		reservations.push_back(i);
	}
	/*ifstream inreservation("Reservations.text");

	if (!inreservation)
	{
		cout << "Reservations can not open";
		system("pause");
	}
	int i = 1;
	while (!inreservation.eof())
	{
		reservations.resize(i);
		inreservation.getline(reservations[i - 1],);
		i++;
	}*/
	inreservation.close();
}

void loadAvailSeats( vector< AvailSeats > &availSeats )
{
	ifstream inavailSeats("AvailSeats.dat", ios::binary);
	if (!inavailSeats)
	{
		cout << "Reservations can not open";
		system("pause");
	}
	AvailSeats i ;
	//inavailSeats.ignore();
	inavailSeats.seekg(0);
	while (!inavailSeats.eof())
	{
		
		inavailSeats.read(reinterpret_cast<char*>(&i), sizeof(i));
		//cout << i.date.day;
		if (i.date.year == 2000)
			continue;

		availSeats.push_back(i);
	}

	inavailSeats.close();

}

void initializeAvailSeats( vector< AvailSeats > &availSeats )
{
   Date currentDate;
   computeCurrentDate( currentDate );

   loadAvailSeats( availSeats );

   Date date;
   AvailSeats seat;
   date = currentDate;
   if( availSeats.size() == 0 )
   {
	   for (int i = 0; i <= 30; i++)
	   {
		   seat.date.year = date.year;
		   seat.date.month = date.month;
		   seat.date.day = date.day;
		   date.day++;
		   if (date.day > days[date.month])
		   {
			   date.month++;
			   date.day = 1;
			   if (date.month > 12)
			   {
				   date.year++;
				   date.month = 1;
			   }
			   else
				   date.year = date.year;
		   }
		   else {
			   date.month = date.month;
			   date.year = date.year;
		   }
		   seat.numAvailSeats[1] = totalNumSeats;
		   seat.numAvailSeats[2] = totalNumSeats;
		   seat.numAvailSeats[3] = totalNumSeats;
		   seat.numAvailSeats[4] = totalNumSeats;
		   availSeats.push_back(seat);
	   }

   }
   else
   {
      if( earlier( availSeats[ availSeats.size() - 1 ].date, currentDate ) )
      {
		  for (int i = 0; i <= 30; i++)
		  {
			  availSeats[i].date.year = date.year;
			  availSeats[i].date.month = date.month;
			  availSeats[i].date.day = date.day;
			  date.day++;
			  if (date.day > days[date.month])
			  {
				  date.month++;
				  date.day = 1;
				  if (date.month > 12)
				  {
					  date.year++;
					  date.month = 1;
				  }
				  else
					  date.year = date.year;
			  }
			  else {
				  date.month = date.month;
				  date.year = date.year;
			  }
			  availSeats[i].numAvailSeats[1] = totalNumSeats;
			  availSeats[i].numAvailSeats[2] = totalNumSeats;
			  availSeats[i].numAvailSeats[3] = totalNumSeats;
			  availSeats[i].numAvailSeats[4] = totalNumSeats;
			  
		  }

      }
      else if( earlier( availSeats[ 0 ].date, currentDate ) )
      {
		  for (int i = 0; i <= 30; i++)
		  {
			  availSeats[i]= availSeats[i+1];
			 
		  }
		  availSeats[30].date.day = availSeats[29].date.day + 1;
		  if (availSeats[30].date.day > days[availSeats[30].date.month])
		  {
			  availSeats[30].date.month++;
			  availSeats[30].date.day=1;
			  if (availSeats[30].date.month > 12)
			  {
				  availSeats[30].date.year++;
				  availSeats[30].date.month = 1;
			  }
			  else
				  availSeats[30].date.year = availSeats[29].date.year;
		  }else{
			  availSeats[30].date.month = availSeats[29].date.month;
			  availSeats[30].date.year = availSeats[29].date.year;
		  }
			  
		  
		  availSeats[30].numAvailSeats[1] = totalNumSeats;
		  availSeats[30].numAvailSeats[2] = totalNumSeats;
		  availSeats[30].numAvailSeats[3] = totalNumSeats;
		  availSeats[30].numAvailSeats[4] = totalNumSeats;

      }
   }
}

bool earlier( const Date &date1, const Date &date2 )
{
	if (date1.year < date2.year)
		return true;
	else if (date1.year > date2.year)
		return false;
	else {
		if (date1.month < date2.month)
			return true;
		else if (date1.month > date2.month)
			return false;
		else {
			if (date1.day < date2.day)
				return true;
			else 
				return false;
		}
	}
	

}

int difference( const Date &date1, const Date &date2 )
{
	int y, m, d, t=0;
	Date date3;
	date3 = date2;
	while (1)
	{
		if (date3.year == date1.year && date3.month == date1.month && date3.day == date1.day)
			return t;
		else
		{
			t++;
			date3.day++;
			if (date3.day > days[date3.month])
			{
				date3.day = 1;
				date3.month++;
				if (date3.month > 12)
				{
					date3.month = 1;
					date3.year++;
				}
			}
		}
	}

}

int inputAnInteger( int begin, int end )
{
	char code[100];
	int intcode;

	cin.getline(code, 100, '\n');

	if (code[0] == '0' && code[1] != '\0')
		return -1;
	int i = 0;
	while(code[i] != '\0')
	{
		if (!isdigit(code[i]))
			return -1;
		i++;
	}

	intcode = atoi(code);

	for (int j = begin; j <= end; j++)
	{
		if (intcode == j)
			return j;
	}
	return -1;
}

void makeReservation( vector< Reservation > &reservations,
                      vector< AvailSeats > &availSeats )
{
   Reservation newReservation;
   cout << endl;
   do cout << "Enter the party size (1~6): ";
   while( ( newReservation.partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   inputDate( availSeats, newReservation.date, currentDate,
                          newReservation.partySize );

   inputTimeCode( availSeats, newReservation.date, newReservation.time,
                  newReservation.partySize );

   cout << "\nEnter name: ";
   cin >> newReservation.name;

   cout << "\nEnter phone Number: ";
   cin >> newReservation.phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   do cout << "? ";
   while( ( newReservation.menu = inputAnInteger( 1, 3 ) ) == -1 );

   cout << endl;
   displayReservationInfo( newReservation );

   cout << "\nReservation Completed.\n";

   reservations.push_back( newReservation );

   decreaseAvailSeats( availSeats, newReservation.date, newReservation.time,
                       newReservation.partySize );
}

void computeCurrentDate( Date &currentDate )
{
   int remainingSeconds = static_cast< int >( time( 0 ) ) + 8 * 60 * 60;

   currentDate.year = 1970;

   int secondsPerYear = 365 * 24 * 60 * 60;
   if( leapYear( currentDate.year ) )
      secondsPerYear += 24 * 60 * 60;

   while( remainingSeconds >= secondsPerYear ) 
   {
      remainingSeconds -= secondsPerYear;
      currentDate.year++;

      secondsPerYear = 365 * 24 * 60 * 60;
      if( leapYear( currentDate.year ) )
         secondsPerYear += 24 * 60 * 60;
   }

   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( leapYear( currentDate.year ) )
      days[ 2 ] = 29;

   currentDate.month = 1;
   while( remainingSeconds >= days[ currentDate.month ] * 24 * 60 * 60 )
   {
      remainingSeconds -= days[ currentDate.month ] * 24 * 60 * 60;
      currentDate.month++;
   }

   currentDate.day = remainingSeconds / ( 24 * 60 * 60 ) + 1;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

void inputDate( vector< AvailSeats > &availSeats, Date &date,
                const Date &currentDate, int partySize )
{
	cout << "\nChoose a date\n";
	int a[31];

	for (int i = 1; i <= 30; i++)
	{
		if (availSeats[i].numAvailSeats[1] < partySize && availSeats[i].numAvailSeats[2] < partySize && availSeats[i].numAvailSeats[3] < partySize && availSeats[i].numAvailSeats[4] < partySize)
		{
			a[i] = 0;
			continue;
		}
		cout << setw(2) << i << ". " << availSeats[i].date.year << "/" << availSeats[i].date.month << "/" << availSeats[i].date.day << "   ";
		a[i] = 1;
		if (i % 4 == 0)
			cout << endl;
	}
	cout << endl;
	int choice;
	do {
		cout << "?";
		choice = inputAnInteger(1, 30);
	} while (a[choice] == 0 || choice == -1);
		
	date.year = availSeats[choice].date.year;
	date.month = availSeats[choice].date.month;
	date.day = availSeats[choice].date.day;
}

Date addition( const Date &currentDate, int numDays )
{
	Date date;
	date.year = currentDate.year;
	date.month = currentDate.month;
	date.day = currentDate.day + numDays;
	while (date.day > days[date.month])
	{
		date.day -= days[date.month];
		date.month++;
		if (date.month > 13)
		{
			date.month = 1;
			date.year++;
		}
	}
	return date;
}

bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int requiredSeats )
{
	for (int i = 1; i <= 30; i++) {
		if (availSeats[i].date.day == date.day && availSeats[i].date.month == date.month && availSeats[i].date.year == date.year)
			if (availSeats[i].numAvailSeats[1] > requiredSeats || availSeats[i].numAvailSeats[2] > requiredSeats || availSeats[i].numAvailSeats[3] > requiredSeats || availSeats[i].numAvailSeats[4] > requiredSeats)
				return true;
	}
	return false;

}

bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int timeCode, int requiredSeats )
{
	int i = findAvailSeat(availSeats, date);
	
	if (availSeats[i].numAvailSeats[timeCode] >= requiredSeats )
				return true;
	
	return false;

}

int findAvailSeat( const vector< AvailSeats > &availSeats, Date date )
{
	for (int i = 0; i <= 30; i++)
	{
		if (availSeats[i].date.day == date.day && availSeats[i].date.month == date.month && availSeats[i].date.year == date.year)
			return i;
	}
	return -1;
}

void inputTimeCode( const vector< AvailSeats > &availSeats, const Date date,
                    int &timeCode, int partySize )
{
	cout << "\nChoose a time:\n";
	int i = findAvailSeat(availSeats, date), a[5] = {};
	for (int j = 1; j <= 4; j++)
		if (hasAvailableSeats(availSeats, date, j, partySize))
		{
			if (j == 1) {
				cout << setw(2) << j << ". 11:30\n";
				a[1] = 1;
			}
				
			if (j == 2) {
				cout << setw(2) << j << ". 13:30\n";
				a[2] = 1;
			}
				
			if (j == 3)
			{
				a[3] = 1;
				cout << setw(2) << j << ". 17:45\n";
			}
				
			if (j == 4) {
				a[4] = 1;
				cout << setw(2) << j << ". 19:45\n";
			}
				
		}

	int choice;
	do {
		cout << "?\n";
		choice = inputAnInteger(1, 4);
	} while (a[choice] == 0 || choice==-1);
	
	timeCode = choice;
}

void displayReservationInfo( const Reservation &reservation )
{
   cout << reservation.partySize << " guests  ";

   cout << reservation.date.year << "/";

   if( reservation.date.month < 10 )
      cout << '0';
   cout << reservation.date.month << "/";

   if( reservation.date.day < 10 )
      cout << '0';
   cout << reservation.date.day;

   char times[ 5 ][ 8 ] = { "", "11:30", "13:30", "17:45", "19:45" };
   cout << "  " << times[ reservation.time ] << endl;
}

void decreaseAvailSeats( vector< AvailSeats > &availSeats, const Date date,
                         int timeCode, int requiredSeats )
{
   int pos = findAvailSeat( availSeats, date );
   if( pos >= 0 ) // found
      availSeats[ pos ].numAvailSeats[ timeCode ] -= requiredSeats;
}

void viewReservation( const vector< Reservation > &reservations )
{
   if( reservations.size() == 0 )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   char phoneNumber[ 12 ];
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   if( !exist( reservations, phoneNumber ) )
   {
      cout << "\nYou have no reservations!\n";
      return;
   }

   displayReservationInfo( reservations, phoneNumber );
}

bool exist( const vector< Reservation > &reservations, char phoneNumber[] )
{
	for (int i = 0; i <= reservations.size() - 1; i++)
	{
		if (strcmp(reservations[i].phoneNumber, phoneNumber) == 0)
			return true;
	}
	return false;
}

void displayReservationInfo( const vector< Reservation > &reservations,
                             char phoneNumber[] )
{
   cout << endl;
   int count = 0;
   for( size_t i = 0; i < reservations.size(); ++i )
      if( strcmp( reservations[ i ].phoneNumber, phoneNumber ) == 0 )
      {
         cout << setw( 2 ) << ++count << ". ";
         displayReservationInfo( reservations[ i ] );
      }
}

void storeReservations( vector< Reservation > &reservations )
{
	ofstream outreservation("Reservations.dat",ios::binary);

	if (!outreservation)
		cout << "No";
	if(reservations.size()!=0)
		for (int i = 0; i <= reservations.size() - 1; i++) {
			//cout << reservations[i].date.day;
			outreservation.write(reinterpret_cast< char*>(&reservations[i]), sizeof(reservations[i]));
		}
			
	
	outreservation.close();
}

void storeAvailSeats( vector< AvailSeats > &availSeats )
{
	ofstream outstoreAvailSeats("AvailSeats.dat", ios::binary);

	if (!outstoreAvailSeats)
		cout << "No";
	
	if (availSeats.size() != 0)
		for (int i = 0; i <= availSeats.size() - 1; i++) {
			outstoreAvailSeats.write(reinterpret_cast<const char*>(&availSeats[i]), sizeof(availSeats[i]));
		}
			

	outstoreAvailSeats.close();

}