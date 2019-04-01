#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "models.h"
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;


//******************************************************************************
//******************************************************************************
//
//  Parameter setting for the storage capacity
//
//******************************************************************************
//******************************************************************************

//The maximum capacity (maximum number of characters allowed)
//		for the storing the vocabulary set
#define VocabularyStorageLimit 20000

//The maximum capacity (maximum number of characters allowed)
//		for storing the corrupted words during spelling recognition
#define NoisyWordsStorageLimit 15000





//******************************************************************************
//******************************************************************************
//
//  Parameter settings for the Spelling model
//
//******************************************************************************
//******************************************************************************
double prSpRepeat = 0.3;
//The probability of repeating the current cognitive state again as the next state
//we make it 0.2 initially, but you can try different values to see the effects.

double prSpMoveOn = 0.7;
//The probability of moving from the current cognitive state to other states
//	as the next state
//we make it 0.8 initially, but you can try different values to see the effects.

//********************************************************
//Note that prSpRepeat + prSpMoveon should always equal 1
//********************************************************

double spDegenerateTransitionDistancePower = 2;
//The likelihood of moving from the cognitive state of typing some character in a word
//to the next cognitive state is proportion to the inverse of
//(spDegenerateTransitionDistancePower) to the
//(the distance between the current state to the next state)th power.
//In the setting of the original spelling model in the project,
//we make it 2, but you can try different values to see the effects.

double spDegenerateInitialStateDistancePower = 2;
//The likelihood of some character in a word as the initial cognitive state
//is proportion to the inverse of
//(spDegenerateInitialStateDistancePower) to the
//(the position of the character in the word)th power.
//In the setting of the original spelling model in the project,
// spDegenerateInitialStateDistancePower and spDegenerateTransitionDistancePower
//have the same value, but you can make them different to see the effects
//By default, we make it 2, but you can try different values to see the effects.


void setParametersSpellingModel()
{
    char temp;
    cout << endl
    << "Reset the parameters of the spelling model:" << endl << endl;
    
    cout << "Reset P_moveOn, the probability of moving on" << endl
    << "   from the current cognitive state to other states:" << endl
    << "P_moveOn = ";
    cin  >> prSpMoveOn;
    
    prSpRepeat = 1- prSpMoveOn;
    cout << endl
    << "Automatically reset P_repeat to 1-P_moveOn" << endl
    << "P_repeat = " << prSpRepeat << endl;
    
    cout << endl
    << "Do you want to change the deg_sp? (y or n)" << endl;
    cin >> temp;
    
    if (temp == 'y' )
    {
        cout << "Reset deg_sp, the power coefficient governing the probability of " << endl
        << "   skipping from the current cognitive state to other states:" << endl
        << "deg_sp = ";
        
        cin  >> spDegenerateTransitionDistancePower;
        
        spDegenerateInitialStateDistancePower = spDegenerateTransitionDistancePower;
    }
}

void displayParametersSpellingModel()
{
    cout << endl
    << "Parameter values of the spelling model:" << endl
    << "   P_repeat  = " << prSpRepeat << endl
    << "   P_moveOn  = " << prSpMoveOn << endl
    << "   deg_sp = " << spDegenerateTransitionDistancePower << endl << endl;
}

//******************************************************************************
//******************************************************************************
//
//  Parameter settings for the keyboard model
//
//******************************************************************************
//******************************************************************************

double prKbHit = 0.6;
//The probability that you want to type a character and you do successfully make it
//In the setting of the original keyboard model in the project,
//we make it 0.9, but you can try different values to see the effects.

double prKbMiss = 0.4;
//The sum of probabilities that you want to type a character but end in touching
//a different character.
//we make it 0.1, but you can try different values to see the effects.

//*******************************************************
//Note that prKbHit + prKbMiss should always equal 1
//*******************************************************

//In the setting of the original keyboard model in the project,
//we make it 0.2, but you can try different values to see the effects.


double kbDegenerateDistancePower = 2;
//The likelihood you want to type a character but end in touching a different character
//is proportion to the inverse of
//(kbDegenerateDistancePower) raised to the (distance between them) th power
//In the setting of the original keyboard model in the project,
//we make it 2, but you can try different constants to see the effects.


void setParametersKbModel()
{
    char temp;
    cout << endl
    << "Reset the parameters of the keyboard model:" << endl << endl;
    
    cout << "Reset P_hit, the probability of hitting" << endl
    << "   the right character wanted on the keyboard:" << endl
    << "P_hit = ";
    cin  >> prKbHit;
    
    prKbMiss = 1- prKbHit;
    cout << endl
    << "Automatically reset P_miss to 1-P_hit" << endl
    << "P_miss = " << prKbMiss << endl;
    
    cout << endl
    << "Do you want to change the deg_kb? (y or n)" << endl;
    
    cin >> temp;
    if ( temp == 'y' )
    {
        cout << "Reset deg_kb, the power coefficient governing the probability of " << endl
        << "   skipping from the current cognitive state to other states:" << endl
        << "deg_kb = ";
        
        cin  >> kbDegenerateDistancePower;
    }
}

void displayParametersKbModel()
{
    cout << endl
    << "Parameter values of the keyboard model:" << endl
    << "   P_hit  = " << prKbHit << endl
    << "   P_miss = " << prKbMiss << endl
    << "   deg_kb = " << kbDegenerateDistancePower << endl << endl;
}


//******************************************************************************
//******************************************************************************
//
//  Trace flag and the alphabet table
//
//******************************************************************************
//******************************************************************************
bool traceON = true;   // output tracing messages


/************************************************************************/
//Calculate and return the probability of charGenerated actually typed
//given charOfTheState as the underlying cognitive state.
/************************************************************************/
double prCharGivenCharOfState(char charGenerated, char charOfTheState)
{   // KEYBOARD STATE
    // CharGenerated = What we actually touched (typed)
    // CharOfTheState = What we want to type in our mind (our cognitive state)
    
    long double prob = 0.0;
    double dist=0;
    
    // this code is to find the distance between the char Generated and the char of the state
    for (int i=0; i<26; i++)
    {
        // distance
        dist=charGenerated-charOfTheState;
        
        // if the difference is less than 0, then just make it positive
        if (dist<0)
            dist=abs(dist);
        
        // we change the distance from being one dimensional (A-N-Z) to (A-Z-N || A-B-N)
        if (dist>13)
        {
            dist=dist-26;
            dist=abs(dist);
        }
    }
    
    double base=0, sum=0;
    
    // this code is to find the total ratio. The number 0.1 has to divide. From the total ratio, we can find out what the lowest probability (distance=13) is.
    for (int i=1; i<13;i++)
        sum=sum+(pow(kbDegenerateDistancePower, i));
    
    sum=sum*2+1;
    base=prKbMiss/sum;
    
    // this part is to distribute the probabilities and multiply each part with the base according to the distance
    if (dist==0)
        prob=prKbHit;
    
    else
        prob=base*((pow(kbDegenerateDistancePower, 13-dist)));
    
    return prob;
}

/************************************************************************/
//Calculate for each cognitive state excluding the special states I and F,
//	the probability of that cognitive state being the first cognitive state
//	after the transition out of the special state I.
//Note that the value of the parameter sizeOfTable should be
//	exactly the number characters in the word.
//Store these prbabilities in the prTable array.
/************************************************************************/
void getPrTableForPossibleInitialStates(double prTable[], int sizeOfTable)
{
    
    // initializationas
    int dist=sizeOfTable;
    double sumRatio=0;
    double base=0;
    
    // find the total sumRatio
    for (int i=dist; i>0; i--)
        sumRatio=sumRatio+pow(spDegenerateInitialStateDistancePower, i-1);
    
    // take 1 divide by the sumratio, which gives us the base
    base=1/sumRatio;
    int y=0;
    
    // put the values in their respective places in the array
    for (int i=dist-1; i>=0; i--)
    {
        prTable[y]=base*(pow(spDegenerateInitialStateDistancePower, i));
        y++;
    }
    
}

/************************************************************************/
//Calculate for each actual cognitive state for a word
//	(excluding the special I state),
//	the probability of that cognitive state being the next cognitive state
//	given that currentState is the index of the current state.
//Note that the value of the parameter sizeOfTable should be
//	1 + the number characters in the word,
//Store these prbabilities in the transitionPrTable[] array.
/************************************************************************/
void getPrTableForPossibleNextStates (double transitionPrTable[], int sizeOfTable, int currentState)
{
    //It is a word of sizeOfTable characters:
    //	i.e. the number of character states is sizeOfTable.
    //	index them from 0 to sizeOfTable-1.
    //currentState is the index of the current state in the word
    
    //First calculate the sum of ratios of probabilities of
    //	going from the current state into other down-stream states down in word
    //	including all the down-stream character states and the
    //	special F final state.
    
    //Second, for each state (excluding the special I state)
    //	calculate the probability of
    //	transitioning from the current state into the character state
    //	and store the probability into the table.
    
    //**************************************************
    //Replace the following with your own implementation
    //**************************************************
    
    // set the probability of the current state to 0.2
    transitionPrTable[currentState]=prSpRepeat;
    
    // if the current state is not the first box, then everting becomes 0
    if (currentState>0)
    {
        for (int i=0; i<currentState; i++)
            transitionPrTable[i]=0;
    }
    
    // find the distance from current state to the end
    int dist=sizeOfTable-1-currentState;
    int sumRatio=0;
    double base=0;
    
    // find the total sumRatio
    for (int i=dist; i>0; i--)
        sumRatio=sumRatio+pow(spDegenerateTransitionDistancePower, i-1);
    
    // get the base by dividing the probability by the sumratio
    base=prSpMoveOn/sumRatio;
    int y=currentState+1;
    
    // plcae the ratios in their respective places; mutliply base by their location on the array
    for (int i=dist; i>0; i--)
    {
        transitionPrTable[y]=base*(pow(spDegenerateTransitionDistancePower, i-1));
        y++;
    }
    
}






/************************************************************************/
//  Programming #2
//
//  List below are function prototypes of functions given  or required
//		to be implemented in Programming #2
//
/************************************************************************/

/************************************************************************/
//Given the probabilities (of sizeOfTable elements) stored in prTable,
//	try to randomly take a sample out of sizeOfTable elements
//	according to the probabilities of sizeOfTable elements;
//Return the index of the non-deterministically sampled element.
/************************************************************************/
int take1SampleFrom1PrSpace(double prTable[], int sizeOfTable)
{ int i;
    double prSum=0;
    for (i=0; i<sizeOfTable; i++)
    {
        //cout << prTable[i] << endl;
        prSum += prTable[i];
    }
    
    if (prSum < 0.999 || prSum > 1.001)
        cout << "Something is wrong with a random sampleing" << endl
        << "The sum of all probabilities in the table is " << prSum  << endl;
    
    //Calculate the probability intervals of the characters
    double prAccumulated = 0;
    double * prIntervals;
    prIntervals = new double[sizeOfTable];
    for (i=0; i<sizeOfTable; i++)
    { prAccumulated = prAccumulated + prTable[i];
        prIntervals[i] = prAccumulated;
    }
    
    /*
     cout << endl;
     for (i=0; i<sizeOfTable; i++)
     { if (i>0)
     cout << "state " << i << " lower bounded by " << prIntervals[i-1]<< endl;
     cout << "state " << i << " upper bounded by " << prIntervals[i]<< endl;
     }
     */
    
    // Generate a random number in [0,1]
    i = rand()% 1001;
    double temp = i / 1000.0;
    //cout << "The random number pair generated is " << i << endl << temp << endl;
    
    bool sampleTaken = false;
    for (i=0; i<sizeOfTable && !sampleTaken; i++)
        if (temp <= prIntervals[i])
        {   delete [] prIntervals;
            //            cout << "The random interval id is " << i << endl;
            return i;
        }
    
    return sizeOfTable-1;
}


/************************************************************************/
//
//Given the character to type (charToType)
//	(assuming that the 1D keyboard of 26 keys is used),
//	(assuming that prTable[] for storing 26 prbabilities),
//	calculate pr(charGenerated = 'a' | charToType),
//	calculate pr(charGenerated = 'b' | charToType),
//	...
//	calculate pr(charGenerated = 'z' | charToType), and
//	store these probabilities in prTable.
/************************************************************************/
void getKeyboardProbabilityTable(char charToType, double *prTable)
{
    char asciiMap[] = "abcdefghijklmnopqrstuvwxyz";
    double dist=0, prob=0, base=0, sum=0;
    
    // this code is to find the total ratio. The number 0.1 has to divide. From the total ratio, we can find out what the lowest probability (distance=13) is.
    for (int i=1; i<13;i++)
        sum=sum+(pow(kbDegenerateDistancePower, i));
    
    sum=sum*2+1;
    base=prKbMiss/sum;
    
    // this code is to find the distance between the char Generated and the char of the state
    for (int i=0; i<26; i++)
    {
        // find the distance
        dist=asciiMap[i]-charToType;
        
        // make sure the distance is not negative
        if (dist<0)
            dist=abs(dist);
        
        // convert the distance from 13-26, to 1-13; since the keyboard distance is symmetric
        if (dist>13)
        {
            dist=dist-26;
            dist=abs(dist);
        }
        
        // convert the distance to probability
        if (dist==0)
            prob=prKbHit;
        
        else prob=base*((pow(kbDegenerateDistancePower, 13-dist)));
        
        prTable[i]=prob;
    }
}


/************************************************************************/
//Simulate the keyboard model:
//Given the charToTye, simulate what character may actually
//	be typed and return it as the result.
/************************************************************************/
char typeOneChar(char charToType)
{
    // declare everything
    char asciiMap[] = "abcdefghijklmnopqrstuvwxyz";
    double prTable[26];
    int randIndex;
    
    // get the probability table
    getKeyboardProbabilityTable(charToType, prTable);
    
    // use take 1 sample to get the random index
    randIndex=take1SampleFrom1PrSpace(prTable, 26);
    
    return asciiMap[randIndex];
}



/************************************************************************/
//Simulate the combination of the spelling model and the keyboard model:
//Given a word stored in the word array, simulate what may actually
//	be typed and store the result in the output array.
//maxOutput specifies the capacity limit of the output array, by default it is 100.
//When traceON is true (by default it is false), extra outputs are provided as traces.
/************************************************************************/
void typeOneWord(char word[], char output[], bool traceON, int maxOutput)
{
    // defaults
    maxOutput=100;
    int sizeOfTable = strlen(word)+1, currentState=0, randIndex, index=0, oriState;
    double *initialPrTable, *transitionPrTable;
    
    char TempLetter;
    initialPrTable = new double[strlen(word)];
    transitionPrTable = new double[sizeOfTable];
    transitionPrTable[sizeOfTable] = NULL;
    
    
    // DEALS WITH THE INITIAL STATES
    getPrTableForPossibleInitialStates(initialPrTable, strlen(word));
    
    initialPrTable[sizeOfTable]=0;
    // find the randomIndex using the initialPrTable and the sizeOfTable
    randIndex=take1SampleFrom1PrSpace(initialPrTable, strlen(word));
    
    
    // place the randomIndex of the word into the ouput
    TempLetter = typeOneChar(word[randIndex]);
    output[0]=TempLetter;
    
    // increase the currentState by 1
    currentState = randIndex;
    
    // show the output
    if (traceON)
        cout << output[index] << " presed, " << "Current State: " << word[0] << ", " << 0 << " -- Next State: " << word[currentState] << ", " << currentState << endl;
    
    index = index + 1;
    
    // DEALS WITH THE TRANSITION STATES
    // while current state is not at final state
    while (currentState!=sizeOfTable-1)
    {
        // save the currentState into a temp variable
        oriState = currentState;
        
        // perform necessary functions
        getPrTableForPossibleNextStates(transitionPrTable, sizeOfTable, currentState);
        randIndex = take1SampleFrom1PrSpace(transitionPrTable, sizeOfTable);
        
        // don't let the blank space go into typeOneChar
        if (randIndex!=sizeOfTable-1)
            TempLetter = typeOneChar(word[randIndex]);
        
        // make the randIndex the new current state
        currentState = randIndex;
        output[index] = TempLetter;
        
        // output
        if (traceON)
            cout << output[index] << " presed, " << "Current State: " << word[oriState] << ", " << oriState << " -- Next State: " << word[currentState] << ", " << currentState << endl;
        
        // increae index
        index++;
    }
    
    output[index] = '\0';
    
}

// type one article
void typeOneArticle(char* corruptedMessageFile, char* sourceArticle, bool trace)
{
    
    // declaration
    ifstream fin(sourceArticle);
    ofstream fout(corruptedMessageFile);
    
    bool temp = trace;
    
    // keep looping
    while (true)
    {
        // temp variables
        char oneString[20], output[100];
        
        // fileInput from outside file
        fin >> oneString;
        
        cout << "Stimulate the typing of -- " << oneString << endl;
        // perform type one word
        typeOneWord(oneString, output, temp);
        
        // save the output from type one word to temporary variable
        corruptedMessageFile = output;
        
        // fout the corrupted message
        fout << corruptedMessageFile << endl;
        cout << "The result -- " << output << endl;
        
        cout << endl;
        
        if (fin.eof())
            break;
    }
    
    cout << "TypeOneArticle done" << endl;
}


/************************************************************************/
//The function should calculate and return
//    the probability of getting a series of characters stored in
//    the string object observedString
//    when you want to type the word stored in
//    the string object wordString
/************************************************************************/
double prOf1CharSeriesWhenTyping1Word
(string observedString, string wordString)
{
    
    // This section is for creating the transition table
    // size of the transitionTable
    long int lengthTransTable=wordString.length()+1, z=0;
    
    // Make the transition table and resize it
    vector< vector<double> > TransTable;
    TransTable.resize(lengthTransTable);
    
    for (int i=0; i<lengthTransTable; i++)
        TransTable[i].resize(lengthTransTable);
    
    // delcare the initalPrTable and the transitionPrTable
    double initialPrTable[1000];
    
    // Run getPrTableForPossibleInitialStates
    getPrTableForPossibleInitialStates(initialPrTable, wordString.length());
    
    // delcare a temp vector to store all values in the transitionPrTable
    vector <double> Temp;
    
    // run the getPrTableForPossibleNextStates and find all the probability
    for (int currentState=0; currentState<wordString.length(); currentState++)
    {
		double transitionPrTable[1000];
        
        getPrTableForPossibleNextStates (transitionPrTable, wordString.length()+1, currentState);
        
        for (int nextState=0; nextState<wordString.length()+1; nextState++)
            Temp.push_back(transitionPrTable[nextState]);
    }
    
    // combine the intialPrTable and all transition states into the transition table
    for (int i=0; i<lengthTransTable; i++)
    {
        for (int j=0; j<lengthTransTable; j++)
        {
            if (i==0)
                TransTable[i][j]=initialPrTable[j];
            
            else
            {
                TransTable[i][j]=Temp[z];
                z++;
                
            }
        }
    }
    
    // make last element in the first row to be 0
    TransTable[0][wordString.length()]=0;
    
    
    // display the transition table
    /*
    for (int i=0; i<lengthTransTable; i++)
    {
        for (int j=0; j<lengthTransTable; j++)
        {
            cout << TransTable[i][j] << "   ";
        }
        
        cout << endl;
    }
     */
    

    /// Now that the table is made, we can use the transition table to perform the forward moving algorithim
    vector< vector<double> > Table;
    int row=wordString.size(), column=observedString.size();
    
    Table.resize(row);
    for (int i = 0; i <row; i++)
        Table[i].resize(column);
    
    int w=0;
    
    // go through all the different boxes in the bigTable and see what belongs where
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            
            // this part is to calculate the first column
            if (j==0)
            {
                // cout << "Trans: " << TransTable[j][i] << endl;
                Table[i][j]=TransTable[j][i]*prCharGivenCharOfState(wordString[i], observedString[j]);
            }
                
            // 2nd to (Last-1) column
            else
            {
                
                double Temp1=0;
                
                for (int z=0; z<i+1; z++){
                    Temp1=Temp1+(Table[z][j-1]*TransTable[z+1][w]);
                }
                
                
                Table[i][j]=Temp1*prCharGivenCharOfState(wordString[i], observedString[j]);
                
            }
            
            //cout << endl;
        
        }
        
        w++;
    }
    
    // The last column
    double Final=0;
    for (int i=0; i<row; i++)
    {
        Final=Final+(Table[i][observedString.length()-1])*(TransTable[i+1][wordString.length()]);
    }
    
    
    // DISPLAY
    /*
    cout << "Display FMA: " << endl;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<column; j++)
        {
            cout << Table[i][j] << "    ";
        }
        
        
        cout << endl;
    }
    */
    
     //display end result
//    cout << "Pr(" << observedString << "|" << wordString << "): " << Final << endl;
    
    return Final;
}


// LOGPR
double logPrOfGettingDocument1WhenTypingDocument2(string actual, string corrupt)
{
    
    // declaration
    ifstream actualFile;
    ifstream corruptFile;
    
    double result=0, result1=0;
    string temp1, temp2;
    
    int i=0;
    
    // open files
    actualFile.open(actual);
    corruptFile.open(corrupt);

    // loop until the end
    while(actualFile>>temp1 && corruptFile >> temp2)
    {
        // get the sums of the logs
        result+=log(prOf1CharSeriesWhenTyping1Word(temp2, temp1));
        result1+=log10(prOf1CharSeriesWhenTyping1Word(temp2, temp1));
    }
    
    return result;
}


void setNewSp(double x)
{
    prSpRepeat=x;
    prSpMoveOn=1-x;
}

void setNewKb(double x)
{
    prKbHit=x;
    prKbMiss=1-x;
}

double bruteForceMethod(string actual, string corrupt)
{
    
    double optimalSp=0, optimalKb =0, log=0, maxLog=logPrOfGettingDocument1WhenTypingDocument2(actual, corrupt);
    
    for (double count1=0.1; count1<1; count1+=0.1)
    {
        for (double count2=0.1; count2<1; count2+=0.1)
        {
            
            setNewKb(count1);
            setNewSp(count2);
            
            log=logPrOfGettingDocument1WhenTypingDocument2(actual, corrupt);
            
            if (log>=maxLog)
            {
                maxLog=log;
                optimalKb=count2;
                optimalSp=count1;
            }
        }
    }

    cout << endl;
    cout << "P_hit: " << optimalSp << " -- " << "P_miss: " << 1-optimalSp << endl;
    cout << "P_MoveOn: " << 1-optimalKb << " -- " << "P_repeat: " << optimalKb << endl;
    cout << "*********************************" << endl;

   
    
    return 1;
}






bool myComparison(const pair<string,double> &a,const pair<string, double> &b)
{
    return a.second<b.second;
}

double optionR(string vocabulary, string corrupt)
{
    
    // delcaration
    ifstream vocabularyFile;
    ifstream corruptFile;
    ofstream fout;
    
    // delcare the vectors
    vector<string> corruptVect, vocabVect, output;
    string temp1, temp2;
    vector <pair <string, double>> totalString;
    pair <string, double> Temp1, Temp2;
    
    vocabularyFile.open(vocabulary);
    corruptFile.open(corrupt);
    
    
    fout.open ("recoveredMessage_V1.txt");
    
    // INPUT FROM FILE
    while(vocabularyFile>>temp1)
        vocabVect.push_back(temp1);
    
     while (corruptFile >> temp2)
         corruptVect.push_back(temp2);
    
    
    // compare each word corruptVect to the whole vocab list
    for (int i=0; i<corruptVect.size(); i++)
    {
        for (int y=0; y <vocabVect.size(); y++)
        {
            Temp1 = make_pair(vocabVect[y], log((prOf1CharSeriesWhenTyping1Word(corruptVect[i], vocabVect[y]))));
            totalString.push_back(Temp1);
        }
        
        // sort the totalString
        sort(totalString.begin(), totalString.end(), myComparison);
        
        // pick out the top four candidates
        for (int i=0; i<totalString.size(); i++)
        {
            if (i>totalString.size()-5)
            fout << totalString[i].first << " ";
        }
        
        fout << endl;
 
        // clear the total String
        totalString.clear();
        
    }
    
    fout.close();
    return 1;
}



double optionT(string vocabulary, string corrupt1, string corrupt2)
{
    
    // delcaration
    ifstream vocabularyFile;
    ifstream corruptFile1;
    ifstream corruptFile2;
    ofstream fout;

    vector<string> vocabVect, corruptVect1, corruptVect2, output;
    string temp1, temp2, temp3;
    
    vocabularyFile.open(vocabulary);
    corruptFile1.open(corrupt1);
    corruptFile2.open(corrupt2);

    fout.open ("recoveredMessage_V2.txt");
    
    while(vocabularyFile>>temp1)
        vocabVect.push_back(temp1);
    
    while (corruptFile1 >> temp2)
        corruptVect1.push_back(temp2);
    
    while (corruptFile2 >> temp3)
        corruptVect2.push_back(temp3);
    
    vector <pair <string, double>> totalString;
    pair <string, double> Temp1, Temp2;
    
    
    for (int i=0; i<corruptVect1.size(); i++)
    {
        for (int y=0; y <vocabVect.size(); y++)
        {
            Temp1 = make_pair(vocabVect[y], (prOf1CharSeriesWhenTyping1Word(corruptVect1[i], vocabVect[y]))*(prOf1CharSeriesWhenTyping1Word(corruptVect2[i], vocabVect[y])));
            totalString.push_back(Temp1);
        }
        
        sort(totalString.begin(), totalString.end(), myComparison);
        
        for (int i=0; i<totalString.size(); i++)
        {
            
            if (i>totalString.size()-5)
                fout << totalString[i].first << " ";
        }
        
        fout << endl;
        totalString.clear();
        
    }
    
    fout.close();
    return 1;
}

double optionU(string original, string recovered1, string recovered2)
{
    
    // delcaration
    ifstream originalFile;
    ifstream recoveredFile1;
    ifstream recoveredFile2;
    
    vector<string> originalVect;
    vector<string> recoveredVect1;
    vector<string> recoveredVect2;
    
    string temp1, temp2, temp3;
    
    originalFile.open(original);
    recoveredFile1.open(recovered1);
    recoveredFile2.open(recovered2);

    
    while(originalFile >> temp1)
        originalVect.push_back(temp1);
    
    while(recoveredFile1 >> temp2)
        recoveredVect1.push_back(temp2);
    
    while(recoveredFile2 >> temp3)
        recoveredVect2.push_back(temp3);
    
//    cout << "OV: " << originalVect.size() << "    RV1: " << recoveredVect1.size() << "    RV2: " << recoveredVect2.size() << endl;
//    cout << "################################" << endl;



    double n=0, countA=0, posOne=0, posTwo=0, posThree=0, posFour=0;
    int sumOne=0;
    
    for (int i=0; i<originalVect.size(); i++)
    {
        n=0;
        
        while (n<4)
        {
            if (originalVect[i] == recoveredVect1[countA])
            {
                if (n==0)
                    posOne+=1;
                
                if (n==1)
                    posTwo+=1;
                
                if (n==2)
                    posThree+=1;
                
                if (n==3)
                    posFour+=1;
                
                sumOne+=1;
            }
            
            countA=countA+1;
            n=n+1;
        }
    }
    
    // STATISTICS FOR THE FIRST PART
    cout << "Stats for recovered one: " << endl;
	cout << posOne << " are recognized in the top 1 list: " << posOne / 195 << endl;
	cout << posOne+posTwo << " are recognized in the top 2 list: " << (posOne+posTwo)/ 195 << endl;
	cout << posOne + posTwo + posThree << " are recognized in the top 3 list: " << (posOne + posTwo + posThree) / 195 << endl;
	cout << posOne + posTwo + posThree + posFour << " are recognized in the top 4 list: " << (posOne + posTwo + posThree + posFour) / 195 << endl;

	cout << endl;
    
    countA=0;
    double posOneA=0, posTwoA=0, posThreeA=0, posFourA=0;
    double sumTwo=0;
    
    for (int i=0; i<originalVect.size(); i++)
    {
        n=0;
        
        while (n<4)
        {
            if (originalVect[i] == recoveredVect2[countA])
            {
                if (n==0)
                    posOneA+=1;
                
                if (n==1)
                    posTwoA+=1;
                
                if (n==2)
                    posThreeA+=1;
                
                if (n==3)
                    posFourA+=1;
                
                sumTwo+=1;
            }
            
            countA=countA+1;
            n=n+1;
        }
    }
    
	// statistics for the second part 
	cout << "Stats for recovered two: " << endl;
	cout << posOneA << " are recognized in the top 1 list: " << posOneA / 195 << endl;
	cout << posOneA + posTwoA << " are recognized in the top 2 list: " << (posOneA + posTwoA) / 195 << endl;
	cout << posOneA + posTwoA + posThreeA << " are recognized in the top 3 list: " << (posOneA + posTwoA + posThreeA) / 195 << endl;
	cout << posOneA + posTwoA + posThreeA + posFourA << " are recognized in the top 4 list: " << (posOneA + posTwoA + posThreeA + posFourA) / 195 << endl;

    return 1;
}

