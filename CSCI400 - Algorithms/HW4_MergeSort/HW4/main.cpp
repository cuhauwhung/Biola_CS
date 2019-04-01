//  main.cpp
//  HW4
//
//  Created by Cu Hauw Hung on 10/5/17.
//  Copyright © 2017 Cu Hauw Hung. All rights reserved.
//

using namespace std;
#include <iostream>
#include <fstream>
#include <new>
#include <string>

// power of 2 function
int pow2roundup (int x)
{
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

void merge(int h, int m, int *u, int *v, int *s){
    int i=0, j=0, k=0;
    
    while (i<h && j<m){
        
        if(u[i]<=v[j]){
            s[k]=u[i];
            i++;
        }
        
        else {
            s[k]=v[j];
            j++;
        }
        k++;
    }

    if (i>=h){
        while (j<m){
            s[k]=v[j];
            j++; k++;
        }
    }
    
    else{
        while (i<h){
            s[k]=u[i];
            i++; k++;
        }
    }

}

void mergeSort(int n, int*s){

    int i=0, h,m, temp1=0, temp2=0;

    if (n>1){
        h=n/2; m=n-h;
        
        int *u = new int[h];
        int *v = new int[m];
    
        while (i<=n){
            if (i<h){
                u[temp1]=s[i]; temp1++;
            }
            else{
                v[temp2]=s[i]; temp2++;
            }
            i++;
        }

        // run mergesort and merge recursibely
        mergeSort(h, u);
        mergeSort(m, v);
        merge(h,m,u,v,s);

    }
}

int main(){

    int i=0, content=0, number_of_lines=0, count=0, temp=0;
    int *p;
    bool is_power_of_two=false;
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

		// check to see if number of lines is power of 2
		if (number_of_lines & ((number_of_lines - 1) == 0))
			is_power_of_two = true;
		else
			is_power_of_two = false;

		// check to see largest power of 2 above number_of_lines
		if (is_power_of_two == false) {
			temp = pow2roundup(number_of_lines);
		}

		// close and open file
		myfile.close(); myfile.clear();
		myfile.open("p1data.txt");

		// create an array with power of 2
		p = new (nothrow) int[temp];

		// start moving contents into array
		while (myfile >> content) {
			p[i] = content;
			i++;
		}

		// close file
		myfile.close();

		// fill remaining of array with 0
		for (int start = number_of_lines; start <= temp; start++)
			p[start] = 0;


		// Output
		cout << "The created array: " << endl;
		for (int i = 0; i < temp; i++) {
			cout << p[i] << endl;
		}

		// perform mergesort
		mergeSort(temp, p);

		// Output
		cout << "The sorted array: " << endl;
		for (int i = 0; i < temp; i++) {
			if (p[i]!=0)

				cout << p[i] << endl;
		}
	}

	system("pause");

}
