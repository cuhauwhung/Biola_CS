
// simpleScanner.cpp gives some some hints on the implementation of your lexical scanner
// function. For example, it shows how you can break a statementinto basic
// components (tokens) and determine their categories.


#include <iostream>  // for basic iostream operations
#include <cctype>    // to check C character type using function like isdigit()

#include "lexScanner.h"
// You may include interface information of simpleScanner.cpp in "lexScanner.h", such as
// the coding of component categories into integers, and the function prototype of
// lexScanner.
// The caller of the lexical scanner module will aso include "lexScanner.h"

using namespace std;

const char DOUBLE_QUOTE = '\"';

//***************************************************************************
//*  Section 1. two functions:
//*  getPerLineTokenVectFromOneCharArray and
//*	 getPerLineTokenVectFromOneStringObject
//*
//***************************************************************************
//*  They analyze one C-style character array or a string object and
//*  collect the tokens there as a vetor of token strings.
//***************************************************************************


void LexicalScanner::getPerLineTokenVectFromOneCharArray(const char* s, perLineTokenVector & tokenVector)
{
    bool inString = false;
    
    string v(s);
    string tokenBuffer;
    
    int i = 0;
    
    // have a loop that doe this
    while (i < v.size())
    {
        // deals with blank space... if blank space then don't do anything
        
        
        if (v[i] == '"')
        {
            tokenBuffer += '"';
            inString = true;
        }
        
        // deals with opeartors with 2 symbols
        else  if (v[i] == '<' && v[i + 1] == '=' && inString == false)
        {
            tokenVector.push_back("<=");
            i = i + 1;
        }
        
        else if (v[i] == '>' && v[i + 1] == '=' && inString == false)
        {
            tokenVector.push_back(">=");
            i = i + 1;
        }
        
        else if (v[i] == '=' && v[i + 1] == '=' && inString == false)
        {
            tokenVector.push_back("==");
            i = i + 1;
        }
        
        else if (v[i] == '!' && v[i + 1] == '=' && inString == false)
        {
            tokenVector.push_back("!=");
            i = i + 1;
        }
        
        else if (v[i] == '/' && v[i + 1] == '/' && inString == false)
        {
            tokenVector.push_back("//");
            i = i + 1;
        }
        
        else if (v[i] == '&' && v[i + 1] == '&' && inString == false)
        {
            tokenVector.push_back("&&");
            i = i + 1;
        }
        
        else if (v[i] == '|' && v[i + 1] == '|' && inString == false)
        {
            tokenVector.push_back("||");
            i = i + 1;
        }
        
        else if (v[i] == ' ')
        {
            
        }
        
        // deal with the operators with 1 symbol
        else if (v[i] == '=' && inString == false)
            tokenVector.push_back("=");
        
        else if (v[i] == ':' && inString == false)
            tokenVector.push_back(":");
        
        else if (v[i] == ';' && inString == false)
            tokenVector.push_back(";");
        
        else if (v[i] == ',' && inString == false)
            tokenVector.push_back(",");
        
        else if (v[i] == '<' && inString == false)
            tokenVector.push_back("<");
        
        else if (v[i] == '>' && inString == false)
            tokenVector.push_back(">");
        
        else if (v[i] == '{' && inString == false)
            tokenVector.push_back("{");
        
        else if (v[i] == '}' && inString == false)
            tokenVector.push_back("}");
        
        else if (v[i] == '(' && inString == false)
            tokenVector.push_back("(");
        
        else if (v[i] == ')' && inString == false)
            tokenVector.push_back(")");
        
        else if (v[i] == '+' && inString == false)
            tokenVector.push_back("+");
        
        else if (v[i] == '-' && inString == false)
            tokenVector.push_back("-");
        
        else if (v[i] == '*' && inString == false)
            tokenVector.push_back("*");
        
        else if (v[i] == '/' && inString == false)
            tokenVector.push_back("/");
        
        else if (v[i] == '%' && inString == false)
            tokenVector.push_back("%");
        
        
        // this deals with the ID name / keywords
        else
        {
            // have an index to store
            int tempIndex = 0;
            
            // have a token buffer to
            for (int z = i; z < v.size(); z++)
            {
                // add the characeters into token tokenBuffer
                tokenBuffer += s[z];
                
                // the number of chars getting placed in tokenBuffer gets stored
                tempIndex = tempIndex + 1;
                
                // if its a string then break if (z+1) is any of these characters
                if (inString == true)
                {
                    if (v[z + 1] == '"')
                    {
                        tokenBuffer += '"';
                        i = i + 1;
                        inString = false;
                        break;
                    }
                }
                
                if (inString == false)
                {
                    // if the next char is like this, this means that the IDname/function name should stop
                    if ((v[z + 1] == '=') || (v[z + 1] == '+') || (v[z + 1] == '-') || (v[z + 1] == '*') || (v[z + 1] == '/') ||
                        (v[z + 1] == '<') || (v[z + 1] == '>') || (v[z + 1] == ')') || (v[z + 1] == ';') || (v[z + 1] == ' ') ||
                        (v[z + 1] == '(') || (v[z + 1] == '}') || (v[z + 1] == '{') || (v[z + 1] == '!') || (v[z + 1] == ',') ||
                        (v[z + 1] == '&') || (v[z + 1] == '|') || (v[z + 1] == '%')
                        )
                        
                        break;
                }
                
            }
            
            // push back the tokenBuffer into tokenVector
            i = i + tempIndex - 1;
            tokenVector.push_back(tokenBuffer);
            tokenBuffer.clear();
            
        }
        
        // add the index
        i++;
    }
}





void LexicalScanner::getPerLineTokenVectFromOneStringObject
(const string statement,
 perLineTokenVector & tokenVector
 )
// 1. One line of code is stored in string object: statement.
// 2. In the end, we'll store all the tokens, each as an object of the string class,
//    in tokenVector, which is a vector of strings.
{
    
    getPerLineTokenVectFromOneCharArray(statement.c_str(), tokenVector);
    
}




//******************************************************************
//* Section 2:
//* The following is a colllection of functions to
//* test the categories of tokens
//******************************************************************

//Check whether a token is a numerical token
bool LexicalScanner::isNUMERICAL_LITERAL(const string & token)
{
    if (token == ".")
        return false;
    
    bool decimalPointSeenBefore = false;
    //no decimal points seen yet
    
    for (size_t i = 0; //index into the string
         i < token.size();
         i++)
    {
        char c;
        c = token[i];
        if (c != '.' && !isdigit(c))
            // not a digit, nor a demical point ==> Not Numerical
            return false;
        if (c == '.' && decimalPointSeenBefore)
            // demical point appears more than once ==> Not right
            return false; //Not Numerical
        if (c == '.' && !decimalPointSeenBefore)
            // Keep a record when decimal point is seen for the first time
            decimalPointSeenBefore = true;
        
    }
    
    return true;
}


bool LexicalScanner::isKEYWORD(const string & token)
// Test whether it is a keyword of BIOLA,
// like function, read, display, if, else, return, while
{
    return (token == "function" || token == "read" || token == "display" || token == "if" ||
            token == "else" || token == "return" || token == "while");
}

bool LexicalScanner::isID_NAME(const string & token)
// Testwhether it is an identifier, i.e. names of variables, labels, and functions
// First char is a letter and then any combination of number or alphanumerical chars
{
    //if it's a keyword, return false
    if (isKEYWORD(token))
        return false;
    
    //only check the entire string if the first char is a letter
    if (isalpha(token[0]))
    {
        //starting index at 0 because the string could be just a char (size = 1)
        for (int x = 0; x < token.size(); x++)
        {
            if (!isalnum(token[x]))
            {
                //stop the loop and return false as soon as we find a non letter or digit
                return false;
            }
        }
        //return true only after every char has been checked
        return true;
    }
    
    //return false if the 1st char isn't even a letter
    return false;
}


bool LexicalScanner::isASSIGNMENT_OP(const string & token)
// Test whether it is =, the assignment operator
{
    return (token == "=");
}

bool LexicalScanner::isLOGICAL_OP(const string & token)
//Test whether it is a logical operator (such as &&, ||, !)
{
    return (token == "&&" || token == "||" || token == "!");
}

bool LexicalScanner::isNUMERICAL_OP(const string & token)
// Test whether it is one of the following
// numerical operators	 (such as +, -, *, /, %)
{
    return (token == "+" || token == "-" || token == "*" || token == "/" || token == "%");
}

bool LexicalScanner::isRELATIONAL_OP(const string & token)
// Test whether it is one of the following
// numerical operators	 (such as >, ==, <, >=, <=, !=)
{
    return (token == ">" || token == "==" || token == "<" || token == ">=" || token == "<=" || token =="!=");
}


bool LexicalScanner::isSTRING_LITERAL(const string & token)
// Test whether it is a string literals
// (like "Hi Hi", in a pair of double quotes)
{
    //cannot be a string literal if it's only 1 character (i.e. " is not a string literal)
    if (token.size() < 2)
        return false;
    return (token[0] == '\"' && token[token.size() - 1] == '\"');
}

bool LexicalScanner::isCOLON(const string & token)
// Test whether it is a colon :
{
    return (token == ":");
}

bool LexicalScanner::isSEMICOLON(const string & token)
// Test whether it is a semicolon ;
{
    return (token == ";");
}

bool LexicalScanner::isCOMMA(const string & token)
// Test whether it is a comma ,
{
    return (token == ",");
}

bool LexicalScanner::isLEFT_CURLYBRACE(const string & token)
// Test whether it is a left CURLYBRACE {
{
    return (token == "{");
}

bool LexicalScanner::isRIGHT_CURLYBRACE(const string & token)
// Test whether it is a right CURLYBRACE }
{
    return (token == "}");
}

bool LexicalScanner::isLEFT_PARENTHESIS(const string & token)
// Test whether it is a left parenthesis (
{
    return (token == "(");
}

bool LexicalScanner::isRIGHT_PARENTHESIS(const string & token)
// Test whether it is a right parenthesis )
{
    return (token == ")");
}

bool LexicalScanner::isCOMMENT(const string & token)
// Test whether it is comment //
{
    return (token == "//");
}




//**************************************************************************
//Section 3: one function:
//getLexCategoryVectorOneLine and getLexCategoryVectorAllLines
//
//You should extend this function to categorize the tokens in the
//tokenVector and store the categories of the tokens in categoryVector
//by calling the categoriry testing functions described in
//the section 2 above.
//**************************************************************************
void LexicalScanner::getCategoryVectorFromTokenVector(
                                                      const perLineTokenVector & tokenVector,
                                                      perLineCategoryVector & categoryVector)
{
    //Loop through the tokenVector and check the category of each string token
    //Append each category into categoryVector
    
    string tokenVect;
    
    for (int x = 0; x < tokenVector.size(); x++)
    {
        tokenVect = tokenVector[x];
        
        if (isKEYWORD(tokenVect))
        {
            categoryVector.push_back(KEYWORD);
        }
        else if (isID_NAME(tokenVect))
        {
            categoryVector.push_back(ID_NAME);
        }
        else if (isASSIGNMENT_OP(tokenVect))
        {
            categoryVector.push_back(ASSIGNMENT_OP);
        }
        else if (isNUMERICAL_OP(tokenVect))
        {
            categoryVector.push_back(NUMERICAL_OP);
        }
        else if (isLOGICAL_OP(tokenVect))
        {
            categoryVector.push_back(LOGICAL_OP);
        }
        else if (isRELATIONAL_OP(tokenVect))
        {
            categoryVector.push_back(RELATIONAL_OP);
        }
        else if (isNUMERICAL_LITERAL(tokenVect))
        {
            categoryVector.push_back(NUMERICAL_LITERAL);
        }
        else if (isSTRING_LITERAL(tokenVect))
        {
            categoryVector.push_back(STRING_LITERAL);
        }
        else if (isCOLON(tokenVect))
        {
            categoryVector.push_back(COLON);
        }
        else if (isSEMICOLON(tokenVect))
        {
            categoryVector.push_back(SEMICOLON);
        }
        else if (isCOMMA(tokenVect))
        {
            categoryVector.push_back(COMMA);
        }
        else if (isLEFT_PARENTHESIS(tokenVect))
        {
            categoryVector.push_back(LEFT_PARENTHESIS);
        }
        else if (isRIGHT_PARENTHESIS(tokenVect))
        {
            categoryVector.push_back(RIGHT_PARENTHESIS);
        }
        else if (isLEFT_CURLYBRACE(tokenVect))
        {
            categoryVector.push_back(LEFT_CURLYBRACE);
        }
        else if (isRIGHT_CURLYBRACE(tokenVect))
        {
            categoryVector.push_back(RIGHT_CURLYBRACE);
        }
        else if (isCOMMENT(tokenVect))
        {
            categoryVector.push_back(COMMENT);
        }
        else
        {
            categoryVector.push_back(UNKNOWN);
        }
    } //end of for loop
}


//**************************************************************************
// Section 4: a core function for the lexical scanner module
//
// getLexicalInfo is used to
// to get two kinds of lexical information from
// all lines of a program, i.e.
// (1) the vector of token vectors of all lines and
// (2) the vector of category vectors of all lines.
//
// Implementation:
// You should implement them by appropriately using the following functions
//	getPerLineTokenVectFromOneStringObject (implemented in section 1 above), and
//	getCategoryVectorFromTokenVector (to be implemented in section 3 above)
//****************************************************************************
void LexicalScanner::getLexicalInfo(
                                    const vector<string> & linesOfStatements,
                                    vectOfTokenVects & tokenVectors,
                                    vectOfCategoryVects & categoryVectors)
{
    //Loop through the vector of strings linesOfStatements
    //Turn each string into a perLineTokenVector (one line of code)
    //Append the token vector into tokenVectors
    //Get the category vector from the token vector
    
    //Create temp per line vectors
    perLineTokenVector T;
    perLineCategoryVector C;
    
    for (int x = 0; x < linesOfStatements.size(); x++)
    {
        getPerLineTokenVectFromOneStringObject(linesOfStatements[x], T); //turn a line of strings into vector of string tokens
        tokenVectors.push_back(T);
        getCategoryVectorFromTokenVector(T, C); //turns the token info in T into category info in C
        categoryVectors.push_back(C);
        
        T.clear();
        C.clear();
    } //end of for loop
}



//**************************************************************************
// Section 5: one function: displayLexicalInfo
//
// You should implement this function to display the lexical information
// strored in
// a vector of token vectors of all lines of statements, and
// a vector of category vectors of all lines of statements.
//****************************************************************************
void LexicalScanner::displayLexicalInfo(
                                        vectOfTokenVects & tokenVectors,
                                        vectOfCategoryVects & categoryVectors)
{
    if (tokenVectors.size() != categoryVectors.size())
    {
        cout << "# of token vectors inconsistent with # of category vectors." << endl;
        return;
    }
    
    for (size_t i = 0; i<tokenVectors.size(); i++)
    {
        perLineTokenVector tokenVect;
        perLineCategoryVector categoryVect;
        
        tokenVect = tokenVectors[i];
        categoryVect = categoryVectors[i];
        
        if (tokenVect.size() != categoryVect.size())
        {
            cout << "Line " << i
            << ": # of tokens inconsistent with # of category labels." << endl;
            return;
        }
        
        cout << endl
        << "***************************** "
        << "Lexical Info of Line " << i
        << "***************************** "
        << endl;
        
        for (size_t j = 0; j<tokenVect.size(); j++)
        {
            string categoryInfo;
            switch (categoryVect[j])
            {
                case KEYWORD:
                    categoryInfo = "KEYWORD";
                    break;
                case ASSIGNMENT_OP:
                    categoryInfo = "ASSIGNMENT_OP";
                    break;
                case COLON:
                    categoryInfo = "COLON";
                    break;
                case COMMA:
                    categoryInfo = "COMMA";
                    break;
                case COMMENT:
                    categoryInfo = "COMMENT";
                    break;
                case ID_NAME:
                    categoryInfo = "ID_NAME";
                    break;
                case LEFT_CURLYBRACE:
                    categoryInfo = "LEFT_CURLYBRACE";
                    break;
                case LEFT_PARENTHESIS:
                    categoryInfo = "LEFT_PARENTHESIS";
                    break;
                case LOGICAL_OP:
                    categoryInfo = "LOGICAL_OP";
                    break;
                case RIGHT_CURLYBRACE:
                    categoryInfo = "RIGHT_CURLYBRACE";
                    break;
                case RIGHT_PARENTHESIS:
                    categoryInfo = "RIGHT_PARENTHESIS";
                    break;
                case NUMERICAL_LITERAL:
                    categoryInfo = "NUMERICAL_LITERAL";
                    break;
                case NUMERICAL_OP:
                    categoryInfo = "NUMERICAL_OP";
                    break;
                case RELATIONAL_OP:
                    categoryInfo = "RELATIONAL_OP";
                    break;
                case SEMICOLON:
                    categoryInfo = "SEMICOLON";
                    break;
                case STRING_LITERAL:
                    categoryInfo = "STRING_LITERAL";
                    break;
                default:
                    categoryInfo = "UNKNOWN";
            }
            
            cout << "Token["
            << j
            << "]:"
            << tokenVect[j]
            << "\t\t"
            << categoryInfo
            << endl;
        }//end for
        
    }
    
}
