//**********************************************************
//The following two lines are additional compiler directives
//	to avoid the inclusion of the contents of DateType.h
//	more than one time when compiling shoe .cpp file.
//**********************************************************
#ifndef MY_DATETYPE_H
#define MY_DATETYPE_H

#define LESS	-1
#define EQUAL	0
#define GREATER	1

#include <iostream>
using namespace std;

// This is file DateType.h
// Here we declare the interface of a class so that we can
//	store the information of dates in objects of the DateType class and
//	call methods provided by these objects to process date information
// The actually implementation of the methods is inside DateType.cpp

class DateType
{
    
 public:	//The following members can be called anywhere

  DateType();
  //The first constructor method to initialize a DateType object
  //  initialize day, month, year in the object
  //  to 1, 1, and 2000 representing 1/1/2000

  DateType(int newMonth, int newDay, int newYear);
  //The second constructor method to initialize a DateType object
  //Check whether newMonth, newDay, newYear compose a valid date first.
  //If they do Not compose a valid date,
  //  initialize day, month, year in the object
  //  to 1, 1, and 2000 representing 1/1/2000
  //If they do compose a valid date,
  //   use newMonth, newDay, newYear to update day, month, year in the object,


  int YearIs();       // a method to returns year
  int MonthIs();      // a method to returns month
  int DayIs();        // a method to returns day

  bool SetDate(int newMonth, int newDay, int newYear);
  //A method to set a new date for the DateType object.
  //Check whether newMonth, newDay, newYear compose a valid date first.
  //If they do Not compose a valid date,
  //   do not change the date stored in the object and then return false.
  //If they do compose a valid date,
  //   use newMonth, newDay, newYear to update day, month, year in the object,
  //   and then return true.

  void ReadDate();
  //A method to read in three integers and set them as the
  //	as the day, month, year of the DateType object to the console cout

  void PrintDate();
  //A method to output the contents of the DateType object to the console cout

  int ComparedTo(DateType aDate);
  // Pre: the object itself and aDate should have been initialized.
  // Post:return value should be
  // 	LESS, if the object itself comes before aDate.
  //	EQUAL, if the object itself is the same as aDate.
  //	GREATER, if the object itself comes after aDate.

  int ComparedCentury(DateType aDate);
	// Pre: Self and aDate have been initialized.
	// Post: return
	//	LESS, if the object itSelf comes before the century of aDate.
	//	EQUAL, if the object itSelf is in the same century as aDate.
	//	GREATER, if the object itSelf comes after the century of aDate.

	void AdvanceDays(int NumDays);
	//Modify the date by advancing it "NumDays" days into the future.
	//Basic approach for implementing AdvanceDays: 
	//The easiest way to advance the current date some (non-negative) NumDays days 
	//	into the future is to use a loop that repeats for NumDays iterations. 
	//	Inside the loop, write your C++ code such that it can correctly 
	//	just advance the date one day into the future on each iteration of the loop. 
	//Note that in the is approach 
	//	(i) you need to precisely detect whether the current date is in the end of the month, 
	//		and be careful especially about February since it depends on whether it is a leap year, 
	//	(ii) when it is not the end of the month advancing one day into the future is very easy, but 
	//	(iii) when it is the end of the month, you have to carefully advance the date into 
	//		the first day of the next month, be careful especially when it is December 31.

	void BackDays(int NumDays);
	//Modify the date by pushing it back "NumDays" days into the past.
	//The easiest way to back down the current date some (non-negative) NumDays days 
	//	into the past is to use a loop that repeats for NumDays iterations. 
	//	Inside the loop, write your C++ code such that it can correctly just back down the date 
	//	one day into the past on each iteration of the loop. 
	//Note that in the is approach 
	//	(i) you need to precisely detect whether the current date is in the beginning of the month, 
	//	(ii) when it is not the beginning of the month backing down one day into the past is very easy, but 
	//	(iii) when it is the beginning of the month, you have to carefully back down the date into 
	//		the very last day of the previous  month, and you need to be careful 
	//		especially when it is Jan. 1 or March 1 (since the previous day could be Feb. 28 or Feb 29 
	//		depending on whether it is a leap year).

	bool IsValidDate (int Month, int Day, int Year);
	//Check the input date to make sure it is a valid date.
	//You can reuse what you did in Programming #3 and #5C in CSCI 105 last semester to 
	//	implement this member function. 
	//Essentially, you need to use the if statement or the switch statement to check to return true 
	//	only when the value in the data member day falls in the range of 
	//	(i) 1 to 31 if the data member month  indicates a month of 31 days, or 
	//	(ii) 1 to 30 if the data member month  indicates a month of 30 days, or 
	//	(iii) 1 to 28 if the data member month  indicates it is February while 
	//		the data member year  indicates it is not a leap year, or 
	//	(iv) 1 to 29 if the data member month  indicates it is February while 
	//		the data member year  indicates it is a leap year.
	//
	//How to determine leap years: 
	//	A year is a leap year if it is divisible by 4 except that 
	//		any year divisible by 100 is a leap year only if it is also divisible by 400. 
	//		So 1900 is not a leap year, but 2000 is. 
	//	In other words, 
	//		(i) a year (e.g. 1996) is a leap year if it is divisible by 4 but not by 100, 
	//		(ii) a year (e.g. 2000) is a leap year if it is divisible by 400, 
	//		(iii) otherwise, it is not a leap year.

  private: //The following members can be direclt accessed in DateType.cpp
  int year;
  int month;
  int day;

  //**********************************************************************
  // The following are new public member functions just added into DateType
  //**********************************************************************

  public:

  void SetRandomDate();

  bool operator> (const DateType & aDate);
	//Define the relationl operator >

  bool operator< (const DateType & aDate);
	//Define the relationl operator <

  bool operator== (const DateType & aDate);
	//Define the relationl operator ==

  bool operator!= (const DateType & aDate);
	//Define the relationl operator !=

  bool operator>= (const DateType & aDate);

      //Define the relationl operator >=

  bool operator<= (const DateType & aDate);

      //Define the relationl operator <=


  DateType operator+ (int numDays);

	//Define the arithmetic operator + such that it will

	//    return a separate DateType object recording a date

	//    that is numDays into the future from the DateType object

	//    performing this operation.

	//Note that the date recorded in the DateType object performing

	//    this operation should remain unchanged.

	//For example, in the following the output should be

	//    1/1/2010 and 1/3/2010 respectively.

	//         DateType d1(1,1, 2010)), d2;

	//          d2 = d1+2;       

	//          d1.PrintDate();

	//          d2.PrintDate();

    
	DateType operator- (int numDays);

	//Define the arithmetic operator - such that it will

	//    return a separate DateType object recording a date

	//    that is numDays into the past from the DateType object

	//    performing this operation.

	//Note that the date recorded in the DateType object performing

	//    this operation should remain unchanged.

	//For example, in the following the output should be

	//    1/3/2010 and 1/1/2010 respectively.

	//         DateType d1(1,3, 2010)), d2;

	//          d2 = d1-2;       

	//          d1.PrintDate();

	//          d2.PrintDate();

	int operator- (const DateType & aDate);

	//Define the arithmetic operator - such that

	//    it will calculate and return the number days to go

	//    from the DateType object aDate passed as the argument 

	//    to this DateType object now performing this operation.

	//The number returned should be positive if aDate records

	//    a date earlier than that recorded in this date,

	//The number returned should be negative if aDate records

	//    a date later than that recorded in this date,

	//The number returned should be 0 if aDate records records

	//    the same date as that recorded in this date.

	//For example, in the following, 2 should be the output generated.

	//         DateType d1(2,16, 2010), d2(2, 14, 2010);

	//          cout << d1-d2;         

 
 //***********************************************************************
 // The following two new global functions as I/O operators for DateType.
 // They are NOT member functions in DateType, but are declared as friends
 //   so that they can access the private data members of DateType objects
 //   for input and output.
 //***********************************************************************

 

  friend ostream & operator<< (ostream & output, const DateType & aDate);

	//For example, in the following 2/16/2010 should be the output.

	//         DateType d1(2,16, 2010);

	//          cout << d1;      

	//For example, in the following 2 14 2010 should be stored

	//    into the file someFile.txt.

	//         DateType d2(2, 14, 2010); ofstream fout;

	//          fout.open("someFile.txt");         

	//          fout << d2;      
	//************************************************************
	// Note that in your code you want to check
	//    whether output is a reference to cout or not by
	//    if (&output == &cout) …
	// If output is indeed a reference to cout,
	//    your code should print out day, month, year separated by '/'.
	//          output << month <<  '/' << day << '/' << year;
	// If output is NOT a reference to cout,
	//    it is a reference to an ostream object for file output and
	//    your code should simply do
	//          output << month <<  ' ' << day << ' ' << year;
	//    write out day, month, year separated by ' '.
	//************************************************************
     

  friend istream & operator>> (istream & input, DateType & aDate);

	//For example, in the following the user will be prompted

	//    to enter the day, month, and year as a date stored in d3

	//    just like how the ReadDate method should work.

	//         DateType d3;

	//          cin >> d3;       

	//For example, in the following 2 14 2010 should be read

	//    from the file someFile.txt into d4 as the date stored in d4.

	//         DateType d4 ifstream fin;

	//          fin.open("someFile.txt");          

	//          fin >> d4;  
  
	//************************************************************
	// Note that in your code you want to check
	//    whether input is a reference to cin or not by
	//    if (&input == &cin) …
	// If input is indeed a reference to cin,
	//    you can simply call the ReadDate method
	//    to prompt the user with messages on the screen
	//    to enter day, month, year separately from the keyboard,
	//    which will check and ensure the validity of date.
	// If input is NOT a reference to cin,
	//    (i) it is a reference to an istream object for file input and
	//    your code should read the information of
	//    day, month, and year into some local variables you declared
	//    through input without prompting the user such as:
	//          input >> tempM >> tempD >> tempYear;
	//    (ii) you should then check whether they compose a valid date:
	//    if yes, update the day, month, and year in aDate;
	//    if no, keep the day, month, and year in aDate unchanged.
	//************************************************************


};

#endif


