/*
 * Name: Mac Howe 
 * Date Submitted: 9/20/23
 * Lab Section: 002
 * Assignment Name: grouping 
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;





//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string fileName){
    ifstream file(fileName);
    char c;
    if (file.is_open()) {
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                file >> c;
                if (c == '.'){
                    grid[i][j] = 0;
                }else{
                    grid[i][j] = 1;
                }
            }
        }
        file.close();

        // Check every square in the grid
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                if (grid[i][j] == 1) {
                    vector<GridSquare> group;
                    // Start finding the group for this square
                    findGroup(i, j, group);  
                    if (!group.empty()) {
                        // Add the found group to the groups vector
                        groups.push_back(group);  
                    }
                }
            }
        }
    }else{
        cerr << "file failed to open" << endl;
        exit(1);
    }


}

void Grouping::findGroup(int row, int col, vector<GridSquare>& group){
    // stop if out of bounds on the grid
    if (row >= 10 || row < 0 || col >= 10 || col < 0 ) return;
    // stop if its not a marked square (0 or -1)
    if (grid[row][col] != 1) return;


    // set the grid square as -1 meaning it was 1 but has been added to a group
    // This allows me not to have to look in the groups already made
    grid[row][col] = -1;

    // adds GridSquare to group
    group.push_back(GridSquare(row, col));

    // Check left, up, right, then down (adjacent squares)
    findGroup(row, col - 1, group); 
    findGroup(row - 1, col, group); 
    findGroup(row, col + 1, group); 
    findGroup(row + 1, col, group); 


}




// //Simple main function to test Grouping
// //Be sure to comment out main() before submitting
// int main()
// {
//     Grouping input1("input1.txt");
//     input1.printGroups();
    
//     return 0;
// }

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}