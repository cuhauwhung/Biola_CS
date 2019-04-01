//  main.cpp
//  HW5
//
//  Created by Cu Hauw Hung on 10/18/17.
//  Copyright © 2017 Cu Hauw Hung. All rights reserved.
//

using namespace std;
#include <iostream>
#include <fstream>
#include <new>
#include <string>

int partition(int low, int high, int* s)
{
    int pivotItem = s[low];
    int j = low;
    
    for (int i = low+1; i <= high; i++)
    {
        if (s[i] <= pivotItem)
        {
            j++;
            swap(s[i], s[j]);
        }
    }
    
    pivotItem=j;
    swap(s[low], s[pivotItem]);
    
    return j;
}


void quickSort(int low, int high, int* s)
{
    if (high > low)
    {
        int pivotPoint = partition(low, high, s);
        quickSort(low, pivotPoint-1, s);
        quickSort(pivotPoint+1, high, s);
    }
}

int main(){
    
    int i=0, content=0, number_of_lines=0, count=0;
    int *p;
    string line;
    
    ifstream myfile("p1data.txt");
    
    // If we couldn't open the output file stream for writing
    if (!myfile){
        // Print an error
        cout << "Could not be opened for writing!" << endl;
        cout << "This program is going to exit" << endl;
        system("pause");
        exit(1);
        
    }
    
    else {
        // cout << "File opened" << endl;
        // check the number of lines
        while (getline(myfile, line))
            ++number_of_lines;
        
        // if file is empty
        if (number_of_lines == 0) {
            cout << "This file is empty" << endl;
            cout << "This program is going to exit" << endl;
            system("pause");
            exit(1);
        }
        
        // close and open file
        myfile.close(); myfile.clear();
        myfile.open("p1data.txt");
        
        p = new (nothrow) int[number_of_lines];
        
        // start moving contents into array
        while (myfile >> content) {
            p[i] = content;
            i++;
        }
        
        // close file
        myfile.close();
        
        // Output
        cout << "The created array: " << endl;
        for (int i = 0; i < number_of_lines; i++) {
            cout << p[i] << endl;
        }
        
        // perform quickSort
        quickSort(0, number_of_lines-1, p);
        
        // Output
        cout << "The sorted array: " << endl;
        for (int i = 0; i < number_of_lines; i++) {
            cout << p[i] << endl;
        }
    }
    
}

