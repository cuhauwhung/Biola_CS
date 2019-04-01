//********************************************************************
//	Replace the Contents of your file
//		with your own DateType.cpp from Programming #1B
//********************************************************************
// Define member functions of class DateType.
// This is file DateType.cpp.

#include "DateType.h" // gain access to specification of class
#include <iostream>
#include <fstream>
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
    
    if (IsValidDate(newMonth, newDay, newYear)==true)
    {
        year=newYear;
        month= newMonth;
        day=newDay;
        
    }
    
        else
        {
            year=2000;
            day=1;
            month=1;
        }
    
    
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
    
    // if the setdate in the main.cpp is wrong then this it will say it's invalid
    // then it will ask us to input a valid date
    if (IsValidDate(newMonth, newDay,newYear)==false)
    {
        return false;
    }
    
    // if the setdate in the main.ccp is correct
        else
        {
            year=newYear;
            month=newMonth;
            day=newDay;
        }

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
    
    // input dates
    cout << endl << "The month is: ";
    cin >> month;
    cout << endl << "The day is: ";
    cin >> day;
    cout << endl << "The year is: ";
    cin >> year;
    
    // check if the inputs are correct
    // if the input is false then it will keep looping until the input is correct
    while (IsValidDate(month, day, year)==false)
        
    {
        if (IsValidDate(month, day, year)==false)
            
        {
            cout << "Not a valid date" << endl;
            cout << "Please enter a valid date" << endl;
            cout << endl << "The month is: ";
            cin >> month;
            cout << endl << "The day is: ";
            cin >> day;
            cout << endl << "The year is: ";
            cin >> year;
        }
        
    }
    
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

//
void DateType::AdvanceDays(int NumDays)
{
    // You want to go back call NumDays
    if (NumDays<0)
    {
        BackDays(-NumDays);
        return;
    }
    
    // the loop to add 1 day to days and see if it reaches the end of the month
    while (NumDays>0)
    {
        NumDays=NumDays-1;
        day++;
        
        // for months with 31 days
        if (month==1|| month==3||month==5||month==7||month==8||month==10)
        {
            // if it gets to the end of the month, then add one to month and then let day go back to 1
            if (day>31)
            {
                day=1;
                month=month+1;
            }
            
        }
        
        // for february
        else if (month==2)
        {
            // This is to check if its a leap year
            if ((year%4==0 && year%100!=0)|| year%400==0)
            {
                
                // leap year then the month should end at 29
                if (day>29)
                {
                    day=1;
                    month=month+1;
                }
                
            }
            // not a leap year then the month should end at the 28
            else
            {
                if (day>28)
                {
                    day=1;
                    month=month+1;
                }
            }
            
        }
        
        // for months with 31 days
        else if (month==4|| month==6||month==9||month==11)
        {
            // if it gets to the end of the month, then add one to month and then let day go back to 1
            if (day>30)
            {
                day=1;
                month=month+1;
            }
            
        }
        
        // for month of December
        else if (month==12)
        {
            // if it reaches the end of December then the year should +1 and the month go back to January
            if (day>31)
            {
                day=1;
                year=year+1;
                month=1;
            }
        }
        
        
    }
    
}

void DateType::BackDays(int NumDays)
{
    
    // You want to go back call NumDays
    if (NumDays<0)
    {
        AdvanceDays(-NumDays);
        return;
    }
    
    // if NumDays is more than 0, the loop will continue to run
    while (NumDays>0)
    {
        
        // NumDays gets subtracted by 1 each iteration
        // days get subracted by 1 each iteration
        NumDays=NumDays-1;
        day=day-1;
        {
            
            // if the month are these ones, then the month before these ones have 31 days
            if (month==2|| month==4 || month==6 || month==8 || month==9 || month==11)
            {
                
                // if the time reaches the beginning of the month, then the month gets subracted and then it goes to the previous month
                if (day==0)
                {
                    day=31;
                    month=month-1;
                }
                
            }
            
            // if its march and it reaches the beginning of the month, then we should check if the previous month (February) has 29 or 28 days
            if (month==3)
            {
                if (day==0)
                {
                    
                    // This is to check if its a leap year
                    if ((year%4==0 && year%100!=0)|| year%400==0)
                    {
                        day=29;
                        month=month-1;
                    }
                    
                    // not a leap year then the month should end at the 28
                    else
                    {
                        day=28;
                        month=month-1;
                    }
                }
            }
            
            // if the month are these ones, then the month before these ones have 30 days
            if (month==5 || month ==7 || month==10 || month==12)
            {
                if (day==0)
                {
                    day=30;
                    month=month-1;
                }
            }
            
            // if the month is january and it reaches the beginning of the month, then we should subract 1 year and go back to December
            if (month==1)
            {
                if (day==0)
                {
                    month=12;
                    day=31;
                    year=year-1;
                }
                
            }
            
        }
        
    }
    
    
    return;
}

// function to check if the date is valid
bool DateType::IsValidDate(int newMonth, int newDay, int newYear)
{
    // overall year to check
    if (year>0)
    {
        // these months should have less than 31 days
        if (newMonth==1|| newMonth==3||newMonth==5||newMonth==7||newMonth==8||newMonth==10||newMonth==12)
        {
            if (newDay>0 && newDay<=31)
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        
        // for february
        else if (newMonth==2)
        {
            // This is to check if its a leap year
            // for leap year
            if ((newYear%4==0 && newYear%100!=0)|| newYear%400==0)
            {
                
                if (newDay<=29)
                {
                    return true;
                }
                else
                    
                {
                    return false;
                }
            }
            
            // for not a leap year
            else if ((newDay%4!=0 && newYear%100==0)|| newYear%400!=0)
            {
                if (newDay<=28)
                {
                    return true;
                }
                
                else
                {
                    return false;
                }
            }
            
        }
        
        // for months with 30 days
        else if (newMonth==4|| newMonth==6||newMonth==9||newMonth==11)
        {
            if (newDay<=30)
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        
        // if anything else return false
        else if (newMonth <0 || newMonth>0)
        {
            return false;
        }
        
    }
    
    // if the day is less than 0; return false
    else
        
    {
        return false;
    }
    
    return 1;
    
}

// SET RANDOM DATE FUNCTION
void DateType:: SetRandomDate()
{
    
    //random year and month
    year=rand()%10000;
    month=rand()%12;
    
    // IF the year and months are 0, then loop until the year isn't 0
    while (year==0)
    {
        year=rand()%10000;
    }
    
    while(month==0)
    {
        month=rand()%12;
    }
    
    
        // these months should have less than 31 days
        if (month==1|| month==3||month==5||month==7||month==8||month==10||month==12)
        {
            
            day=rand()%31;
            
        }
        
        // for february
        else if (month==2)
        {
            // This is to check if its a leap year
            // for leap year
            if ((year%4==0 && year%100!=0)|| year%400==0)
            {
                
                day=rand()%29;
      
            }
            
            // for not a leap year
            else if ((year%4!=0 && year%100==0)|| year%400!=0)
            {
                day=rand()%28;
            }
        }
        
        // for months with 30 days
        else if (month==4|| month==6||month==9||month==11)
        {
            day=rand()%30;
        }
    
    while(day==0)
    {
        // these months should have less than 31 days
        if (month==1|| month==3||month==5||month==7||month==8||month==10||month==12)
        {
            
            day=rand()%31;
            
        }
        
        // for february
        else if (month==2)
        {
            // This is to check if its a leap year
            // for leap year
            if ((year%4==0 && year%100!=0)|| year%400==0)
            {
                
                day=rand()%29;
                
            }
            
            // for not a leap year
            else if ((year%4!=0 && year%100==0)|| year%400!=0)
            {
                day=rand()%28;
            }
        }
        
        // for months with 30 days
        else if (month==4|| month==6||month==9||month==11)
        {
            day=rand()%30;
        }

    }
    
}

// overload the operator >
bool DateType:: operator>(const DateType& aDate)
{
    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==GREATER)
    {
        return true;
    }
    
        else
        {
            return false;
        }
    
    
    return 1;
}

// overload the < operator
bool DateType:: operator<(const DateType & aDate)
{
    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==LESS)
    {
        return true;
    }
    
        else
        {
            return false;
        }
    
    
    return 1;

}

// overload the == operator
bool DateType:: operator==(const DateType & aDate)
{

    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==EQUAL)
    {
        return true;
    }
    
        else
        {
            return false;
        }
    
    return 1;
    
}

bool DateType:: operator!=(const DateType & aDate)
{
    
    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==EQUAL)
    {
        return false;
    }
    
        else
        {
            return true;
        }
    
    return 1;
    
}

// overload the operator >=
// THIS IS ALMOST thes same as the > operator, but add a = behind the >
// So instead of just strictly greater to, it compares greater and equal to
bool DateType:: operator>=(const DateType & aDate)
{
    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==GREATER || bDate.ComparedTo(aDate)==EQUAL)
    {
        return true;
    }
    
        else
        {
            return false;
        }
    
    return 1;
    
}


// overload the operator <=
// THIS IS ALMOST thes same as the < operator, but add a = behind the <
// So instead of just strictly less to, it compares less and equal to
bool DateType:: operator<=(const DateType & aDate)
{
    
    DateType bDate;
    bDate.SetDate(month, day, year);
    
    // call compared to and return according to the relationship
    if (bDate.ComparedTo(aDate)==LESS || bDate.ComparedTo(aDate)==EQUAL)
    {
        return true;
    }
    
        else
        {
            return false;
        }
    

    return 1;
    
}

// This is to overload the operator +
DateType DateType:: operator+(int numDays)
{
    
    // Make two datetype objects
    DateType aDate, bDate;
    
    // Set the date of the first object and make the second object equal to the first one
    aDate.SetDate(month, day, year);
    bDate=aDate;
    
    // Advance the date of the second date and return the second date
    bDate.AdvanceDays(numDays);
    
    return bDate;
}

// This is to overload the operator -
DateType DateType:: operator-(int numDays)
{
    
    // Make two datetype objects
    DateType aDate, bDate;
    
    // Set the date of the first object and make the second object equal to the first one
    aDate.SetDate(month, day, year);
    bDate=aDate;
    
    // Back the date of the second date and return the second date
    bDate.BackDays(numDays);
    
    return bDate;
    
}

// This is to overload the operator - for two date type classes
int DateType:: operator- (const DateType& aDate)
{
    // Create and set a Datetype object
    DateType oDate;
    oDate.SetDate(month, day, year);
    
    // Create an int variable to keep track of each iteration
    int runday=0;

    // While the dates are not equal, than keep the loop running
    while (oDate.ComparedTo(aDate)!=EQUAL)
    {
        
        // if the first date is greater than, then do back days
        if (oDate.ComparedTo(aDate)==GREATER)
        {
            
            oDate.BackDays(1);
            runday++;

        }
        
        // if the first date is less than, then do advance days
        else if (oDate.ComparedTo(aDate)==LESS)
        {
            
            oDate.AdvanceDays(1);
            runday=runday-1;
            
        }
        
        // the loop will stop once the two date equal each other
        
    }

    // return the number of days that are being kept tracked
    return runday;
    
}

// To overlaod the console OUTPUT and file OUTPUT
ostream & operator<< (ostream & output, const DateType & aDate)
{
    
    // if << (output) is the cout than just do cout
    if (&output == &cout)
    {
        cout << aDate.month << " / " << aDate.day << " / " << aDate.year << endl;
    }
    
    // if << (output) is the file output then do the file output
    if (&output != &cout)
    {
        
        output <<aDate.month << endl;
        output << aDate.day << endl;
        output << aDate.year << endl;
        
    }
    
    return output;
}

istream & operator>> (istream&input, DateType& aDate)

{
    DateType bDate;
    
    // if << (input) is the cin than just do read date
    if (&input == &cin)
    {
        
        aDate.ReadDate();
        
    }
    
    // if << (input) is not cin, then it is file input
    if (&input != &cin)
    {
        
        // get the input from the file
        input >>bDate.month >>bDate.day >>bDate.year;
        
        // if the dates from the file are true than set the date to the new date
        if (bDate.IsValidDate(bDate.month, bDate.day, bDate.year)==true)
            
            {
                aDate=bDate;
            }
        
                // if false, then keep the don't change the date
                else
                {

                }

    }
        
    return input;
}

