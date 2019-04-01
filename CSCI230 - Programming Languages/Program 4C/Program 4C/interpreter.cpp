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
expVector infixExp, whileExp;
string keyWord;
bool top, silent, firstTime=true;

stack <int> stackLineNumbers;
stack <string> stackKeys;

stack <int> functionLines;





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

            if (silent==false)
            {

                // DISPLAY
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
            
                // READ
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

                // ASSIGNMENT
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
            
                // IF
                // ***************************************
                else if (tokenVect[0] == "if")
                {
                    
                    startPos=j+1;
                    stackKeys.push("if");
                    
                    // push everyting into the infixExp
                    for (int i=startPos; i<tokenVect.size(); i++)
                        infixExp.push_back(tokenVect[i]);
                    
                    ExpressionEvaluator:: infixEvaluator(infixExp, valuesList, value);
                    
                    if (value==1)
                        top=true;
                    
                    else if (value==0)
                    {
                        top=false;
                        silent=true;
                    }
                    
                    infixExp.clear();
                    break;
                }
                
                // ELSE
                // ***************************************
                else if (tokenVect[0] == "else")
                {
                    stackKeys.push("else");
                    
                    // if the if on top is true, then stay silent
                    if (top==true)
                        silent=true;
                    
                    // if the if on top is false, then run the block
                    else if (top==false){ }
                    
                    break;
                }
                
                // WHILE
                // ***************************************
                else if (tokenVect[0] =="while")
                {
                    
                    startPos=j+1;
                    stackKeys.push("while");
                    
                    // push everyting into the infixExp
                    for (int i=startPos; i<tokenVect.size(); i++)
                    {
                        infixExp.push_back(tokenVect[i]);
                        
                        if (firstTime==true)
                            whileExp.push_back(tokenVect[i]);
                    }

                    firstTime=false;
                    
//                    cout << "infixExp" << endl;
//                    for (int i=0; i<infixExp.size(); i++)
//                        cout << infixExp[i] << endl;
//
//                    cout << "whileExp" << endl;
//                    for (int i=0; i<whileExp.size(); i++)
//                        cout << whileExp[i] << endl;
                    
                    ExpressionEvaluator:: infixEvaluator(infixExp, valuesList, value);
                    
                    if (value==1)
                        silent=false;
                    
                    else if (value==0)
                        silent=true;
                    
                    infixExp.clear();
                    break;
                    
                }
                
                // dont do anything
                else if (tokenVect[j] == "{" || tokenVect[j] == "}") { }
                
                // Syntax error
                else
                {
                    cout << "Syntax error" << endl;
                    goto Exit;
                }
                
            }
        
        if (tokenVect[0]=="{")
            stackLineNumbers.push(i);

        else if (tokenVect[0]=="}")
        {

            if (stackLineNumbers.empty())
            {
                cout << "There is a syntax error" << endl;
                goto Exit;
            }
            
            else if (stackKeys.top() == "if" || stackKeys.top() == "else")
            {
                stackLineNumbers.pop();
                stackKeys.pop();
                silent=false;
            }
            
            else if (stackKeys.top() == "while")
            {
                stackKeys.pop();
                int closingWhile=i;
     
                ExpressionEvaluator:: infixEvaluator(whileExp, valuesList, value);
                
                if (value==1)
                    i=stackLineNumbers.top()-2;
                
                else if (value==0)
                {
                    i=closingWhile;
                    whileExp.clear();
                    firstTime=true;
                }
                
                stackLineNumbers.pop();
                
                break;
            }
       
        }
      
        }
        
    }
    
Exit:

    // clear everything
    myVectOfTokenVects.clear();
    myVectOfCategoryVects.clear();
    valuesList.clear();

}






