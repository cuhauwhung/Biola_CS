
#include "Appointment.h"
#include "DateType.h"
// Include the header file


//Default constrctor method to initialize a Appointment object.
//We want to initialize firstName and lastName as "John" and "Doe",
//						meeting place and phone as empty strings ""
//						AppointmentDay as Jan. 1 2000
Appointment::Appointment()
{
    FirstName = "John";
    LastName = "Doe";
    MeetingPlace = "";
    Phone = "";
}



//Another constrctor method to initialize a Appointment object
//using what is supplied in te declaration
Appointment::Appointment
(	string aFirstName,
	string aLastName,
	string aMeetingPlace,
	string aPhone,
	DateType aAppointmentDay
 )

{
    FirstName = aFirstName;
    LastName = aLastName;
    MeetingPlace = aMeetingPlace;
    Phone = aPhone;
    AppointmentDay = aAppointmentDay;
}



//Set the data members of a Appointment object.
// by using the information provided in the parameters above
void Appointment::SetAppointment
(	string newFirstName,
 string newLastName,
 string newMeetingPlace,
 string newPhone,
 DateType newAppointmentDay
 )
{
    FirstName = newFirstName;
    LastName = newLastName;
    MeetingPlace = newMeetingPlace;
    Phone = newPhone;
    AppointmentDay = newAppointmentDay;
}


// This member function should prompt the user to key in the first name, the last name,
// the phone number, the meeting place address, and the appointment day of a person.
// This member function should store the user input into the cooresponding data members
// of the object.
void Appointment::ReadInfo()
{
    cout << "What is the first name?" << endl;
    cin >> FirstName;
    cout << "What is the last name?" << endl;
    cin >> LastName;
    cout << "Where is the meeting place?" << endl;
    cin >> MeetingPlace;
    cout << "What is the phone number?" << endl;
    cin >> Phone;
    cout << "What is the appointment day?" << endl;
    AppointmentDay.ReadDate();
    
    
}


//Just print out the contents of the data members to
void Appointment::PrintInfo()
{
    
    cout << "The first name is: ";
    cout << FirstName << endl;
    cout << "The last name is: ";
    cout << LastName << endl;
    cout << "The meeting place is: ";
    cout << MeetingPlace << endl;
    cout << "The phone number is: ";
    cout << Phone << endl;
    cout << "The appointment day is: ";
    AppointmentDay.PrintDate();
    
    return;
}





// Pre: the object itself and a reference to another Appointment object aappointment
// Post: Function return value is
// LESS, if the full name of the object alphbatically comes before that of aappointment.
// EQUAL, if the full name of the object is the same of that of aappointment.
// GREATER, if the full name of the object alphbatically comes after that of aappointment.
int Appointment::CompareFullName(const Appointment & aappointment)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (LastName < aappointment.LastName)
    {
        return LESS;
    }
    else if (LastName == aappointment.LastName)
    {
        if (FirstName < aappointment.FirstName)
        {
            return LESS;
        }
        
        else if (FirstName == aappointment.FirstName)
        {
            return EQUAL;
        }
        else
        {
            return GREATER;
        }
    }
    
    else
    {
        return GREATER;
    }
    
    return 0;
}



// Pre: the object itself and 2 string objects: aFristName and aLastName
// Post: Function return value is
// LESS, if the full name of the object comes before that of aFristName and aLastName.
// EQUAL, if the full name of the object is the same of that of aFristName and aLastName.
// GREATER, if the full name of the object comes after that of aFristName and aLastName.
int Appointment::CompareFullName(string aFirstName, string aLastName)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
        if (LastName < aLastName)
    {
        return LESS;
    }
    else if (LastName == aLastName)
    {
        if (FirstName < aFirstName)
        {
            return LESS;
        }
        else if (FirstName == aFirstName)
        {
            return EQUAL;
        }
        else
        {
            return GREATER;
        }
    }
    else
    {
        return GREATER;
    }
    
    return 0;
}




// Pre: the object itself and a reference to another Appointment object aappointment
// Post: Function return value is
//	true if the full name of the object is the same as that
//		 of aappointment.
//	false otherwise
bool Appointment::SameFullName(const Appointment & aappointment)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
        if (FirstName == aappointment.FirstName && LastName == aappointment.LastName)
    {
        return true;
    }
    
    return false;
}


// Pre: the object itself and 2 string objects: aFristName and aLastName
// Post: Function return value is
//	true if the full name of the object is the same as that
//		 of 2 string objects: aFristName and aLastName.
//	false otherwise
bool Appointment::SameFullName(string aFirstName, string aLastName)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
        if (FirstName == aFirstName && LastName == aLastName)
    {
        return true;
    }
    
    return false;
}



// Pre: the object itself and a reference to another Appointment object aappointment
// Post: Function return value is
// LESS, if the appointment day of the object comes before that of aappointment.
// EQUAL, if the appointment day of the object is the same as that of aappointment.
// GREATER, if the appointment day of the object comes after that of aappointment.
int Appointment::CompareAppointmentDay(const Appointment & aappointment)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (AppointmentDay.ComparedTo(aappointment.AppointmentDay) == GREATER)
    {
        return GREATER;
    }
    else if (AppointmentDay.ComparedTo(aappointment.AppointmentDay) == LESS)
    {
        return LESS;
    }
    else if (AppointmentDay.ComparedTo(aappointment.AppointmentDay) == EQUAL)
    {
        return EQUAL;
    }
    return 0;
}


// Pre: the object itself and a DateType object aAppointmentDay
// Post: Function return value is
// LESS, if the appointment day of the object comes before aAppointmentDay.
// EQUAL, if the appointment day of the object is the same as aAppointmentDay.
// GREATER, if the appointment day of the object comes after aAppointmentDay.
int Appointment::CompareAppointmentDay(DateType aAppointmentDay)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (AppointmentDay.ComparedTo(aAppointmentDay) == GREATER)
    {
        return GREATER;
    }
    else if (AppointmentDay.ComparedTo(aAppointmentDay) == LESS)
    {
        return LESS;
    }
    else if (AppointmentDay.ComparedTo(aAppointmentDay) == EQUAL)
    {
        return EQUAL;
    }
    return 0;
}



// Pre: the object itself and a reference to another Appointment object aappointment
// Post: Function return value is
//	true if the appointment day of the object is the same as that of aappointment;
//	false otherwise.
bool Appointment::SameAppointmentDay(const Appointment & aappointment)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (AppointmentDay.ComparedTo(aappointment.AppointmentDay) == EQUAL)
    {
        return true;
    }
    else
        return false;
}


// Pre: the object itself and a DateType object aAppointmentDay
// Post: Function return value is
//	true if the appointment day of the object is the same as that of anInfo.
//	false otherwise
bool Appointment::SameAppointmentDay(DateType aAppointmentDay)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (AppointmentDay.ComparedTo(aAppointmentDay) == EQUAL)
    {
        return true;
    }
    else
        return false;
}


//Define the relationl operator >
bool Appointment::operator> (const Appointment & aappointment)
{
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    if (Appointment.CompareAppointmentDay(aappointment) == GREATER)
    {
        return true;
    }
    
    else if (Appointment.CompareAppointmentDay(aappointment) == EQUAL)
    {
        if (Appointment.CompareFullName(aappointment) == GREATER)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

//Define the relationl operator >=
bool Appointment::operator>= (const Appointment & aappointment)
{
    
    // Declare the object and set
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (Appointment.CompareAppointmentDay(aappointment) == GREATER || Appointment.CompareAppointmentDay(aappointment) == EQUAL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Define the relationl operator <
bool Appointment::operator< (const Appointment & aappointment)
{
    // Declare a new object and set
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (Appointment.CompareAppointmentDay(aappointment) == LESS)
    {
        return true;
    }
    
        else if (Appointment.CompareAppointmentDay(aappointment) == EQUAL)
        {
            if (Appointment.CompareFullName(aappointment) == LESS)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    
        else
        {
            return false;
        }
}


//Define the relationl operator <=
bool Appointment::operator<= (const Appointment & aappointment)
{
    // declare the object and set
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (Appointment.CompareAppointmentDay(aappointment) == LESS || Appointment.CompareAppointmentDay(aappointment) == EQUAL)
        
    {
        return true;
    }
    
        else
            
        {
            return false;
        }
}



//Define the relationl operator ==
bool Appointment::operator== (const Appointment & aappointment)
{
    // delcare object and set
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (Appointment.CompareAppointmentDay(aappointment) == EQUAL)
    {
        return true;
    }
    
        else
        {
            return false;
        }
}

//Define the relationl operator !=
bool Appointment::operator!= (const Appointment & aappointment)
{
    //declare object and set
    Appointment Appointment;
    Appointment.SetAppointment(FirstName, LastName, MeetingPlace, Phone, AppointmentDay);
    
    // JUST FOLLOW THE INSTRUCTIONS AS STATED ABOVE
    if (Appointment.CompareAppointmentDay(aappointment) == EQUAL)
    {
        return false;
    }
    
        else
        {
            return true;
        }
}


ostream & operator<< (ostream & output, const Appointment & aappointment)
{
    // if << (output) is the cout than just do cout
    if (&output == &cout)
    {
        cout << aappointment.FirstName << endl;
        cout << aappointment.LastName << endl;
        cout << aappointment.MeetingPlace << endl;
        cout << aappointment.Phone << endl;
        cout << aappointment.AppointmentDay << endl;
    }
    
    // if << (output) is the file output then do the file output
    if (&output != &cout)
    {
        
        output << aappointment.FirstName << endl;
        output << aappointment.LastName << endl;
        output << aappointment.MeetingPlace << endl;
        output << aappointment.Phone << endl;
        output << aappointment.AppointmentDay << endl;
    }
    
    return output;
}

istream & operator>> (istream & input, Appointment & aappointment)
{
    
    // if << (input) is the cin than just do read date
    if (&input == &cin)
    {
        
        aappointment.ReadInfo();
        
    }
    
    // if << (input) is not cin, then it is file input
    if (&input != &cin)
    {
        
        input >> aappointment.FirstName;
        input >> aappointment.LastName;
        input >> aappointment.MeetingPlace;
        input >> aappointment.Phone;
        input >> aappointment.AppointmentDay;
        
    }
    
    return input;
}



