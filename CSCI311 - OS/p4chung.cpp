#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>


using namespace std;

struct myPage{
    int frameNumber;
};

struct myFrame{
    int pageNumber;
    int iterLastAccessed;
};

// Arrays
myPage pageTable[16];
myFrame frameTable[8];
char physicalMemory[8][256];

// Addresses file and masks
FILE *addresses = fopen("addresses.txt", "r");
unsigned pageNumberMask = 65280, offsetMask = 255;

int main() {
    
    // Variables
    double pageFaultRate=0, faultCount=0;
    int virtualAddress=0, addressCount=0, pageNumber=0, offset=0, hit=1, baseTime=10, indexLRU=0, indexHit=0, indexFreeFrame=0, itNumber=0, temp=0;
    bool isEmpty=true;
    
    // File part
    ifstream inFile;
    inFile.open("BACKING_STORE.bin");//open the file
    
    // initialize page table & frame table
    for (int i=0; i<16; i++){
        pageTable[i].frameNumber=-1;
    }
    
    for (int i=0; i<8; i++){
        frameTable[i].pageNumber=-1;
    }

    // loop to obtain inputs
    while(fscanf(addresses, "%d", &virtualAddress) == 1) {

        isEmpty=false;
        hit=-1; addressCount++; baseTime=10; indexLRU=0;
        
        // Get page number and offset from the integer
        pageNumber = (virtualAddress & pageNumberMask) >> 8;
        offset = virtualAddress & offsetMask;
        
        // check for hit
        for (int i=0; i<8; i++){
            if (frameTable[i].pageNumber==pageNumber){
                hit=1;
                indexHit=i;
            }
        }
        
        // check for empty
        for (int i=0; i<8; i++){
//            cout << frameTable[i].pageNumber << " ";
            if (frameTable[i].pageNumber==-1){
                isEmpty=true;
                indexFreeFrame=i;
                break;
            }
        }
        
        cout << endl;

//        cout << "Hit: " << hit << endl;
//        cout << "isEmpty: " << isEmpty << endl;
        
        // Got a hit
        if (hit==1){
            
            // Page 12 is contained in frame 6 must be printed.
            for (int i=0; i<8; i++){
                if(frameTable[i].pageNumber==pageNumber){
                    frameTable[i].iterLastAccessed=itNumber;
                }
            }
            
            cout << "Virtual Address " << virtualAddress << " is contained in frame " << indexHit << endl;
        }
        
        // No hit; FAULT OCCURRED
        else if (hit==-1){
            
            // If there are free fames
            if (isEmpty==true){
                
                cout << "Virtual address " << virtualAddress << " contained in page " << pageNumber << " causes a page fault" << endl;
                cout << "Page " << pageNumber << " is loaded into frame " << indexFreeFrame << endl;
                
                // Allocations
                frameTable[indexFreeFrame].iterLastAccessed=itNumber;
                frameTable[indexFreeFrame].pageNumber=pageNumber;
                pageTable[pageNumber].frameNumber=indexFreeFrame;

                // Bin
                inFile.seekg(pageNumber * 260 - (!pageNumber) * 2, inFile.beg);
                for (int i = 0; (i<256) && (inFile >> physicalMemory[indexFreeFrame][i]); i++) {}
                
            }
            
            // If there are no free frames; we have to use LRU
            else if (isEmpty==false){
                
                baseTime=frameTable[0].iterLastAccessed;
                
                // Check with the longest duration
                for(int i=0; i<8; i++){
                    
//                    cout << frameTable[i].iterLastAccessed << " -- ";
                    
                    if (frameTable[i].iterLastAccessed < baseTime){
                        baseTime=frameTable[i].iterLastAccessed;
                        indexLRU=i;
                    }
                }
                
                // Allocations
                frameTable[indexLRU].iterLastAccessed=itNumber;
                temp = frameTable[indexLRU].pageNumber;
                frameTable[indexLRU].pageNumber=pageNumber;

                pageTable[temp].frameNumber=-1;
                pageTable[pageNumber].frameNumber=indexLRU;

                cout << "Virtual address " << virtualAddress << " contained in page " << pageNumber << " causes a page fault" << endl;
                cout << "Page " << pageNumber << " is loaded into frame " << indexLRU << endl;

                // Bin
                inFile.seekg(pageNumber * 260 - (!pageNumber) * 2, inFile.beg);
                for (int i = 0; (i<256) && (inFile >> physicalMemory[indexLRU][i]); i++) {}
            }
            
            inFile.close();
            faultCount++;
        }
        
        itNumber++;
        cout << "---------------- ";
    }
    
    // Disply contents of pageTable
    cout << endl;
    cout << "The contents of page table after simulation: " << endl;
    for (int i=0; i<16; i++){
        if (pageTable[i].frameNumber==-1){
            cout << "Page " << i << ": -- " << endl;
        }
        else{
            cout << "Page " << i << ": " << pageTable[i].frameNumber << endl;
        }
    }

    // Display contents of frameTable
    cout << "---------------- " << endl;
    cout << "Contents of Memory After Simulation" << endl;
    for (int i=0; i<8; i++){
        cout << "Frame " << i << ": " << frameTable[i].pageNumber << endl;
    }
    
    // Display page fault rate
    cout << "---------------- " << endl;
    pageFaultRate=faultCount/itNumber;
    cout << "The reference string generated " << faultCount << " page faults in memory with page fault rate (" << faultCount << "/" << itNumber << ") = " << pageFaultRate << endl;
    
    return 0;
}
