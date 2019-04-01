// Define member functions of class DateType.
// This is file DateType.cpp.

#include "DateType.h" // gain access to specification of class
#include <iostream>
using namespace std;

//The first constructor method to initialize a DateType object
//  initialize day, month, year in the object
//  to 1, 1, and 2000 representing 1/1/2000
DateType::DateType()
{
  year = 2000;
  month = 1;
  day = 1;
}

//The second constructor method to initialize a DateType object
//Check whether newMonth, newDay, newYear compose a valid date first.
//If they do Not compose a valid date,
//  initialize day, month, year in the object
//  to 1, 1, and 2000 representing 1/1/2000
//If they do compose a valid date,
//   use newMonth, newDay, newYear to update day, month, year in the object,
DateType::DateType(int newMonth, int newDay, int newYear)
{
  year = newYear;
  month = newMonth;
  day = newDay;
}

//A method to set a new date for the DateType object.
//Check whether newMonth, newDay, newYear compose a valid date first.
//If they do Not compose a valid date,
//   do not change the date stored in the object and then return false.
//If they do compose a valid date,
//   use newMonth, newDay, newYear to update day, month, year in the object,
//   and then return true.
bool DateType::SetDate(int newMonth, int newDay, int newYear)
{
  year = newYear;
  month = newMonth;
  day = newDay; 


  return true;
}

int DateType::MonthIs()
// Accessor function for data member month.
{
  return month;
}

int DateType::YearIs()
// Accessor function for data member year.
{
  return year;
}


int DateType::DayIs()
// Accessor function for data member day.
{
    return day;
}


void DateType::ReadDate()
{
	cout << endl 
		 << "Read in the information of a date: " ;
		 
	cout << endl << "The month is: "; 
	cin >> month;
	cout << endl << "The day is: "; 
	cin >> day;
	cout << endl << "The year is: "; 
	cin >> year;
}

void DateType::PrintDate()
{
    
    // Display the date
    cout << month << "/" << day << "/" << year << endl;
    
}


int DateType::ComparedTo(DateType aDate)
// Pre: Self and aDate have been initialized.
// Post: return
//  LESS, if self comes before aDate.
//  EQUAL, if self is the same as aDate.
//  GREATER, if self comes after aDate.
{
    // If tax year is less than groundhog year; return less
    if (year<aDate.year)
        
        {
            
            return LESS;
            
        }
    
    // If tax year is greater than groundhog year; return greater
    if (year>aDate.year)
        
        {
            
            return GREATER;
            
        }
    
    // If tax year is equal to the groundhog year
    if (year==aDate.year)
        
        {
            // if month is equal; we go one level down and compare day
            if (month==aDate.month)
                {
                    
                    // if days are equal; return equal
                    if (day==aDate.day)
                        
                        {
                            return EQUAL;
                        
                        }
                    
                    // if tax day less than groundhog day; return less
                    else if (day<aDate.day)
                        
                        {
                            
                            return LESS;
                            
                        }
                    
                    // if tax day more than groundhog day; return more
                    else if (day>aDate.day)
                        
                        {
                            
                            return GREATER;
                            
                        }
                    
                }
            
            // if month is less; return less
            if (month<aDate.month)
                
            {
                
                return LESS;
                
            }
        
            // if month is greater; return greater
            if (month>aDate.month)
                
            {
                
                return GREATER;
                
            }
            
        }
    return 1;
}

int DateType::ComparedCentury(DateType aDate)
// Pre: Self and aDate have been initialized.
// Post: return
//	LESS, if the object itSelf comes before the century of aDate.
//	EQUAL, if the object itSelf is in the same century as aDate.
//	GREATER, if the object itSelf comes after the century of aDate.
{
	//Replace the return statement with your own code here
 
        // Since its calcualted in integers, the values are rounded, making it easier to compare the difference and see which date comes first
        // If year/100 and aDate.year/100 is divided by 100 and yields the same integer, then they are in the same century. Eg 125/100 == 137/100 => 1==1
        if (year/100==aDate.year/100)
            
        {
            
            return EQUAL;
            
        }
    
        // if year/100>aDate.year/100. E.g. 562/100 > 354/100, which will be 5>3, then it will in a later century
        else if (year/100>aDate.year/100)
            
        {
            
            return GREATER;
            
        }
    
        // if year/100<aDate.year/100. E.g. 125/100 > 354/100, which will be 1<3, then it will in an earlier century
        else if (year/100<aDate.year/100)
            
        {
            
            return LESS;
            
        }

    return 1;
    
}



