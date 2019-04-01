#include "Puzzle.h" // gain access to specification of class
#include <iostream>
#include <iomanip>

using namespace std;

// first constructor
Puzzle::Puzzle()
{
    
    dimension=3;
    layout.resize(dimension);
    
    for (int i=0; i<dimension; i++)
    {
        layout[i].resize(dimension);
    }

    space_i=0;
    space_j=0;
    
}

// second constructor
Puzzle ::Puzzle (int newDim)
{

    dimension=newDim;
    layout.resize(dimension);
    
    for (int i=0; i<dimension; i++)
    {
        layout[i].resize(dimension);
    }
    
    space_i=0;
    space_j=0;
    
}

// Display
void Puzzle :: display()
{
    int count=1;
    
    // cout #####
    for (int i=0; i<dimension*9; i++)
    {
        cout << "#";
    }
    
    cout << " " << endl;
    
    // cout the values
    for (int i=0; i<dimension; i++)
    {
        
        for (int j=0; j<dimension; j++)
        {
            
            if (layout[i][j]!=0)
            {
                cout << setw(9) << left << layout[i][j];
            }
            
                else if (layout[i][j]==0)
                {
                    cout << setw(9) << left << "    ";
                }
                
            if (count%dimension==0)
            {
                cout << "" << endl;
            }
            
            count++;
            
        }
        
    }
    
    // cout #####
        for (int i=0; i<dimension*9; i++)
    {
        cout << "#";
    }
    
    cout << " " << endl << endl;

}

bool Puzzle :: isInOrder()
{
    
    int count=1;
    for (int i=0; i<dimension; i++)
    {
        for (int j=0; j<dimension;j++)
        {
            
            if (i==dimension-1 && j==dimension-1 )
            {
                break;
            }
            
            if (layout[i][j]!=count)
            {
                return false;
            }
            
            count++;
        }
        
    }
    
    return true;
}

bool Puzzle :: moveUp()
{
    
    int temp_i, temp_j;
    
    if (canMoveUp()==true)
    {
        
        
        temp_i=space_i;
        temp_j=space_j;
        

        
        layout[space_i][space_j]=layout[space_i+1][space_j];
        layout[space_i+1][space_j]=0;
        
        space_i=space_i+1;
        
        
    }
    
    else
        {

        }
    
    return true;
}

bool Puzzle :: moveDown()
{
    int temp_i, temp_j;
    
    if (canMoveDown()==true)
    {
        
        
        temp_i=space_i;
        temp_j=space_j;
        
        layout[space_i][space_j]=layout[space_i-1][space_j];
        layout[space_i-1][space_j]=0;
        
        space_i=space_i-1;
    
    }
    
    else
        {

        }
    
    return true;
}

bool Puzzle :: moveLeft()
{
    
    int temp_i, temp_j;
    
    if (canMoveLeft()==true)
    {
        
        temp_i=space_i;
        temp_j=space_j;
        
        layout[space_i][space_j]=layout[space_i][space_j+1];
        layout[space_i][space_j+1]=0;
        
        space_j=space_j+1;
        
        
    }
    
    else
    {

    }
    
    return true;
}

bool Puzzle :: moveRight()
{
    
    
    int temp_i, temp_j;
    
    if (canMoveRight()==true)
    {
        
        temp_i=space_i;
        temp_j=space_j;
        
        
        layout[space_i][space_j]=layout[space_i][space_j-1];
        layout[space_i][space_j-1]=0;
        
        space_j=space_j-1;
        
    }
    
    else
    {

    }
    
    return true;
}

bool Puzzle :: canMoveUp()
{
    
    if (space_i==dimension-1)
        
    {
        return false;
    }
    
    return true;
}

bool Puzzle :: canMoveDown()
{
    
    if (space_i==0)
        
    {
        return false;
    }
    
    return true;
}

bool Puzzle :: canMoveLeft()
{
    
    if (space_j==dimension-1)
        
    {
        return false;
    }
    
    
    return true;
}

bool Puzzle :: canMoveRight()
{
    
    if (space_j==0)
        
    {
        return false;
    }
    
    return true;
}


void Puzzle :: interactWithConsole()
{
    
    Puzzle test, test2;
    
    bool run=true;
    char choice;

    // MENU
    cout << "####################### MOVE THE EMPTY CELL ####################### " << endl;
    cout << "i -> UP      " << "k-> DOWN" << endl;
    cout << "j -> LEFT    " << "l-> RIGHT" << endl;
    
    cout << "####################### SET UP NEW PUZZLE ######################### " << endl;
    cout << "s - > specify a puzzle trough keyboard input" << endl;
    cout << "r - > randomly generate a puzzle" << endl;
    
    cout << "############################# MORE ################################ " << endl;
    cout << "t - > Testing the public methods of the puzzle class" << endl;
    cout << "? - > Display the help menu" << endl;
    
    cout << "################################################################### " << endl;
    
    while (run==true)
        
    {
        
        cout << "Option: " << endl;
        cin >> choice;
        
        if (choice=='s' || choice=='S')
        {

            test.setUpLayoutManually();
            test.display();
            
            cout << " " << endl;
            cout << " " << endl;
            
        }
        
        if (choice=='R' || choice=='r')
        {
            
            test.setRandomLayout();
            test.display();
        }
        
        
        // Directions
        if (choice=='z' || choice=='i')
        {
            test.moveUp();
            test.display();
        }
            
        if (choice=='J' || choice=='j')
        {
            test.moveLeft();
            test.display();
        }
        
        if (choice=='K' || choice=='k')
        {
            test.moveDown();
            test.display();
        }
        
        if (choice=='L' || choice=='l')
        {
            test.moveRight();
            test.display();
        }
        
        if (choice=='?')
        {
            interactWithConsole();
        }
        
        if (test.isInOrder()==true)
        {
            cout << "Congratulations! You solved the puzzle!" << endl << endl;
        }
        
    }
    
}

void Puzzle :: setUpLayoutManually()
{
    
    int temp=0;
    cout << "What is the dimension?" << endl;
    cin >> dimension;
    
    vector <int> temp_vector;
    temp_vector.resize(dimension*dimension);
    
    
    // resize things
    layout.resize(dimension);
    
    for (int i=0; i<dimension; i++)
    {
        layout[i].resize(dimension);
    }
    
    bool runA=true;
    
    while (runA==true)
    {

        bool good=true, runB=true;
        int countB=0;

        cout << "###########################" << endl;
        cout << "Enter the values row by row" << endl;
        cout << "Use 0 to mark empty space" << endl;
        
        while (runB==true)
        {
            cout << countB << ": ";
            cin >> temp;
        
            if (temp>=0 && temp<(dimension*dimension))
            {
                temp_vector[countB]=temp;
                countB++;
            }
            
                else
                {
                    cout << "Invalid input" << endl;
                }
            
            if (countB==temp_vector.size())
            {
                runB=false;
            }
            
        }
        
        // check for duplicates
        for (int j=0; j<(dimension*dimension); j++)
        {
            for (int i=0; i<(dimension*dimension); i++)
            {
                
                if (j!=i)
                {
                    if (temp_vector[j]==temp_vector[i])
                    {
                        good=false;
                    }
                }

            }
            
        }

        if(good==false)
        {
            cout << "This is not a valid input" << endl;
        }
        
            else
            {
                runA=false;
            }
    
    }
    
    // copy from vector to matrix
    int countC=0;
    
    for (int i=0; i<dimension; i++)
    {
        for (int j=0; j<dimension; j++)
        {
            
            if (temp_vector[countC]==0)
            {
                space_i=i;
                space_j=j;
            }
            
            layout[i][j]=temp_vector[countC];
            countC++;
        }
        
    }
    
    cout << "Location of 0: " << "[" << space_i << "]" << "[" << space_j << "]" << endl;

}

void Puzzle :: setRandomLayout()
{
    
    cout << "What do you want the dimensions to be?" << endl;
    cin >> dimension;
    
    layout.resize(dimension);
    
    for (int i=0; i<dimension; i++)
    {
        layout[i].resize(dimension);
    }
    
    // initialize
    int count=1;
    for (int i=0; i<dimension; i++)
    {
        for (int j=0; j<dimension;j++)
        {
            
            layout[i][j]=count;
            
            if (i==dimension-1 && j==dimension-1 )
            {
                layout[i][j]=0;
                space_i=i;
                space_j=j;
            }
            
            count++;
        }
        
    }
    
    for (int i=0; i<(dimension*dimension*dimension); i++)
    {
    
        int tempA=0;
        int randA, randB, randC, randD;
        
        randA=rand()%dimension;
        randB=rand()%dimension;
        randC=rand()%dimension;
        randD=rand()%dimension;

        tempA=layout[randA][randB];
        layout[randA][randB]=layout[randC][randD];
        layout[randC][randD]=tempA;
        
    }
    
    
    for (int i=0; i<dimension; i++)
    {
        for (int j=0; j<dimension; j++)
        {
            if (layout[i][j]==0)
            {
                space_i=i;
                space_j=j;
            }
        }
    }
    
    cout << "Location of 0: " << "[" << space_i << "] " << "[" << space_j << "]" << endl;
    
}



