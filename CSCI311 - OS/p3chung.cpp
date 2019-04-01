#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <mutex>
#include <iostream>

using namespace std;
#define BUFFER_SIZE 10

// Two general semaphores and binary mutex
sem_t empty, full;
pthread_mutex_t mutexA, mutexB;

// thread ID and attributes
pthread_t tidA, tidB;
pthread_attr_t attrA, attrB;

// initializations
int buffer[BUFFER_SIZE];
int in=0, out=0;

int insert_item (int item){
    pthread_mutex_lock(&mutexA);
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutexA);
    return 0;
}

int remove_item(int *item){
    pthread_mutex_lock(&mutexB);
    *item = buffer[out];
    buffer[out] = 0;
    out = (out+1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutexB);
    return 0;
}

void *producer(void *param) {
    
    int item;
  
    while(true) {
        
        // Sleep for random number of time
        int sleepTime = rand() % 4;
        sleep(sleepTime);
        
        // Create random number
        item = rand() % 21;
        
        // wait empty
        sem_wait(&empty);
        
        // Display
        if(insert_item(item)){
            cout << "report error condition -- Producer" << endl;
        }
        
        else {
            cout << "producer (" << tidA << ") produced " << item << " in buffer " << in << endl;
        }
        
        // signal full
        sem_post(&full);
    }
}

void *consumer(void *param) {
    
    int item;

    while(true) {

        // sleep
        int sleepTime = rand() % 4;
        sleep(sleepTime);

        // wait full
        sem_wait(&full);

        // Display
        if (remove_item(&item)){
            cout << "report error condition -- Consumer" << endl;
        }

        else{
            cout << "consumer (" << tidB << ") consumed " << item << " from buffer " << out << endl;
        }

        // signal empty
        sem_post(&empty);
    }
}

int main(){

    // initialize variables
    int numSeconds, numProd, numCons;
    
    // initialize mutexes
    pthread_mutex_init(&mutexA, NULL);
    pthread_mutex_init(&mutexB, NULL);
    
    // initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    
    // Get default attributes
    pthread_attr_init(&attrA);
    pthread_attr_init(&attrB);

    // obtain input from user
    cout << "Enter the number of seconds for the main() function to sleep: " << endl;
    cin >> numSeconds;

    cout << "Enter the number of producter threads" << endl;
    cin >> numProd;
    
    cout << "Enter the number of consumer threads: " << endl;
    cin >> numCons;
    
    // Create producer threads
    for(int i = 0; i < numProd; i++) {
        pthread_create(&tidA,&attrA,producer,NULL);
    }
    
    // Create consumer threads
    for(int i = 0; i < numCons; i++) {
        pthread_create(&tidB,&attrB,consumer,NULL);
    }
    
    // Sleep
    sleep(numSeconds);
    
    // Exit
    exit(0);
}
