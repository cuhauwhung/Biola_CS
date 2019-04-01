//
//  main.cpp
//  4
//
//  Created by Willy Hung on 3/14/16.
//  Copyright  2016 Willy Hung. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

bool works = true;
bool mergeTwoSortedSeries(double * ptrA, int sizeOfA, double * ptrB, int sizeOfB, double * ptrC)
{
    
    // PRECONDITIONS
    // check precondition 1
    // it is checked in the main function
    
    // check precondition 2
    if (sizeOfA<0 || sizeOfB<0)
    {
        return false;
    }
    
    // check precondition 3 (ASECNDING ORDER)
    //Two ways to compare
    for (int i = 0; i<sizeOfA - 1; i++)
    {
        
        if (ptrA[i] > ptrA[i + 1])
        {
            cout << "First Series Is Not Sorted" << endl;
            works = false;
            return false;
        }
        
    }
    
    for (int i = 0; i<sizeOfB - 1; i++)
    {
        if (*ptrB + i > *ptrB + i + 1)
        {
            cout << "Second Series Is Not Sorted" << endl;
            works = false;
            return false;
        }
        
    }
    
    // start with the sorting
    int countA = 0, countB = 0, countC = 0;
    bool combine1 = true, combine2 = true;
    
    // keep running until the elements in both serieses are compared
    while (combine1 == true)
    {
        
        // if the count is equal to size, which means it reached the end, then break
        if (countB == sizeOfB || countA == sizeOfA)
        {
            break;
        }
        
        // check whichvever is less, then insert the less integer to the new vector
        if (ptrA[countA] <= ptrB[countB])
        {
            ptrC[countC] = ptrA[countA];
            countC++;
            countA++;
        }
        
        else if (ptrA[countA]>ptrB[countB])
        {
            ptrC[countC] = ptrB[countB];
            countC++;
            countB++;
        }
    }
    
    // if the one vector reaches the end, then copy the remaining values in the other vector to the new vector.
    if (sizeOfA == countA)
    {
        while (combine2 == true)
        {
            if (countC == sizeOfA + sizeOfB)
            {
                break;
            }
            
            ptrC[countC] = ptrB[countB];
            countC++;
            countB++;
        }
    }
    
    // if the one vector reaches the end, then copy the remaining values in the other vector to the new vector. SAME AS TOP
    else if (sizeOfB == countB)
    {
        while (combine2 == true)
        {
            if (countC == sizeOfA + sizeOfB)
            {
                
                break;
                
            }
            
            ptrC[countC] = ptrA[countA];
            countC++;
            countA++;
        }
        
    }
    
    
    return 1;
}

// MERGESORT section
void mergeSort(double * ptrSeriesToSort, int sizeOfSeries)
{
    
    // if size is negative then retun
    if (sizeOfSeries<0)
    {
        return;
    }
    
    // if size is one then return
    else if (sizeOfSeries == 1)
    {
        return;
    }
    
    // if size is 2 then swap the two values
    else if (sizeOfSeries == 2)
    {
        
        if (ptrSeriesToSort[0]>ptrSeriesToSort[1])
        {
            int temp = ptrSeriesToSort[0];
            ptrSeriesToSort[0] = ptrSeriesToSort[1];
            ptrSeriesToSort[1] = temp;
            
        }
    }
    
    else if (sizeOfSeries>2)
    {
        // split the big vetor to two smaller vectors
        double *ptrSeries1, *ptrSeries2;
        ptrSeries1 = new double[sizeOfSeries / 2];
        ptrSeries2 = new double[sizeOfSeries - (sizeOfSeries / 2)];
        int w = 0;
        
        // transfer the values from the big vetor to the two smaller ones
        for (int i = 0; i<(sizeOfSeries / 2); i++)
        {
            ptrSeries1[i] = ptrSeriesToSort[w];
            w++;
        }
        
        for (int i = 0; i<(sizeOfSeries - (sizeOfSeries / 2)); i++)
        {
            ptrSeries2[i] = ptrSeriesToSort[w];
            w++;
        }
        
        // call the mergesort to sort the split smaller vectors
        mergeSort(ptrSeries1, (sizeOfSeries / 2));
        mergeSort(ptrSeries2, (sizeOfSeries - (sizeOfSeries / 2)));
        
        // merge the two sorted vectors, which were split from the big vector
        mergeTwoSortedSeries(ptrSeries1, (sizeOfSeries / 2), ptrSeries2, (sizeOfSeries - (sizeOfSeries / 2)), ptrSeriesToSort);
        
        // delete allocated memory
        delete[] ptrSeries1;
        delete[] ptrSeries2;
        
    }
    
}

int main()
{
    bool running1=true;
    bool running2=true;
    
    while (running1==true)
    {
        cout << "******************************" << endl;
        cout << "STARTING MergeToSort SECTION" << endl;
        
        // delcare variables
        int n1, n2;
        
        // set the size of n1
        cout << "Please enter two non-negative integers for the sizes of the two vectors" << endl;
        cout << "Vector 1 Size: ";
        cin >> n1;
        
        // end program if n1 < 0
        if (n1<0 || n2<0)
        {
            cout << "Ending MergeToSort..." << endl;
            break;
        }
        
        // Set the size of n2
        cout << "Vector 2 Size: ";
        cin >> n2;
        
        // declare variables and dynamic memory allocation
        double *ptrA, *ptrB, *ptrC;
        ptrA = new double[n1];
        ptrB = new double[n2];
        ptrC = new double[n1 + n2];
        
        // Input elements
        cout << "Input elements for the first vector" << endl;
        for (int i = 0; i<n1; i++)
        {
            cout << "Element " << i + 1 << " :";
            cin >> ptrA[i];
        }
        
        cout << "Input elements for the second vector " << endl;
        for (int i = 0; i<n2; i++)
        {
            cout << "Element " << i + 1 << " :";
            cin >> ptrB[i];
        }
        
        // CHECK PRECONDITION
        // Precondition 1 is fulfilled already
        mergeTwoSortedSeries(ptrA, n1, ptrB, n2, ptrC);
        
        if (works == false)
        {
            
        }
        
        else if (works == true)
        {
            // output for new sorted vector
            cout << "The merged series: " << endl;
            for (int i = 0; i<n1 + n2; i++)
            {
                cout << "Element #" << i + 1 << ": " << ptrC[i] << endl;
            }
        }
        
        delete[] ptrA;
        delete[] ptrB;
    }
    

    while (running2==true)
    {
        cout << "******************************" << endl;
        cout << "STARTING MERGESORT SECTION" << endl;
        //NEW SECTION
        int sizeOfSeries;
        cout << "What is the size of the series?" << endl;
        cin >> sizeOfSeries;
        
        if (sizeOfSeries<0)
        {
            cout << "Ending Program..." << endl;
            return 1;
        }
        
        // delcare new pointer series
        double *ptrSeriesToSort;
        ptrSeriesToSort = new double[sizeOfSeries];
        
        // enter desired elements
        cout << "Please enter the elements you want to sort" << endl;
        for (int i = 0; i <sizeOfSeries; i++)
        {
            cout << "Element#" << i + 1 << ": ";
            cin >> ptrSeriesToSort[i];
        }
        
        // perform the mergesort)
        mergeSort(ptrSeriesToSort, sizeOfSeries);
        
        cout << "The New Sorted Series: " << endl;
        for (int i = 0; i<sizeOfSeries; i++)
        {
            cout << "Element #" << i + 1 << ": " << ptrSeriesToSort[i] << endl;
        }
        
        // delete dynamically allocated memory
        delete[] ptrSeriesToSort;
    }
    
}