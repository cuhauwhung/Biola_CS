// File: DateDriver.cpp

#include <iostream>
#include "DateType.h"
using namespace std;

int main()
{


	bool inMenu = true;	// while the user is using the program this var is set to true and the menu keeps looping.
						// when the user wants to quit, it is set to false and the loop ends.
	char keyPressed;	// This var stores which menu selection the user picks.

	while ( inMenu )
	{
		cout<< endl << endl << endl;
		cout << "****************************************************" << endl;
		cout  <<"**  MENU:(press a character to select an option)  **" << endl;
 		cout << "****************************************************" << endl;
		cout<<"Q. [QUIT]     Quit."<<endl;
		cout<<"C. [Constructor]	Test the default constructor and more"<<endl;
  		cout<<"S. [Set ]     Test the other constructor and the SetDate method,"<<endl;

		cout<<"R. [Read date]  Test the ReadDate, ComparedTo, and ComparedCentury methods"<<endl;
		cout << endl;

		cout<<"A. [Advance date]    Test the AdvanceDate method" << endl;
		cout<<"B. [Back date]  Test the BackDate method"<<endl;
		cout<<"T. [Test]   Test further how well the date move back"<<endl;

		cout << "****************************************************" <<endl<< endl;

		cout<<"Your choice is: ";
		cin >> keyPressed ;


		//Two DateType objects to be tested
		DateType taxDay;	//Declared and constructued by the defualt constructor

		DateType groundHogDay(2,12,2001); //Declared and constructued by the second constructor


		//Some  more objects and variables for testing in the code below
		DateType AdvancedDate;
		DateType BackDate;

        int numDays;
		int ddd;
		char chr;

		DateType x;

		switch(keyPressed) {
		case 'Q': case 'q'://Quit
			cout << "[QUIT]:" << endl;
			inMenu = false;
			break;

		case 'C': case 'c':
			cout << endl << endl 
				  << "******************************************************************" << endl
				  << "***   Test 1: test taxDay, a DateType object declared in the main function,"  << endl
				  << "***   to see how the defualt constructor, and YearIs(), MonthIs() " << endl
				  << "***   DayIs() and the PrintDate() methods work on taxDay" << endl
				  << "******************************************************************" << endl;

			  cout << "taxDay is initialized by the default constructor method:" << endl;
			  cout << "taxDay: year is " << taxDay.YearIs() << endl;
			  cout << "taxDay: day is " << taxDay.DayIs() << endl;
			  cout << "taxDay: month is " << taxDay.MonthIs() << endl<< endl;

			  cout<< " PrintDate methos prints the contents of taxDay as:"  << endl;
			  taxDay.PrintDate();
			break;

		case 'S': case 's':
			  cout << endl << endl 
				  << "******************************************************************" << endl
				  << "***   Test 2: test the second constructor,  SetDate() and" << endl
				  << "***  and the PrintDate() method ***" << endl
 				  << "******************************************************************" << endl;

				  cout << "groundHogDay is initialized by the second constructor:" << endl
				   << "groundHogDay(2,12,2001)" << endl
 				   << "The result is " << endl;
			  groundHogDay.PrintDate();
                
			  groundHogDay.SetDate(8,8,2005);
			  cout << endl
				   << "groundHogDay is reset now: groundHogDay.SetDate(8,8,2005)" << endl
				   << "The result is" << endl;
			  groundHogDay.PrintDate();
			break;

		case 'R': case 'r':// 3. Append new lines of code to the end
			  cout << endl << endl 
				  << "******************************************************************" << endl
				  << "***   Test 3: test ReadDate(), ComparedTo( ) and "<< endl
				  << "***   ComparedCentury methods " << endl
				  << "******************************************************************" << endl;

			  cout << endl << "Get a new groundHogDay" << endl;
			  groundHogDay.ReadDate();
			  cout << endl << "Got the groundHogDay as" << endl;
			  groundHogDay.PrintDate();

			  cout << endl << "Get a new taxDay" << endl;
			  taxDay.ReadDate();
			  cout << endl << "Got the taxDay as" << endl;
			  taxDay.PrintDate();

//			  cout << taxDay.ComparedTo(groundHogDay) << endl;

			  if (taxDay.ComparedTo(groundHogDay) == LESS)
				cout << "taxDay is less than groundHogDay" << endl;
			  else if (taxDay.ComparedTo(groundHogDay) == EQUAL)
				  cout << "taxDay is equal to groundHogDay" << endl;
			  else cout << "taxDay is greater than groundHogDay" << endl;

			  if (groundHogDay.ComparedTo(taxDay) == LESS)
				cout << "groundHogDay is less than taxDay" << endl;
			  else if (groundHogDay.ComparedTo(taxDay) == EQUAL)
				  cout << "groundHogDay is equal to taxDay" << endl;
			  else cout << "groundHogDay is greater than taxDay" << endl;

			  if (groundHogDay.ComparedCentury(taxDay) == LESS)
				cout << "groundHogDay is in an earlier century" << endl;
			  else if (groundHogDay.ComparedCentury(taxDay) == EQUAL)
				  cout << "groundHogDay and taxday are in the same century" << endl;
			  else cout << "groundHogDay is in a later century" << endl;

			break;

		case 'A': case 'a':// 4. 

			 cout << endl << endl 
			  << "******************************************************************" << endl
			  << "*** Test 4: test the AdvanceDays( )  method " << endl
			  << "******************************************************************" << endl;

			 cout << endl << "Set the initial date:" << endl;
			 AdvancedDate.ReadDate();
			 AdvancedDate.PrintDate();
			 cout << endl << "Advance the date:" << endl;

			 cout << "How many days to advence into the future?";
			 cin  >> numDays;
			 AdvancedDate.AdvanceDays(numDays);
			 cout << "The new date is: ";
			 AdvancedDate.PrintDate();
			break;

		case 'B': case 'b':// 5.
			 cout << endl << endl 
			  << "******************************************************************" << endl
			  << "*** Test 5: test the BackDays( ) method " << endl
			  << "******************************************************************" << endl;

			 cout << endl << "Set the initial date:" << endl;
			 AdvancedDate.ReadDate();
			 AdvancedDate.PrintDate();
			 cout << endl << "Set back the date:" << endl;
			 cout << "How many days to set back into hte past?";
			 cin  >> numDays;
			 AdvancedDate.BackDays(numDays);
			 cout << "The new date is: ";
			 AdvancedDate.PrintDate();
			break;


		case 'T': case 't':// 6. 
			  cout << endl << endl 
				  << "******************************************************************" << endl
				  << "*** Test 6: Check the BackDays( ) method 365 times and verify " << endl
				  << "*** it can correctly set Feb 14, 2007 back into Feb 14, 2006." << endl
 				  << "******************************************************************" << endl;
			 
			  x.SetDate(2,14,2007);
			  x.PrintDate();
			  cout << endl << endl;

			  ddd = 0;

			  //Back to Jan, 14, 2007
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;

			 //Back to Dec, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to Nov, 14, 2006
			  for (int i=0; i<30; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 30;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to Oct, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to Sept, 14, 2006
			  for (int i=0; i<30; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 30;
			  cout <<"Enter c to continue:";
			  cin >> chr;



			  //Back to Aug, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to July, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to June, 14, 2006
			  for (int i=0; i<30; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 30;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to May, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			  //Back to April, 14, 2006
			  for (int i=0; i<30; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 30;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			 
			  //Back to March, 14, 2006
			  for (int i=0; i<31; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 31;
			  cout <<"Enter c to continue:";
			  cin >> chr;


			 //Back to Feb, 14, 2006
			  for (int i=0; i<28; i++)
			  {
				x.BackDays(1);
				x.PrintDate();
				cout << endl << endl;
			  }
			  ddd+= 28;


			  cout << ddd << " days back from Feb 14, 2007 is :"  << endl;
			  x.PrintDate();
			break;

		default:
			cout << "[?? UNKNOWN COMMAND]:" << endl;
			// Unrecognized key, do nothing
			break;
		}


	} // End of while loop


}