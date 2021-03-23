#include "AdaShip.h"

#ifndef ADASHIPGRID_H
#define ADASHIPGRID_H


class AdaShipGrid //The game board grids: Multiple are created when the game runs: e.g. to hold player AdaShips, for AI AdaShips, also for the player to fill in as the game progresses...
{
  private:
    char grid[10][10]; //2D-Array containing all the game board data

  int aiShotX;
  int aiShoty;
  bool lastShotSuccess;

  //Used for converting user-inputed chars to ints for array reference
  int charToInt(char c);
  char intToChar(int i);

  public:
    AdaShipGrid(); //Constructor, fills grid array with empty spaces
  void clearGrid(); //Erases grid
  void displayKey(); //Displays info for the player
  void displayGrid(); //Displays grid object
  void generateGrid(); //Generates random Computer Grid
  void editGrid(int index1, int index2, char symbol); //Edits single char in grid array
  bool detectCross(AdaShip s); //Detects whether passed AdaShip conflicts with ships already placed
  bool detectWin(); //Scans the board to look for any remaining ship characters - if none exist, returns true
  void placeAdaShip(AdaShip s); //Places passed AdaShip into the game board
  AdaShipGrid playerShot(AdaShipGrid blankGrid); //Lets player shoot at AI board - blankGrid is passed to update with result of player's shot
  void aiShot(); //Lets the Computer shoot at the player's grid
};

#endif 