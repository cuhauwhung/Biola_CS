//
//  main.cpp
//  HW7_Path
//
//  Created by Cu Hauw Hung on 11/9/17.
//  Copyright © 2017 Cu Hauw Hung. All rights reserved.
//

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <new>
#include <string>
#include <algorithm>
#include <vector>

int weight;
void floyd2(int n, int (&w)[10][10], int (&d)[10][10], int (&p)[10][10]){
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            p[i][j]=0;
        }
    }
    
    for (int i=0; i<10; i++){
        for (int j=0; j<n; j++){
            d[i][j]=w[i][j];
        }
    }
    
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                cout << "d[" << i << "][" << k << "]=" << d[i][k] << "+";
                cout << "d[" << k << "][" << j << "]=" << d[k][j] << " ----- ";
                cout << "d[" << i << "][" << j << "]=" << d[i][j] << endl;

                if (d[i][k]+d[k][j]<d[i][j]){
                    cout << "---- YES " << endl;
                    p[i][j]=k+1;
                    d[i][j]=d[i][k]+d[k][j];
                }
            }
        }
    }
}

void path(int q, int r, int p[10][10], int d[10][10]){
    if(p[q-1][r-1]!=0){
        path(q, p[q-1][r-1], p, d);
        cout << "V" << p[q-1][r-1] << " -> ";
        weight=d[q-1][r-1];
        path(p[q-1][r-1], r, p, d);
    }
}

void OutputValues(int d[10][10], int matrixsize){
    for (int i=0; i<matrixsize; i++){
        for (int j=0; j<matrixsize; j++){
            cout << d[i][j] << " ";
        } cout << endl;
    }
}

int main(){

    int w[10][10], d[10][10], p[10][10],content, i=0, j=0, q, r, matrixsize=0;
    string line;
    
    ifstream myfile("hw7in.txt");
    
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
            ++matrixsize;
        
        // if file is empty
        if (matrixsize == 0) {
            cout << "This file is empty" << endl;
            cout << "This program is going to exit" << endl;
            system("pause");
            exit(1);
        }
        
        // close and open file
        myfile.close(); myfile.clear();
        myfile.open("hw7in.txt");

        // start moving contents into array
        while (myfile >> content) {
            w[i][j] = content;
            j++;
            
            if (j==matrixsize){
                j=0;
                i++;
            }
        }
        myfile.close();
    }
    
    cout << "Program starts running" << endl;
    cout << "This is the inputted matrix" << endl;
    OutputValues(w, matrixsize);
    cout << "----------------------------" << endl;
    floyd2(matrixsize, w, d, p);
    cout << "Following shows the P and D matrix respectively" << endl;
    OutputValues(d, matrixsize);
    cout << "----------------------------" << endl;
    OutputValues(p, matrixsize);
    
    char temp='Y';
    
    do{
        cout << "Enter source and destination vertex" << endl;
        cin >> q;
        cin >> r;
        
        cout << "V" << q << " -> ";
        path(q, r, p, d);
        cout << "V" << r << " with the weight: " << weight << endl;

        cout << "Another path? (Y/N)" << endl;
        
        cin >> temp;
        
    } while(temp=='Y' || temp=='y');
}


