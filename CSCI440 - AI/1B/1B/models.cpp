#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "models.h"

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
double prSpRepeat = 0.4;
//The probability of repeating the current cognitive state again as the next state
//we make it 0.2 initially, but you can try different values to see the effects.

double prSpMoveOn = 0.6;
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

double prKbHit = 0.75;
//The probability that you want to type a character and you do successfully make it
//In the setting of the original keyboard model in the project,
//we make it 0.9, but you can try different values to see the effects.

double prKbMiss = 0.25;
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
//  Programming #1
//
//  List below are function prototypes of functions required
//		to be implemented in Programming #1.
//	Replace the implementation of the following functions with
//		your own code from Programmin #1A and #1B.
//
/************************************************************************/
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
    //It is a word of sizeOfTable characters:
    //	i.e. the number of character states is sizeOfTable.
    //	let's index these chracters from 0 to sizeOfTable-1.
    //
    
    //First calculate the sum of ratios of probabilities of
    //	going from the I state into these character states.
    
    
    //Second, for each character state calculate the probability
    //	transitioning from the special I state into the character state.
    
    //**************************************************
    //Replace the following with your own implementation
    //**************************************************
    
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
void getPrTableForPossibleNextStates
(double transitionPrTable[], int sizeOfTable, int currentState)
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
        sumRatio=sumRatio+pow(kbDegenerateDistancePower, i-1);
    
    // get the base by dividing the probability by the sumratio
    base=prSpMoveOn/sumRatio;
    int y=currentState+1;
    
    // plcae the ratios in their respective places; mutliply base by their location on the array
    for (int i=dist; i>0; i--)
    {
        transitionPrTable[y]=base*(pow(kbDegenerateDistancePower, i-1));
        y++;
    }
    
}
