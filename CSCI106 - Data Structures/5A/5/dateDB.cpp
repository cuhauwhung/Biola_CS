//
//  main.cpp
//  Programming 5B
//
//  Created by Willy Hung on 3/11/16.
//  Copyright © 2016 Willy Hung. All rights reserved.
//

#include "DateType.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

bool mergeTwoSortedVectors(vector<DateType> & vecA, vector< DateType > & vecB, vector< DateType > & vecC)
{
    // declare variables
    int countA = 0, countB = 0, countC = 0;
    bool combine1 = true, combine2 = true;
    
    // make sure the two vectors are in order
    // check if A is in order
    for (int i = 0; i < vecA.size() - 1; i++)
    {
        if (vecA[i].ComparedTo(vecA[i + 1]) == GREATER)
        {
            cout << "Vector is not in ascending order" << endl;
            return false;
        }
    }
    
    // make sure the two vectors are in order
    // check if B is in order
    for (int i = 0; i < vecB.size() - 1; i++)
    {
        if (vecB[i].ComparedTo(vecB[i + 1]) == GREATER)
        {
            cout << "Vector is not in ascending order" << endl;
            return false;
        }
    }
    
    // keep the loop running


    while (combine1==true)
    {
        // if one of the vectors reaches the end, just break
        if (countA == vecA.size() || countB == vecB.size())
        {
            break;
        }
     
        // if the countA variable of the first vector
        // is less than the countB variable of the second vector, then insert the
        // smaller number to vectorC[countC]
        if (vecA[countA].ComparedTo(vecB[countB])==LESS)
        {
            vecC[countC] = vecA[countA];
            countA++;
            countC++;
        }
        
        else if (vecA[countA].ComparedTo(vecB[countB]) == GREATER)
        {
            vecC[countC] = vecB[countB];
            countB++;
            countC++;
        }
        
        else if (vecA[countA].ComparedTo(vecB[countB]) == EQUAL)
        {
            vecC[countC] = vecA[countA];
            countA++;
            countC++;
            
            if (countA == vecA.size() || countB == vecB.size())
            {
                break;
            }
            
        }
    }
    
    
    // if vecA ends first, then transfer the remaining variables from vecB to vecC
    if (vecA.size() == countA)
    {
        while (combine2 == true)
        {
            
            if (countC == (vecA.size() + vecB.size()))
            {
                combine2=false;
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
                combine2=false;
            }
            
            vecC[countC] = vecA[countA];
            countC++;
            countA++;
            
        }
    }
    
    return true;
}

// mergesort section
bool mergeSort(vector<DateType> &vecToSort)

{

    // for 1 just return
    if (vecToSort.size()==1)
    {
        return true;
    }
    
    // for 2 just sawp elemnts
    else if (vecToSort.size()==2)
    {
        if (vecToSort[0].ComparedTo(vecToSort[1]) == GREATER)
        {
            DateType temp;
            temp=vecToSort[0];
            vecToSort[0] = vecToSort[1];
            vecToSort[1] = temp;
        }
    }
    
    // greater than 2
    else if (vecToSort.size()>2)
        
    {
        vector <DateType> vec1, vec2;
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
    vector <DateType> dateDB;
    DateType date, dBegin, dEnd;
    char input;
    string filename;
    ifstream fin;
    ofstream fout;
    int numDateRecords;
    
    bool running1 = true;
    while (running1== true)
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
        cout << "S: Sort the dates currently stored in the vector dateDB in order" << endl;
        cout << "Q: Quit the program" << endl;
        
        cin >> input;
        
        // JUST PUSHBACK NEW DATES
        if (input=='k' || input =='K')
        {
            cout << "Please input date: " << endl;
            cin >> date;
            dateDB.push_back(date);
        }
        
        // FILE INPUT
        if (input=='b' || input =='B')
        {
            cout << "What is the name of the file?" << endl;
            cin >> filename;
            
            fin.open(filename);
            
            // INPUT THE NUMBER OF DATES
            fin >> numDateRecords;
            
            // INPUT DATES ONE BY ONE
            if (numDateRecords>0)
            {
                dateDB.clear();
                
                for (int i=0; i<numDateRecords; i++)
                {
                    fin >> date;
                    dateDB.push_back(date);
                }
            }
            
            // CLOSE FILE
            fin.close();
        }
        
        // DISPLAY DATES
        if (input=='d' || input =='D')
        {
            cout << "The dates stored are: " << endl;
            for (int i=0; i<dateDB.size(); i++)
            {
                cout << dateDB[i] << endl;
            }
            
        }
        
        // MODIFY
        if (input=='m' || input =='M')
        {
            // INSERT INDEX
            int i;
            cout << "What is the index of the date you want to modify?" << endl;
            cin >> i;
            
            // MODIFY DATES ACCORDING TO INDEX
            dateDB[i].ReadDate();
            
        }
        
        // FILE OUTPUT
        if (input=='w' || input =='W')
        {
            
            cout << "What is the name of the file?" << endl;
            cin >> filename;
            
            // OPEN FILE
            fout.open(filename);
            
            // OUTPUT THE SIZE OF VECTOR
            fout << dateDB.size() << endl;
            
            // OUTPUT THE DATES
            for (int i=0; i<dateDB.size(); i++)
            {
                fout << dateDB[i] << endl;
            }
            
            // CLOSE
            fout.close();
            
        }
        
        // RANGE
        if (input=='f' || input =='F')
        {
            
            cout << "Please enter the beginning date: " << endl;
            cin >> dBegin;
            
            cout << "Please enter the ending date: " << endl;
            cin >> dEnd;
            
            // LOOP TO GO THROUGH THE WHOLE VECTOR
            for (int i=0; i<dateDB.size(); i++)
            {
                // IF THE DATES ARE IN BETWEEN SPECIFIED DATES THEN DISPLAY DATES
                if (dBegin<=dateDB[i] && dateDB[i]<=dEnd)
                    
                {
                    cout << dateDB[i];
                    
                }
                
            }
            
        }
        
        // CALL MERGESORT for the vector
        if (input == 's' || input == 'S')
        {
            mergeSort(dateDB);
            cout << "The date is Sorted" << endl;
        }
        
        // To QUIT
        if (input == 'q' || input == 'Q')
        {
            return 0;
        }
    }
    
}
