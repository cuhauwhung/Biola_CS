// This is the Appointment.h file

#ifndef APPOINTMENT_INFO_H
#define APPOINTMENT_INFO_H

#include <iostream>
#include <string>
using namespace std;

#include "DateType.h"
//We use a DateType class object to store the appointment day information.
//Therefore. we need the DateType class interface information.
//We also refer to the following symbolic constants LESS, EQUAL, GREATER
//as define in DateType.h
//		#define LESS	-1
//		#define EQUAL	0
//		#define GREATER	1

// Include all the standard C++ libraries we need for the implementation.
// For example, we need the string class defined in <string> and std.
// We need <iostream> and std for input/output with cin, cout


// Declare the Appointment class to handle appointment information
class Appointment
{
public:
    
    Appointment();
    //Default constrctor method to initialize a Appointment object.
    //We want to initialize firstName and lastName as "John" and "Doe",
    //						meeting place and phone as empty strings ""
    //						AppointmentDay as Jan. 1 2000
    
    
    Appointment		(string aFirstName,
                     string aLastName,
                     string aMeetingPlace,
                     string aPhone,
                     DateType aAppointmentDay
                     );
    //Another constrctor method to initialize a Appointment object
    //using what is supplied in te declaration
    
    
    void SetAppointment(	string newFirstName,
                        string newLastName,
                        string newMeetingPlace,
                        string newPhone,
                        DateType newAppointmentDay
                        );
    //Set the data members of a Appointment object.
    // by using the information provided in the parameters above
    
    void ReadInfo();
    // This member function should prompt the user to key in the first name, last name,
    // the phone number, the meeting place address, and the appointment day of a person.
    // This member function should store the user input into the
    // corresponding data members of the object.
    
    void PrintInfo();
    //Just print out the contents of the data members to cout
    
    int CompareFullName(const Appointment & aappointment);
    // Pre: the object itself and a reference to another Appointment object aappointment
    // Post: Function return value is
    // LESS, if the full name of the object alphbatically comes before that of aappointment.
    // EQUAL, if the full name of the object is the same of that of aappointment.
    // GREATER, if the full name of the object alphbatically comes after that of aappointment.
    
    
    int CompareFullName(string aFirstName, string aLastName);
    // Pre: the object itself and 2 string objects: aFristName and aLastName
    // Post: Function return value is
    // LESS, if the full name of the object alphbatically comes before that of aFristName and aLastName.
    // EQUAL, if the full name of the object is the same of that of aFristName and aLastName.
    // GREATER, if the full name of the object alphbatically comes after that of aFristName and aLastName.
    
    
    bool SameFullName(const Appointment & aappointment);
    // Pre: the object itself and a reference to another Appointment object aappointment
    // Post: Function return value is
    //	true if the full name of the object is the same as that
    //		 of aappointment.
    //	false otherwise
    
    bool SameFullName(string aFirstName, string aLastName);
    // Pre: the object itself and 2 string objects: aFristName and aLastName
    // Post: Function return value is
    //	true if the full name of the object is the same as that
    //		 of 2 string objects: aFristName and aLastName.
    //	false otherwise
    
    
    int CompareAppointmentDay(const Appointment & aappointment);
    // Pre: the object itself and a reference to another Appointment object aappointment
    // Post: Function return value is
    // LESS, if the appointment day of the object comes before that of aappointment.
    // EQUAL, if the appointment day of the object is the same as that of aappointment.
    // GREATER, if the appointment day of the object comes after that of aappointment.
    
    
    int CompareAppointmentDay(DateType aAppointmentDay);
    // Pre: the object itself and a DateType object aAppointmentDay
    // Post: Function return value is
    // LESS, if the appointment day of the object comes before aAppointmentDay.
    // EQUAL, if the appointment day of the object is the same as aAppointmentDay.
    // GREATER, if the appointment day of the object comes after aAppointmentDay.
    
    
    bool SameAppointmentDay(const Appointment & aappointment);
    // Pre: the object itself and a reference to another Appointment object aappointment
    // Post: Function return value is
    //	true if the appointment day of the object is the same as that of aappointment;
    //	false otherwise.
    
    
    bool SameAppointmentDay(DateType aAppointmentDay);
    // Pre: the object itself and a DateType object aAppointmentDay
    // Post: Function return value is
    //	true if the appointment day of the object is the same as aAppointmentDay;
    //	false otherwise.
    
    
    
    bool operator> (const Appointment & aappointment);
    //Define the relationl operator >
    
    bool operator< (const Appointment & aappointment);
    //Define the relationl operator <
    
    bool operator== (const Appointment & aappointment);
    //Define the relationl operator ==
    
    bool operator!= (const Appointment & aappointment);
    //Define the relationl operator !=
    
    bool operator>= (const Appointment & aappointment);
    //Define the relationl operator >=
    
    bool operator<= (const Appointment & aappointment);
    //Define the relationl operator <=
    
    
    //Declare the following two global operators as friends
    friend ostream & operator<< (ostream & output, const Appointment & aappointment);
    friend istream & operator>> (istream & input, Appointment & aappointment);
    
    
    // Four data members to record the name, the meeting place, and the phone number.
private:
    
    // four data members to hold the name, meeting place, phone information in strings.
    string FirstName;
    string LastName;
    string MeetingPlace;
    string Phone;
    
    // One data member to hold the appointment day information in a DateType object.
    DateType AppointmentDay;
};


#endif

