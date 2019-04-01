//cont/map1.cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>
#include <string>

#include "lexScanner.h"
#include "expEvaluator.h"
#include "interface.h"
#include "interpreter.h"
using namespace std;

typedef map <string, float> StringFloatMap;
StringFloatMap valuesList;
StringFloatMap:: iterator pos;

float value=0;
expVector infixExp;


void interpreter:: executeProgram(vector <string> &sourceProgram)
{
    
    int startPos=0;
    string TempString;
    
    vectOfTokenVects myVectOfTokenVects;
    vectOfCategoryVects myVectOfCategoryVects;
    
    LexicalScanner::getLexicalInfo(sourceProgram, myVectOfTokenVects, myVectOfCategoryVects);
    
    for (int i=0; i<myVectOfTokenVects.size(); i++)
    {
        perLineTokenVector tokenVect;
        tokenVect = myVectOfTokenVects[i];
        
        for (int j=0; j<tokenVect.size(); j++)
        {
            
            //                cout << "############################" << endl;
            //                cout << "i: " << i << endl;
            
            // DEALS WITH DISPLAY
            // ***************************************
            if (tokenVect[0] == "display")
            {
                for (int y=1; y<tokenVect.size(); y++)
                {
                    // deals with pure strings
                    if (LexicalScanner::isSTRING_LITERAL(tokenVect[y]))
                    {
                        TempString=tokenVect[y];
                        
                        TempString.erase(TempString.begin());
                        TempString.erase(TempString.end()-1);
                        
                        if (tokenVect[y+1] == ";")
                            cout << TempString << endl;
                        
                        else if (tokenVect[y+1] == ",")
                            cout << TempString;
                        
                        y=y+1;
                    }
                    
                    // deals with anything else
                    else if (LexicalScanner::isNUMERICAL_LITERAL(tokenVect[y]) || LexicalScanner::isID_NAME(tokenVect[y]))
                    {
                        // loop keep pushing back until , or ; is met
                        for (; y<tokenVect.size()-1; y++)
                        {
                            infixExp.push_back(tokenVect[y]);
                            
                            if (tokenVect[y+1] == "," || tokenVect[y+1] == ";")
                                break;
                        }
                        
                        ExpressionEvaluator::infixEvaluator(infixExp, valuesList, value);
                        
                        if (tokenVect[y+1] == ";")
                            cout << value << endl;
                        
                        else if (tokenVect[y+1] == ",")
                            cout << value;
                    }
                    
                    infixExp.clear();
                }
                
                break;
                
            }
            
            // DEALS WITH READ
            // ***************************************
            else if (tokenVect[0] == "read")
            {
                // just put into the map
                double Temp1;
                cout << "Please enter the value for " << tokenVect[j+1] << endl;
                
                cin >> Temp1;
                cout << endl;
                
                valuesList[tokenVect[j+1]] = Temp1;
                break;
            }
            
            // DEALS WITH ASSIGNMENT
            // ***************************************
            else if (LexicalScanner::isID_NAME(tokenVect[0])==true)
            {
                if (tokenVect[j]== "=")
                {
                    startPos=j+1;
                    
                    // push everyting into the infixExp
                    for (int i=startPos; i<tokenVect.size()-1; i++)
                        infixExp.push_back(tokenVect[i]);
                    
                    for (int i=0; i<infixExp.size(); i++)
                    {
                        if (LexicalScanner::isID_NAME(infixExp[i]))
                        {
                            pos = valuesList.find(infixExp[i]);
                            
                            if (pos != valuesList.end()) {}
                            
                            else
                            {
                                cout << "Variables: " << infixExp[i] << " not found" << endl;
                                goto Exit;
                            }
                        }
                    }
                    
                    // evaluate the infix exp and find value
                    string stringTemp =tokenVect[0];
                    ExpressionEvaluator:: infixEvaluator(infixExp, valuesList, value);
                    valuesList[stringTemp]=value;
                    infixExp.clear();
                    break;
                }
            }
            
            else
            {
                cout << "Syntax error" << endl;
                goto Exit;
            }
            
            
        }
        
    }
    
Exit:
    
    
    // clear everything
    myVectOfTokenVects.clear();
    myVectOfCategoryVects.clear();
    
}






