#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include "lexScanner.h"
using namespace std;


class interpreter
{
    
public:
    static void executeProgram(vector< string > &sourceProgram);
    static void checkforFunctions (vector< string > &sourceProgram);

};





#endif
