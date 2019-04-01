
#include <iostream>     //including I/O support
#include <fstream>      //including file I/O support
#include <vector>		//including support of vector container
#include <string>		//including the new C++ string class support
#include <cstring>		//including old C character array support
						//	to read one char at a time from user input
#include "lexScanner.h"	//
#include "interface.h"	//
using namespace std;

// 1. Read in a program (lines of statements) from a file
void Interface::loadProgramFromFile()
{
	char fileName[MaxLengthFileName];	
	// this char array stores the name of the file the program reads from.

	cout<<"Name of file to upload program from (ex. file.txt): ";
	cin >> fileName;
	while( strlen(fileName) == 0 )
		cin >> fileName;

	ifstream inFile;
	inFile.open( fileName );
	if ( inFile.fail() )
	{ cout << endl << "Cannot open this file!" << endl;
	return;
	}

    
	lines.clear();  //Delete all the lines of statements
	string inputBuffer;
	while( !inFile.eof() )
	{
		getline(inFile, inputBuffer);
		while( !inFile.eof() && inputBuffer.size() == 0 )
			getline(inFile, inputBuffer);

		if (!inFile.eof())
		{
  			cout<< "Line["
				<< lines.size()
				<< "] read:"
				<< inputBuffer << endl;
			lines.push_back(inputBuffer);
		}

	}


	inFile.close();
}



// 2. Display the lines of statements
void Interface::displayProgram()
{
	for (int i = 0; i<lines.size(); i++)
		cout << "[" << i << "]: " << lines[i] << endl;
}



// 3. Enter new lines of code to the end of the program
void Interface::appendLines()
{
	cout << "Keep reading and appending lines of statements you enter to the end of the program until a single period is entered as a line." << endl;
    
	double i = lines.size();
    string temp;
    bool running=true;
    
	while (running == true)
	{
		cout << "[" << i << "]: ";
        
        getline(cin, temp);
        
        while (temp.empty())
            getline(cin, temp);
        
        if (temp==".")
            running=false;
            else
                
          lines.push_back(temp);
        
		i++;
	}
    
	cout << "Total number of lines: " << lines.size(); 
	cout << "The soruce code numbered in lines" << endl;

	displayProgram();
}

// 4. Insert new lines after an existing line
void Interface::insertLines()
{
    int lineIndex=0;
    bool running=true;
    vector <int>::iterator lines_Iter;
    
    cout << "Before which line <tell us the line #> do you want to insert a new line?" << endl;
    cin >> lineIndex;
    
    if (lineIndex > lines.size() || lineIndex < 0)
        cout << "Unable to do it. There is no line " << lineIndex << endl;
    
    else
    {
        cout << "We'll keep reading and inserting lines of staements you enter until a single period is entered as a line." << endl;
        
            while (running == true)
            {
                string temp;
                cout << "[" << lineIndex << "]: ";
                
                getline(cin, temp);

                while (temp.empty( ) )
                    getline(cin, temp);
                
                if (temp == ".")
                    running = false;
                
                else
                    lines.insert(lines.begin()+lineIndex, temp);
                
                lineIndex=lineIndex+1;
            }
        
        cout << "Total number of lines: " << lines.size();
        cout << "The soruce code numbered in lines" << endl;
        
        displayProgram();
    }
}
    
    



// 5. Delete a range of existing line
void Interface::deleteLines()
{
    int BegLine=0, EndLine=0;
    cout << "What lines do you want to delete?" << endl;
    cout << "From #: " << endl << endl;
    cin >> BegLine;
    
    cout << "to line #: " << endl << endl;
    cin >> EndLine;
    
    if (BegLine-EndLine==0)
        lines.erase(lines.begin()+BegLine);

    else
        lines.erase(lines.begin()+BegLine, lines.begin()+EndLine+1);
}



// 6. Replace the contents of an existing line
void Interface::replaceOneLine()
{
    int tempLineIndex=0;
    
    cout << "Which lines do you want to replace?" << endl;
    cin >> tempLineIndex;
    
    cout << "Enter new contents into line " << tempLineIndex << endl;
    
    string tempLine;
    
    cin.ignore();
    getline (cin, tempLine);
    
    cout << endl << endl;
    
    lines[tempLineIndex]=tempLine;
    
    cout << "Total number of lines: " << lines.size() << endl;
    cout << "The soruce code numbered in lines" << endl;
    
    displayProgram();
}


// 7. Save program to a file
void Interface::saveProgramIntoFile()
{
    string fileName;
    cout << "Name of file to save the program to <ex. file.txt>: " << endl;
    cin >> fileName;
    
    ofstream outFile;
    outFile.open(fileName);
    
    for (int i=0; i<lines.size(); i++)
        outFile << lines[i] << endl;
    
    outFile.close();
    
    cout << "Totally " << lines.size() << " lines of code saved."  << endl;
}

//An auxilliary message displaying function
void Interface::endOfService(const string service)
{
    char temp;
	cout<<endl << service << " done." << endl << "Press any key to continue.";
    cin >> temp;
    cout << endl;
	cout << "****************************************************" <<endl<< endl;
}

// This menu() function is the interface
void Interface::startInterface() {

	// "Then I suppose now is the time for me to say something profound....
	// Nothing comes to mind. Let's do it."

	bool inMenu = true;	// while the user is using the program this var is set to true and the menu keeps looping.
						// when the user wants to quit, it is set to false and the loop ends.
	char keyPressed;	// This var stores which menu selection the user picks.
	
	vectOfTokenVects myVectOfTokenVects;
	vectOfCategoryVects myVectOfCategoryVects;

	while ( inMenu )
	{
		cout<< endl << endl << endl;
		cout << "****************************************************" << endl;
		cout  <<"**  MENU:(press a character to select an option)  **" << endl;
 		cout << "****************************************************" << endl;
		cout<<"Q. [QUIT]     Quit."<<endl;
		cout<<"L. [LOAD}     Read in a program (lines of statements) from a file"<<endl;
  		cout<<"S. [SAVE]     Save lines of statement as a program into a file"<<endl;
		cout << endl;

		cout<<"D. [DISPLAY]  Display the source code as lines of statements"<<endl;
		cout << endl;

		cout<<"A. [APPEND]   Append new lines to the end of the program"<<endl;
		cout<<"I. [INSERT}   Insert new lines before an existent line"<<endl;
		cout<<"X. [DELETE]   Delete a range of existent lines"<<endl;
		cout<<"R. [REPLACE]  Replace the contents of an existent line"<<endl;
		cout << endl;

		cout<<"P. [PARSE]    Parse and ident the code" << endl;
		cout<<"E. [EXECUTE]  Execute (run) the program"<<endl;
		cout<<"T. [TOGGLE]   Toggle the execution debug mode"<<endl;
		cout << "W. [Lexical Analysis]  Analysis of all lines of statements" << endl;

		cout << "****************************************************" <<endl<< endl;

		cout<<"Your choice is: ";
        
        cin >> keyPressed;
        cout<< keyPressed << endl;

		switch (keyPressed) {
		case 'Q': case 'q'://Quit
			cout << "[QUIT]:" << endl;
			inMenu = false;
			break;

		case 'L': case 'l':// 1. Read in a program (lines of statements) from a file
 			cout << "[LOAD PROGRAM]:" << endl;
			loadProgramFromFile();
			endOfService("[LOAD PROGRAM]");
			break;

		case 'D': case 'd':// 2. Display the lines of statements
			cout << "[DISPLAY PROGRAM]:" << endl;
			displayProgram();
			endOfService("[DISPLAY PROGRAM]");
			break;

		case 'A': case 'a':// 3. Append new lines of code to the end
			cout << "[APPEND]:" << endl;
			appendLines();
			endOfService("[APPEND LINES]");
			break;

		case 'I': case 'i':// 4. Insert a new line after an existing line
			cout << "[INSERT LINES]:" << endl;
			insertLines();
			endOfService("[INSERT LINES]");
			break;

		case 'X': case 'x':// 5. Delete an existing line
			cout << "[DELETE LINES]:" << endl;
			deleteLines();
			endOfService("[DELETE LINES]");
			break;

		case 'R': case 'r':// 6. Replace the contents of an existing line
			cout << "[REPLACE]:" << endl;
			replaceOneLine();
			endOfService("[REPLACE ONE LINE]");
			break;

		case 'S': case 's':// 7. Save program to a file
			cout << "[SAVE]:" << endl;
			saveProgramIntoFile();
			endOfService("[SAVE CODE INTO A FILE]");
			break;

		case 'P': case 'p':// 8. Parse and Indent the program
			cout << "[PARSE AND INDENT SOURCE CODE]:" << endl;
			endOfService("[PARSE AND INDENT SOURCE CODE]");
			break;

		case 'W': case 'w':// Toggle the debug mode
			cout << "[Lexical Analysis]: " << endl;

			//Get the lexical information 
			LexicalScanner::getLexicalInfo(lines, myVectOfTokenVects, myVectOfCategoryVects);

			//Display the lexical information 
			LexicalScanner::displayLexicalInfo(myVectOfTokenVects, myVectOfCategoryVects);
			
			// clear both of these vectors
                myVectOfTokenVects.clear();
                myVectOfCategoryVects.clear();
                
			break;

		case 'E': case 'e':// 9. Run program
			cout << "[EXECUTE TO RUN PROGRAM]:" << endl;
			endOfService("[EXECUTE TO RUN PROGRAM]");
			break;

		case 'T': case 't':// Toggle the debug mode
			cout << "[TOGGLE the debug mode]:" << endl;
			break;

		default:
			cout << "[?? UNKNOWN COMMAND]:" << endl;
			// Unrecognized key, do nothing
			break;
		}

	} // End of while loop.
}
