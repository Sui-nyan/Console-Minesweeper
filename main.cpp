#include <windows.h>
#include <iostream>
#include "Int2.h"
#include "MinesweeperGrid.h"
using namespace std;

int2 RequestLocationInput();

int GetNumberFromUser(const string& msg);

void RevealOrFlag(MinesweeperGrid& grid, int2 location);

int main()
{
    MinesweeperGrid m = MinesweeperGrid(10,10, 0.01);
    m.PrintGrid();
    while(!m.CheckGameWon()) {
        int2 location = RequestLocationInput();
        if(m.LocationInBounds(location)) {
            RevealOrFlag(m, location);
            m.PrintGrid();
        }
        else {
            cout << "Coordinates exceeds boundaries. Please try again." << endl;
        }
    }

    cout << "Congrats. Game Won." << endl;
    exit(0);
}

/**
 * Asks user to reveal or flag until either is chosen
 * @param grid
 * @param location
 */
void RevealOrFlag(MinesweeperGrid& grid, int2 location) {
    cout <<"What do you want to do at " << location << endl;
    cout << "Set Flag or Reveal?(F/R)" << endl;
    char input;
    while(true) {
        cin >> input;

        switch(input) {
            case 'F':case 'f':
                if(grid.IsRevealed(location)) {
                    cout << "You cannot flag revealed cells." << endl; return;
                }
                grid.FlagCellAtLocation(location); return;
            case 'R': case 'r':
                if(grid.IsFlagged(location)) {
                    cout << "You cannot reveal flagged cells." << endl; return;
                }
                    grid.RevealNeighboringCellsAtLocation(location); return;

            default: cout << "Invalid Argument. Please try again." << endl;
                break;
        }
    }
}

/**
 * Requests X and Y coordinates from user
 * @return user input as location
 */
int2 RequestLocationInput() {
    int x,y;

    x = GetNumberFromUser("Please enter the X-coordinate: ");
    y = GetNumberFromUser("Please enter the Y-coordinate: ");

    return {x,y};
}
/**
 * Requests the user for an input until the user provides a number
 * @param msg
 * @return
 */
int GetNumberFromUser(const string& msg) {
    string input;
    cout << msg << endl;

    while(true) {
        try {
            cin >> input;
            return stoi(input);
        } catch (const std::exception&) {
            cout << "Invalid Argument. Please try again." << endl;
        }
    }
}


