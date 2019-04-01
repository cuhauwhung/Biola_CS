#ifndef MY_PUZZLE_H
#define MY_PUZZLE_H

#include <iostream>
#include <vector>

using namespace std;

class Puzzle
{
    
public:     //The following members can be called anywhere
    
    Puzzle();
    //      The constructor to initialize the puzzle.
    //      By default, just set the dimension to 3 and
    //      can initialize the puzzle properly as a 3 by 3 puzzle.
    //
    //      You can extend and add another constructor like the following
    //              Puzzle(int dimension);
    //      to make it capable of handling any dimension and
    //      can initialize the puzzle properly as an n by n puzzle.

    Puzzle(int newDim);


    
    void display();         //display the puzzle
    
    void interactWithConsole();
    //      Repeatedly
    //      display the menu of options, ask the user about option to go, and
    //      call the right member function to serve the option.
    
    bool moveUp();          //move the space cell up
    bool moveDown();                //move the space cell down
    bool moveLeft();                //move the space cell left
    bool moveRight();       //move the space cell right
    
    bool canMoveUp();       //check whether we can move the space cell up
    bool canMoveDown();     //check whether we can move the space cell down
    bool canMoveLeft();     //check whether we can move the space cell left
    bool canMoveRight();    //check whether we can move the space cell right
    
    bool isInOrder();       //check whether the puzzle is solved with all the cells in order
    
    void setRandomLayout(); //Reset the puzzle with a random layout
    
    void setUpLayoutManually();
    //Set up the puzzle manually:
    // Based on the dimension of the puzzle n, the method should ask the user to
    // enter the contents of the n by n puzzle.
    //If the user enter things that does not compose a valid puzzle,
    //      the program should ask the user to do it again until it is valid.
    
private:
    int dimension;
    //The dimension of the puzzle, i.e. the number of rows and columns of the puzzle.
    //By default dimension is 3, and the puzzle is a 3 by 3 puzzle.
    
    vector<vector<int>>  layout;
    // layout is a vector of vector of integers to record
    // the current layout of the puzzle.
    // layout[i][j] stores the number appearing on row i and column j of the puzzle.
    //
    // For the empty cell,
    // we use the number 0 to indicate that the cell should be display as an empty cell.
    
    
    // The following two data members record the current location of the empty cell.
    // In other words, the empty cell is currently at row space_i and column space_j
    // of the puzzle and the contents of layout[space_i] [ space_j] is 0.
    int space_i;            //The space cell is in layout[space_i][space_j] of the
    int space_j;            //the puzzle.
    
};

#endif

