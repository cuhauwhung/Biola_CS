// File: appointmentTest.cpp

#include <string>
#include <vector>
#include <iostream>
#include "Appointment.h"
#include <fstream>
using namespace std;

bool mergeTwoSortedVectors(vector<Appointment> & vecA, vector< Appointment > & vecB, vector< Appointment > & vecC)
{
    // declare variables
    int countA = 0, countB = 0, countC = 0;
    bool combine1 = true, combine2 = true;
    
    // keep the loop running
    while (combine1 == true)
    {
        // if one of the vectors reaches the end, just break
        if (countB == vecB.size() || countA == vecA.size())
        {
            break;
        }
        
        // if the countA variable of the first vector
        // is less than the countB variable of the second vector, then insert the
        // smaller number to vectorC[countC]
        if (vecA[countA] <= vecB[countB])
        {
            vecC[countC] = vecA[countA];
            countA++;
            countC++;
        }
        
        else if (vecA[countA] > vecB[countB])
        {
            vecC[countC] = vecB[countB];
            countB++;
            countC++;
        }
        
    }
    
    // if vecA ends first, then transfer the remaining variables from vecB to vecC
    if (vecA.size() == countA)
    {
        while (combine2 == true)
        {
            
            if (countC == (vecA.size() + vecB.size()))
            {
                break;
            }
            
            vecC[countC] = vecB[countB];
            countC++;
            countB++;
            
        }
        
    }
    
    // if vecB ends first, then transfer the remaining variables from vecA to vecC
    else if (vecB.size() == countB)
    {
        while (combine2 == true)
        {
            if (countC == (vecA.size() + vecB.size()))
            {
                break;
            }
            
            vecC[countC] = vecA[countA];
            countC++;
            countA++;
            
            
        }
    }
    
    return true;
}

// mergesort section
bool mergeSort(vector<Appointment> &vecToSort)
{
    
    // for 1 just return
    if (vecToSort.size()==1)
    {
        return true;
    }
    
    // for 2 just sawp elemnts
    else if (vecToSort.size()==2)
    {
        if (vecToSort[0]>vecToSort[1])
        {
            Appointment temp;
            temp=vecToSort[0];
            vecToSort[0] = vecToSort[1];
            vecToSort[1] = temp;
        }
    }
    
    // greater than 2
    else if (vecToSort.size()>2)
        
    {
        vector <Appointment> vec1, vec2;
        int w = 0;
        
        // resize the big to two smaller vectors
        vec1.resize(vecToSort.size() / 2);
        vec2.resize(vecToSort.size() - vecToSort.size() / 2);
        
        
        // sort the first halve of the vector
        for (int i = 0; i<vec1.size(); i++)
        {
            vec1[i] = vecToSort[w];
            w++;
        }
        
        // sort the second halve of the vector
        for (int i = 0; i<vec2.size(); i++)
        {
            vec2[i] = vecToSort[w];
            w++;
        }
        
        // this is the recursion
        mergeSort(vec1);
        mergeSort(vec2);
        
        // once the two havles are sorted after the recursion, then merge the sorted vectors
        mergeTwoSortedVectors(vec1, vec2, vecToSort);
        
    }
    
    return true;
    
}

int main()
{
    
    // declare the vector
    vector<Appointment> appointmentDB;
    vector <Appointment>::iterator Iter;

    // delcrations
    ifstream fin;
    ofstream fout;
    
    bool run=true;
    char option;
    
    while (run==true)
    {
        
        // menu options
        cout << "###############################################################################" << endl;
        cout << "K: to read an Appointment object manually" << endl;
        cout << "R: Read information of Appointment objects from a file specified" << endl;
        cout << "D: Display appointment objects in vector" << endl;
        cout << "M: Modify one of the appointment objects" << endl;
        cout << "X: Excldue one of the appointment objects by removing it from the vector appointmentDB" << endl;
        cout << "W: Write to file" << endl;
        cout << "A: Find appointment objects within two specified dates" << endl;
        cout << "E: Find appointment days within the same week of the date specified by the user" << endl;
        cout << "N: Find the full Name given by the user" << endl;
        cout << "S: Sort the Appointment objects in vector in order" << endl;
        cout << "Q: Quit" << endl;
        cout << "###############################################################################" << endl;
        
    
        cin >> option;
        
        // option k
        if (option=='K' || option=='k')
            
        {
            
            // delcare
            Appointment insert;
            
            // read the info into insert
            insert.ReadInfo();
            
            // add insert into vector
            appointmentDB.push_back(insert);
            
        }
        
        // Read file
        if (option=='R' || option=='r')
        {
            // declare variables
            string filename;
            int numContsctInfoRecords;
            Appointment aAppointment;
            
            // input filename
            cout << "Input the filename: ";
            cin >> filename;
            fin.open(filename);
            fin >> numContsctInfoRecords;
            
            // check if count is greater than 0
            if (numContsctInfoRecords > 0)
                
            {
                
                appointmentDB.clear();
                
                // loop and read the data
                for (int i = 0; i < numContsctInfoRecords; i++)
                {
                    fin >> aAppointment;
                    appointmentDB.push_back(aAppointment);
                }
                
            }
            
            fin.close();
        }
        
        // display data
        if (option=='D' || option=='d')
        {
            // loop until all the data is displayed
            for (int i=0; i<appointmentDB.size(); i++)
            {
                cout << appointmentDB[i] << endl;
            }

        }
        
        // modify the information
        if (option=='M' || option=='m')
        {
            
            int index;
            // check index
            cout << "What is the index of the appointment information you want to modify?" << endl;
            cin >> index;
            
            // index has to be in between 0 and size of vector
            if (index >= 0 && index < appointmentDB.size())
            {
                appointmentDB[index].ReadInfo();
            }
            
        }
        
        // delete one appointment
        if (option=='X' || option=='x')
        {
            
            // delcare
            int i;
            
            // index of the appointment you want to delete
            cout << "What is the index of the appointment you want to delete?" << endl;
            cin >> i;
            
            // index has to be in between 0 and size of vector
            if (i >= 0 && i<appointmentDB.size())
            {
                appointmentDB.erase(appointmentDB.begin()+i);
            }
            
        }
        
        // write data into file
        if (option=='W' || option=='w')
        {
            // insert file name
            string filename;
            cout << "What is the name of the file?" << endl;
            cin >> filename;
            
            // OPEN FILE
            fout.open(filename);
            
            // OUTPUT THE SIZE OF VECTOR
            fout << appointmentDB.size() << endl;
            
            // OUTPUT THE DATES
            for (int i=0; i<appointmentDB.size(); i++)
            {
                fout << appointmentDB[i] << endl;
            }
            
            // CLOSE
            fout.close();

        }
        
        // disply dates between a set range
        if (option=='A' || option=='a')
        {
            
            // declare and set
            DateType dBegin, dEnd;
            dBegin.ReadDate();
            dEnd.ReadDate();
            
            // loop and check the whole vector
            for (int i=0; i<appointmentDB.size(); i++)
            {
                
                // if the appointment is in between the set dates, then display
                if (appointmentDB[i].CompareAppointmentDay(dBegin) == GREATER && appointmentDB[i].CompareAppointmentDay(dEnd) == LESS)
                {
                    cout << appointmentDB[i] << endl;
                }
            }
                
        }
        
        // display dates within a week
        if (option=='E' || option=='e')
        {
            
            // dBegin is Sunday and dEnd is Saturday
            DateType d, dBegin, dEnd, dReference(5,1,2016), temp;
            
            // Insert date
            cout << "Insert the date: ";
            d.ReadDate();
            
            // this works if the date is after the reference date
            dBegin=d+(dReference-d)%7;
            
            // however if the date is before we have to account for a week, because the date will go traverse right to d
            if (d.ComparedTo(dReference)==LESS)
            {
                dBegin=dBegin-7;
            }
            
            dEnd=dBegin+6;

            // loop through whole vector
            for (int i=0; i<appointmentDB.size(); i++)
            {
                
                // if dates fall between specified criteria, display
                if (appointmentDB[i].SameAppointmentDay(dBegin) == true || (appointmentDB[i].CompareAppointmentDay(dBegin) == GREATER && appointmentDB[i].CompareAppointmentDay(dEnd) == LESS) || appointmentDB[i].SameAppointmentDay(dEnd) == true)
                    
                {
                    cout << appointmentDB[i] << endl;
                }
                
            }
            
            
        }
        
        // search name and display
        if (option=='N' || option=='n')
        {
            Appointment name;
            string aFirstName, aLastName;
            
            // enter name
            cout << "Please enter first name" << endl;
            cin >> aFirstName;
            cout << "Please enter last name" << endl;
            cin >> aLastName;
            
            // search through whole vector
            for (int i=0; i<appointmentDB.size(); i++)
            {
                // if names match, display
                if (appointmentDB[i].SameFullName(aFirstName, aLastName))
                {
                    appointmentDB[i].PrintInfo();
                }
            }
            
            
        }
        
        // mergeSort 
        if (option=='S' || option=='s')
        {
            
            mergeSort(appointmentDB);

        }
        
        // QUIT 
        if (option=='Q' || option=='q')
        {
            
            cout << "The service is ending now" << endl;
            return 1;
            
        }
        
        
    }
}



