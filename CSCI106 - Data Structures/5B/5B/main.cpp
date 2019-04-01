// File: main.cpp

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

int main()
{
    bool running=true;
    List myList;
    List dateDB;
    char input;
    string filename;
    ifstream fin;
    ofstream fout;
    
    DateType date, dBegin, dEnd;
    
    while (running==true)
    {
        

        
        cout << "********************************" << endl;
        cout << "**************MENU**************" << endl;
        cout << "Please select one: " << endl;
        cout << "K: To read a date manually" << endl;
        cout << "B: To clear the vector and then read a batch of dates by a specified file" << endl;
        cout << "D: Display the current dates" << endl;
        cout << "M: To modify one of the dates" << endl;
        cout << "W: Write the dates currently sorted into a specified file" << endl;
        cout << "F: Find and display dates within a range specified by user" << endl;
        cout << "Q: Quit the program" << endl;
        
        cin >> input;
        
        // add a new date 
        if (input=='k' || input =='K')
        {
            cout << "Please input date: " << endl;
            cin >> date;
            
            dateDB.InsertInOrder(date);

        }
        
        // FILE INPUT
        if (input=='b' || input =='B')
        {
            cout << "What is the name of the file?" << endl;
            cin >> filename;
            
            fin.open(filename);
            fin >> dateDB;
            // CLOSE FILE
            fin.close();
        }
        
        // DISPLAY DATES
        if (input=='d' || input =='D')
        {
            dateDB.Display();
        }
        
        // MODIFY
        if (input=='m' || input =='M')
        {
            DateType date;
            cin >> date;
            dateDB.Remove(date);
            cin >> date;
            dateDB.InsertInOrder(date);
        }
        
        // FILE OUTPUT
        if (input=='w' || input =='W')
        {
            
            cout << "What is the name of the file?" << endl;
            cin >> filename;
            
            // OPEN FILE
            fout.open(filename);
            
            // output the information
            fout << dateDB;
            
            // CLOSE
            fout.close();
            
        }
        
        // RANGE
        if (input=='f' || input =='F')
        {
            
            DateType dBegin, dEnd;
            cout << "Please enter the beginning date: " << endl;
            cin >> dBegin;
            
            cout << "Please enter the ending date: " << endl;
            cin >> dEnd;
        
            dateDB.FindAndDisplay(dBegin, dEnd);
            
        }
        
        // To QUIT
        if (input == 'q' || input == 'Q')
        {
            return 0;
        }
        
        
        
        if (input == 'G')
        {
            
            date.AdvanceDays(100);
            cout << date << endl; 
            
            
        }
        
    }
}







