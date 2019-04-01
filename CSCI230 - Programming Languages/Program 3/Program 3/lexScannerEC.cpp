// simpleScanner.cpp gives some some hints on the implementation of your lexical scanner
// function. For example, it shows how you can break a statementinto basic
// components (tokens) and determine their categories.
#include <stdio.h>
#include <string.h>
#include <iostream>  // for basic iostream operations
#include <cctype>    // to check C character type using function like isdigit()
#include <string>
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




void LexicalScanner::getPerLineTokenVectFromOneStringObject(const string statement, perLineTokenVector & tokenVector)

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
	if (token == "function" || token == "read" || token == "display" || token == "if" || token == "else" || token == "return" || token == "while")
		return true;
	else
		return false;
}

bool LexicalScanner::isID_NAME(const string & token)
// Testwhether it is an identifier, i.e. names of variables, labels, and functions
{
	// if is a keyword/string literal/numerical literal, then return false, because it is not an ID name
	if (isKEYWORD(token) || isSTRING_LITERAL(token) || isNUMERICAL_LITERAL(token) || (isdigit(token[0])))
		return false;

	// loop through the whole token
	for (int i = 0; i < token.size(); i++)
	{
		// make sure all the values in token are alphanumeric
		if (!isalnum(token[i]))
			return false;
	}

	// if not false for both above, then retun true; it is indeed an ID_NAME
	return true;
}

bool LexicalScanner::isASSIGNMENT_OP(const string & token)
{
	// if it is =, return true
	if (token == "=")
		return true;
	else
		return false;
}

bool LexicalScanner::isLOGICAL_OP(const string & token)
{
	// if it it a logical operator, then return true
	if (token == "!" || token == "||" || token == "&&")
		return true;
	else
		return false;
}

bool LexicalScanner::isNUMERICAL_OP(const string & token)
// Test whether it is one of the following
// numerical operators (such as +, -, *, /, %)
{
	// if numerical operator then return true
	if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%")
		return true;
	else
		return false;
}

bool LexicalScanner::isRELATIONAL_OP(const string & token)
// Test whether it is one of the following
// numerical operators (such as <, >, <=, >=, ==, !=)
{
	// if relational opeartor then return true
	if (token == "<" || token == ">" || token == "<=" || token == ">=" || token == "==" || token == "!=")
		return true;
	else
		return false;
}

bool LexicalScanner::isSTRING_LITERAL(const string & token)
// Test whether it is a string literals
// (like "Hi Hi", in a pair of double quotes)
{
	// check to make sure that the first and last element is a double quote
	// declare temp as index of token.size()-1
	int Temp = token.size() - 1;

	// make sure the first and the token.size()-1 are double quotes
	if (token[0] == DOUBLE_QUOTE && token[Temp] == DOUBLE_QUOTE)
		return true;
	else
		return false;

}

bool LexicalScanner::isCOLON(const string & token)
// Test whether it is a colon :
{
	// if colon then return true
	if (token == ":")
		return true;
	else
		return false;
}

bool LexicalScanner::isSEMICOLON(const string & token)
// Test whether it is a semicolon ;
{
	// if semi-colon then return true
	if (token == ";")
		return true;
	else
		return false;
}

bool LexicalScanner::isCOMMA(const string & token)
// Test whether it is a comma ,
{
	// if comma then return true
	if (token == ",")
		return true;
	else
		return false;
}

bool LexicalScanner::isLEFT_CURLYBRACE(const string & token)
// Test whether it is a left CURLYBRACE {
{
	// if left parantehsis then return true
	if (token == "{")
		return true;
	else
		return false;
}

bool LexicalScanner::isRIGHT_CURLYBRACE(const string & token)
// Test whether it is a right CURLYBRACE }
{
	// if right parantehsis then return true
	if (token == "}")
		return true;
	else
		return false;
}

bool LexicalScanner::isLEFT_PARENTHESIS(const string & token)
// Test whether it is a left parenthesis (
{
	// if left parantehsis then return true
	if (token == "(")
		return true;
	else
		return false;
}

bool LexicalScanner::isRIGHT_PARENTHESIS(const string & token)
// Test whether it is a right parenthesis )
{
	// if right parantehsis then return true
	if (token == ")")
		return true;
	else
		return false;
}

bool LexicalScanner::isCOMMENT(const string & token)
{
	// if its double slash return true, because its start of a comment
	if (token == "//")
		return true;
	else
		return false;
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
	// loop through the whole token vector and try to categorize everything
	for (int i = 0; i < tokenVector.size(); i++)
	{
		// try to call the functions from section 2 and find out what each token belongs in which category
		// go through all the possible options. If none of the optiosn get passed then just output unknown
		if (isKEYWORD(tokenVector[i]) == true)
			categoryVector.push_back(KEYWORD);

		else if (isID_NAME(tokenVector[i]) == true)
			categoryVector.push_back(ID_NAME);

		else if (isASSIGNMENT_OP(tokenVector[i]) == true)
			categoryVector.push_back(ASSIGNMENT_OP);

		else if (isNUMERICAL_OP(tokenVector[i]) == true)
			categoryVector.push_back(NUMERICAL_OP);

		else if (isLOGICAL_OP(tokenVector[i]) == true)
			categoryVector.push_back(LOGICAL_OP);

		else if (isRELATIONAL_OP(tokenVector[i]) == true)
			categoryVector.push_back(RELATIONAL_OP);

		else if (isNUMERICAL_LITERAL(tokenVector[i]) == true)
			categoryVector.push_back(NUMERICAL_LITERAL);

		else if (isSTRING_LITERAL(tokenVector[i]) == true)
			categoryVector.push_back(STRING_LITERAL);

		else if (isCOLON(tokenVector[i]) == true)
			categoryVector.push_back(COLON);

		else if (isSEMICOLON(tokenVector[i]) == true)
			categoryVector.push_back(SEMICOLON);

		else if (isCOMMA(tokenVector[i]) == true)
			categoryVector.push_back(COMMA);

		else if (isLEFT_PARENTHESIS(tokenVector[i]) == true)
			categoryVector.push_back(LEFT_PARENTHESIS);

		else if (isRIGHT_PARENTHESIS(tokenVector[i]) == true)
			categoryVector.push_back(RIGHT_PARENTHESIS);

		else if (isLEFT_CURLYBRACE(tokenVector[i]) == true)
			categoryVector.push_back(LEFT_CURLYBRACE);

		else if (isRIGHT_CURLYBRACE(tokenVector[i]) == true)
			categoryVector.push_back(RIGHT_CURLYBRACE);

		else if (isCOMMENT(tokenVector[i]) == true)
			categoryVector.push_back(COMMENT);

		else
			categoryVector.push_back(UNKNOWN);
	}
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
// getPerLineTokenVectFromOneStringObject (implemented in section 1 above), and
// getCategoryVectorFromTokenVector (to be implemented in section 3 above)
//****************************************************************************
void LexicalScanner::getLexicalInfo(
	const vector<string> & linesOfStatements,
	vectOfTokenVects & tokenVectors,
	vectOfCategoryVects & categoryVectors)
{
	// declarations
	perLineTokenVector tokenVector;
	perLineCategoryVector categoryVector;

	// extract and analyze each line one by one
	for (int i = 0; i < linesOfStatements.size(); i++)
	{
		// get all the tokens from the string object and place it in the token vector
		getPerLineTokenVectFromOneStringObject(linesOfStatements[i], tokenVector);

		// get the categories from the token vector
		getCategoryVectorFromTokenVector(tokenVector, categoryVector);

		// insert the token to the token vectors and then clear the token vector
		tokenVectors.push_back(tokenVector);
		tokenVector.clear();

		// insert the token category into the category vectors and then clear the categoryvector
		categoryVectors.push_back(categoryVector);
		categoryVector.clear();
	}
}


//**************************************************************************
// Section 5: one function: displayLexicalInfo
//
// You should implement this function to display the lexical information
// strored in
// a vector of token vectors of all lines of statements, and
// a vector of category vectors of all lines of statements.
//****************************************************************************
void LexicalScanner::displayLexicalInfo(vectOfTokenVects & tokenVectors, vectOfCategoryVects & categoryVectors)
{

	// make sure both vector sizes are consistent
	if (tokenVectors.size() != categoryVectors.size())
	{
		cout << "# of token vectors inconsistent with # of category vectors." << endl;
		return;
	}

	// declarations
	int i = 0, j = 0;

	// loop until the end
	while (i < tokenVectors.size())
	{
		// make sure j gets refreshed after every line
		j = 0;

		// delcarations
		perLineTokenVector tokenVect;
		perLineCategoryVector categoryVect;

		// go through the tokenVectors and category Vectors and place it in the repsective perLine vector
		tokenVect = tokenVectors[i];
		categoryVect = categoryVectors[i];

		// if inconsitent, return
		if (tokenVect.size() != categoryVect.size())
		{
			cout << "Line " << i << ": # of tokens inconsistent with # of category labels." << endl;
			return;
		}

		// display
		cout << endl
			<< "***************************** " << "Lexical Info of Line " << i << "***************************** " << endl;

		// loop until the end of the tokenVect
		while (j < tokenVect.size())
		{
			string categoryInfo;

			// check what the label in the cateogry vect is and then assign label
			// go through all the information
			if (categoryVect[j] == KEYWORD)
				categoryInfo = "KEYWORD";

			else if (categoryVect[j] == ASSIGNMENT_OP)
				categoryInfo = "ASSIGNEMT_OP";

			else if (categoryVect[j] == COLON)
				categoryInfo = "COLON";

			else if (categoryVect[j] == COMMA)
				categoryInfo = "COMMA";

			else if (categoryVect[j] == COMMENT)
				categoryInfo = "COMMENT";

			else if (categoryVect[j] == ID_NAME)
				categoryInfo = "ID_NAME";

			else if (categoryVect[j] == LEFT_CURLYBRACE)
				categoryInfo = "LEFT_CURLYBRACE";

			else if (categoryVect[j] == LEFT_PARENTHESIS)
				categoryInfo = "LEFT_PARENTHESIS";

			else if (categoryVect[j] == LOGICAL_OP)
				categoryInfo = "LOGICAL_OP";

			else if (categoryVect[j] == RIGHT_CURLYBRACE)
				categoryInfo = "RIGHT_CURLYBRACE";

			else if (categoryVect[j] == RIGHT_PARENTHESIS)
				categoryInfo = "RIGHT_PARENTHESIS";

			else if (categoryVect[j] == NUMERICAL_LITERAL)
				categoryInfo = "NUMERICAL_LITERAL";

			else if (categoryVect[j] == NUMERICAL_OP)
				categoryInfo = "NUMERICAL_OP";

			else if (categoryVect[j] == RELATIONAL_OP)
				categoryInfo = "RELATIONAL_OP";

			else if (categoryVect[j] == SEMICOLON)
				categoryInfo = "SEMICOLON";

			else if (categoryVect[j] == STRING_LITERAL)
				categoryInfo = "STRING_LITERAL";

			else
				categoryInfo = "UNKNOWN";

			// display
			cout << "Token[" << j << "]:" << tokenVect[j] << "\t\t" << categoryInfo << endl;
			j++;

		}

		i++;

	}
}


