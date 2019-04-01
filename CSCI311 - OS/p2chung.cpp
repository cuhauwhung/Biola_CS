#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

int number_of_elements;
int unsortedArray[21], sortedArray[21];

struct myInfo{
    int begin;
    int end;
};

// Sorting function
void *sort(void *param){
    
    myInfo pointsTemp = *(myInfo *) param;
    
    // Sort according to the input.
    for (int i = pointsTemp.begin; i<pointsTemp.end-1; i++){
        int min = i;
        for (int j = i+1; j< pointsTemp.end; j++)
            if (unsortedArray[j] < unsortedArray[min]) min = j;
        int temp = unsortedArray[i];
        unsortedArray[i] = unsortedArray[min];
        unsortedArray[min] = temp;
    }
    
    pthread_exit(0);
}

// Merging function
void *merge(void *param){

    int i = 0, j = number_of_elements/2, k = 0;
    
    // Compare both unsorted Arrays and place into sorted
    while (i < (number_of_elements/2) && j < number_of_elements){
        if (unsortedArray[i] < unsortedArray[j])
            sortedArray[k++] = unsortedArray[i++];
        else
            sortedArray[k++] = unsortedArray[j++];
    }
    
    // Merge remaining elements into sorted Array
    while (i < number_of_elements/2)
        sortedArray[k++] = unsortedArray[i++];
    
    while (j < number_of_elements)
        sortedArray[k++] = unsortedArray[j++];
    
    pthread_exit(0);
}

int main()
{
    ifstream inFile("p2data.txt");
    int i=0, content;
    string line;
    bool is_even;

    if(!inFile){
        // print an error
        cout << "Could not be opened for writing!.\n";
        cout << "Program is going to exit.\n";
        return 1;
    }
    
    else {
        
        while (getline(inFile, line))
            ++number_of_elements;
        
        // if file is empty
        if (number_of_elements == 0) {
            cout << "This file is empty.\n";
            cout << "This program is going to exit.\n";
            exit(1);
        }
    }
    
    // check to see if number of lines is power of 2
    if (number_of_elements%2==0)
        is_even = true;
    else
        is_even = false;
    
    if (is_even==false){
        cout << "There is not an even number of elements in the file.\n";
        exit(1);
    }
    
    else {
        
        // Obtain inputs
        inFile.close(); inFile.clear();
        inFile.open("p2data.txt");
        
        while (inFile >> content) {
            unsortedArray[i] = content;
            i++;
        }
        
        inFile.close();
    }
    
    // Input from file
    cout << "Input from File.\n";
    for (int i=0; i<number_of_elements; i++){
        cout << unsortedArray[i] << "\n";
    }

    // Values
    myInfo valA, valB;
    valA.begin = 0;
    valA.end = number_of_elements/2;
    
    valB.begin = number_of_elements/2;
    valB.end = number_of_elements;
    
    // Thread section
    pthread_t threadA, threadB, threadC;
    
    // First two are for sorting
    pthread_create(&threadA, NULL, sort, (void*) &valA);
    pthread_join(threadA,NULL);
    
    pthread_create(&threadB, NULL, sort, (void*) &valB);
    pthread_join(threadB,NULL);
    
    // Last one is for merging
    pthread_create(&threadC, NULL, merge, (void*) NULL);
    pthread_join(threadC,NULL);
    
    // Output
    cout << endl;
    cout << "Output after sort and merge:\n";
    for (int i=0; i<number_of_elements; i++){
        cout << sortedArray[i] << "\n";
    }
    
    cout << endl;
}




