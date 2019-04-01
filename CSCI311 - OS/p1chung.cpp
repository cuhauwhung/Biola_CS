
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{

    cout << "Welcome to the Linux Shell" << endl;
    
    // Declarations
    char line[82];
    char *token;
    
    while (1) {
        
        // Declarations
        char *args[30];
        int count=0;

        // Get input from the user
        printf("# ");
        cin.getline(line, 82);
        
        if (strlen(line) > 80){
            cout << "Error, input-string too large\n" << endl;
            continue;
        }
        
        if (strcmp(line, "exit") == 0)
            exit(0);
        
        // Parse the input from the user
        token = strtok(line, " ");
        
        // Place the input from the user into
        while (token != NULL){
            
            args[count] = token;
            count++;
            token = strtok(NULL, " ");
        }
        
        // Last place as NULL
        args[count] = NULL;

//        cout << "Last count: " << count << endl;

//        int x = 0;
//        while (args[x]!=NULL){
//            cout<<args[x]<<endl;
//            x++;
//        }
        
        // Fork
        int pid = fork();

        // Error
        if (pid < 0){
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }

        // Child proces
        else if (pid == 0){
            execvp(args[0], args);
            printf("Exec failed\n");
            exit(0);
        }

        // Parent process
        else {
            wait(NULL);
        }
    
    }
}



