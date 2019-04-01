//
//  main.cpp
//  Programming 3
//
//  Created by Willy Hung on 3/11/16.
//  Copyright © 2016 Willy Hung. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool one=true, two=true;

bool mergeTwoSortedVectors (vector<double> & vecA, vector<double> & vecB, vector<double> & vecC)
{
    // declare variables
    int countA = 0, countB = 0, countC = 0;
    bool combine1 = true, combine2 = true;
    
    // make sure the two vectors are in order
    // check if A is in order
    for (int i = 0; i<vecA.size() - 1; i++)
    {
        if ((vecA[i]>vecA[i + 1]))
        {
            one=false;
            return false;
        }
    }
    
    // check if B is in order
    for (int i = 0; i<vecB.size() - 1; i++)
    {
        if ((vecB[i]>vecB[i + 1]))
        {
            two=false;
            return false;
        }
    }
    
    
    
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
void mergeSort(vector<double>&vecToSort)
{
    // for 1 just return
    if (vecToSort.size() == 1)
    {
        return;
    }
    
    // for 2, just swap elements
    if (vecToSort.size() == 2)
    {
        if (vecToSort[0]>vecToSort[1])
        {
            int temp = vecToSort[0];
            vecToSort[0] = vecToSort[1];
            vecToSort[1] = temp;
        }
        
    }
    
    // greater than 2
    if (vecToSort.size()>2)
    {
        vector <double> vec1;
        vector <double> vec2;
        
        // resize the big to two smaller vectors
        vec1.resize(vecToSort.size() / 2);
        vec2.resize(vecToSort.size() - vecToSort.size() / 2);
        
        int w = 0;
        
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
    
}

int main()
{
    vector <double> vecA, vecB, vecC;
    
    int ai, bi;
    // Set the size of A
    cout << "Please enter the sizes of the two vectors" << endl;
    cout << "Vector 1 Size: ";
    cin >> ai;
    vecA.resize(ai);
    
    // Set the size of B
    cout << "Vector 2 Size: ";
    cin >> bi;
    vecB.resize(bi);
    
    // resieze vecC into the sizes of A and B
    vecC.resize(vecB.size() + vecA.size());
    
    if (ai<0 || bi<0)
    {
        return 0;
    }
    
    // Input values for vector A
    cout << "Please enter values in the first vector." << endl;
    for (int i = 0; i<vecA.size(); i++)
    {
        cout << "Element #" << i + 1 << ": ";
        cin >> vecA[i];
    }
    
    // Input values for vector B
    cout << "Please enter values in the second vector." << endl;
    for (int i = 0; i<vecB.size(); i++)
    {
        cout << "Element #" << i + 1 << ": ";
        cin >> vecB[i];
    }
    
    // perform function call
    mergeTwoSortedVectors(vecA, vecB, vecC);
    
    // if first vector is not in order display:
    if (one==false)
    {
        cout << "The first vector is not in ascending order" << endl;
    }
    
    // if secon vector is not in order display:
    else if (two==false)
    {
        
        cout << "The second vector is not in ascending order" << endl;
    }
    
    // if both are in order just cout the vector
    else
    {
        // Output values for vector C
        cout << "The merged vector: " << endl;
        for (int i = 0; i<vecC.size(); i++)
        {
            cout << "Element #" << i + 1 << ": " << vecC[i] << endl;
        }
    }

    // series sorting
    cout << "SERIES SORTING" << endl;
    cout << "Please enter sizes of the vector to be sorted" << endl;
    
    //merge sort section
    vector <double> vector;
    int n;
    
    cout << "What is the vector size?" << endl;
    cin >> n;
    vector.resize(n);
    
    cout << "Please enter the elements you want to sort" << endl;
    for (int i = 0; i<vector.size(); i++)
    {
        cout << "Element #" << i + 1 << ": ";
        cin >> vector[i];
    }
    
    // perform the mergesort
    mergeSort(vector);
    
    // cout new sorted vector
    cout << "New Sorted Vector: " << endl;
    
    for (int i = 0; i<vector.size(); i++)
    {
        cout << "Element #" << i + 1 << ": " << vector[i] << endl;
    }
    
    char quit;
    cout << "Enter X to Quit" << endl;
    cin >> quit;
    
    if (quit=='x')
    {
        return 0;
    }
    
}
