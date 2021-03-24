#include <iostream>
#include "headers/AdaShipGrid.h"
#include "headers/Colours.h"

using namespace std;

AdaShipGrid::AdaShipGrid() //Constructor, fills grid array with empty spaces
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j] = ' ';
    }
  }
}

void AdaShipGrid::clearGrid() //Resets all grid data to default
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j] = ' ';
    }
  }
}

void AdaShipGrid::displayKey() //Simple display function to help the player
{
  cout << "\n***SYMBOL KEY***" << endl <<
    "#: Your AdaShips    M: Misses    H: Hits" << endl;
}

void AdaShipGrid::displayGrid() //Displays all data in the grid
{
  cout << "   A   B   C   D   E   F   G   H   I   J" << endl <<
    "1 [" << grid[0][0] << "] [" << grid[0][1] << "] [" << grid[0][2] << "] [" << grid[0][3] << "] [" << grid[0][4] << "] [" << grid[0][5] << "] [" << grid[0][6] << "] [" << grid[0][7] << "] [" << grid[0][8] << "] [" << grid[0][9] << "]" << endl <<
    "2 [" << grid[1][0] << "] [" << grid[1][1] << "] [" << grid[1][2] << "] [" << grid[1][3] << "] [" << grid[1][4] << "] [" << grid[1][5] << "] [" << grid[1][6] << "] [" << grid[1][7] << "] [" << grid[1][8] << "] [" << grid[1][9] << "]" << endl <<
    "3 [" << grid[2][0] << "] [" << grid[2][1] << "] [" << grid[2][2] << "] [" << grid[2][3] << "] [" << grid[2][4] << "] [" << grid[2][5] << "] [" << grid[2][6] << "] [" << grid[2][7] << "] [" << grid[2][8] << "] [" << grid[2][9] << "]" << endl <<
    "4 [" << grid[3][0] << "] [" << grid[3][1] << "] [" << grid[3][2] << "] [" << grid[3][3] << "] [" << grid[3][4] << "] [" << grid[3][5] << "] [" << grid[3][6] << "] [" << grid[3][7] << "] [" << grid[3][8] << "] [" << grid[3][9] << "]" << endl <<
    "5 [" << grid[4][0] << "] [" << grid[4][1] << "] [" << grid[4][2] << "] [" << grid[4][3] << "] [" << grid[4][4] << "] [" << grid[4][5] << "] [" << grid[4][6] << "] [" << grid[4][7] << "] [" << grid[4][8] << "] [" << grid[4][9] << "]" << endl <<
    "6 [" << grid[5][0] << "] [" << grid[5][1] << "] [" << grid[5][2] << "] [" << grid[5][3] << "] [" << grid[5][4] << "] [" << grid[5][5] << "] [" << grid[5][6] << "] [" << grid[5][7] << "] [" << grid[5][8] << "] [" << grid[5][9] << "]" << endl <<
    "7 [" << grid[6][0] << "] [" << grid[6][1] << "] [" << grid[6][2] << "] [" << grid[6][3] << "] [" << grid[6][4] << "] [" << grid[6][5] << "] [" << grid[6][6] << "] [" << grid[6][7] << "] [" << grid[6][8] << "] [" << grid[6][9] << "]" << endl <<
    "8 [" << grid[7][0] << "] [" << grid[7][1] << "] [" << grid[7][2] << "] [" << grid[7][3] << "] [" << grid[7][4] << "] [" << grid[7][5] << "] [" << grid[7][6] << "] [" << grid[7][7] << "] [" << grid[7][8] << "] [" << grid[7][9] << "]" << endl <<
    "9 [" << grid[8][0] << "] [" << grid[8][1] << "] [" << grid[8][2] << "] [" << grid[8][3] << "] [" << grid[8][4] << "] [" << grid[8][5] << "] [" << grid[8][6] << "] [" << grid[8][7] << "] [" << grid[8][8] << "] [" << grid[8][9] << "]" << endl <<
    "10[" << grid[9][0] << "] [" << grid[9][1] << "] [" << grid[9][2] << "] [" << grid[9][3] << "] [" << grid[9][4] << "] [" << grid[9][5] << "] [" << grid[9][6] << "] [" << grid[9][7] << "] [" << grid[9][8] << "] [" << grid[9][9] << "]" << endl;
}

int AdaShipGrid::charToInt(char c) //Used for converting player input
{
  switch (c) {
  case 'A':
    return 1;
  case 'B':
    return 2;
  case 'C':
    return 3;
  case 'D':
    return 4;
  case 'E':
    return 5;
  case 'F':
    return 6;
  case 'G':
    return 7;
  case 'H':
    return 8;
  case 'I':
    return 9;
  case 'J':
    return 10;
  }

  return 0;
}

char AdaShipGrid::intToChar(int i) //Used for converting array subscript to char for displaying
{
  switch (i) {
  case 1:
    return 'A';
  case 2:
    return 'B';
  case 3:
    return 'C';
  case 4:
    return 'D';
  case 5:
    return 'E';
  case 6:
    return 'F';
  case 7:
    return 'G';
  case 8:
    return 'H';
  case 9:
    return 'I';
  case 10:
    return 'J';
  }

  return 0;
}

void AdaShipGrid::editGrid(int index1, int index2, char symbol) //Edit a single element in the grid
{
  //Pass the actual point you want to edit - this adjust automatically for off-by-one
  if (index2 == 0) //If this function is passed a 0, it aborts the edit
    return;
  index1--;
  index2--;
  grid[index1][index2] = symbol;
}

void AdaShipGrid::generateGrid() //Generates a random preset Computer grid
{
  //Get random number between 1 and 3
  int map = rand() % 5 + 1;

  //Places AdaShips based on random int
  switch (map) {
  case 1:
    grid[1][0] = '#';
    grid[2][0] = '#';
    grid[1][5] = '#';
    grid[1][6] = '#';
    grid[1][7] = '#';
    grid[1][8] = '#';
    grid[1][9] = '#';
    grid[5][3] = '#';
    grid[5][4] = '#';
    grid[5][5] = '#';
    grid[4][7] = '#';
    grid[5][7] = '#';
    grid[6][7] = '#';
    grid[7][7] = '#';
    grid[7][9] = '#';
    grid[8][9] = '#';
    grid[9][9] = '#';
    break;

  case 2:
    grid[0][0] = '#';
    grid[0][1] = '#';
    grid[0][2] = '#';
    grid[1][8] = '#';
    grid[2][8] = '#';
    grid[3][8] = '#';
    grid[4][8] = '#';
    grid[5][8] = '#';
    grid[5][4] = '#';
    grid[6][4] = '#';
    grid[7][5] = '#';
    grid[7][6] = '#';
    grid[7][7] = '#';
    grid[8][1] = '#';
    grid[8][2] = '#';
    grid[8][3] = '#';
    grid[8][4] = '#';
    break;

  case 3:
    grid[0][3] = '#';
    grid[1][3] = '#';
    grid[2][3] = '#';
    grid[3][3] = '#';
    grid[4][0] = '#';
    grid[5][0] = '#';
    grid[6][0] = '#';
    grid[2][9] = '#';
    grid[3][9] = '#';
    grid[4][9] = '#';
    grid[5][9] = '#';
    grid[6][9] = '#';
    grid[6][2] = '#';
    grid[6][3] = '#';
    grid[6][4] = '#';
    grid[8][7] = '#';
    grid[9][7] = '#';
    break;

  case 4:
    grid[1][0] = '#';
    grid[2][0] = '#';
    grid[3][0] = '#';
    grid[7][0] = '#';
    grid[8][0] = '#';
    grid[9][0] = '#';
    grid[6][2] = '#';
    grid[6][3] = '#';
    grid[6][4] = '#';
    grid[6][5] = '#';
    grid[6][6] = '#';
    grid[9][2] = '#';
    grid[9][3] = '#';
    grid[9][4] = '#';
    grid[9][5] = '#';
    grid[8][7] = '#';
    grid[8][8] = '#';
    break;

  case 5:
    grid[1][5] = '#';
    grid[1][6] = '#';
    grid[1][8] = '#';
    grid[2][8] = '#';
    grid[3][8] = '#';
    grid[6][0] = '#';
    grid[6][1] = '#';
    grid[6][2] = '#';
    grid[6][4] = '#';
    grid[7][4] = '#';
    grid[8][4] = '#';
    grid[9][4] = '#';
    grid[4][6] = '#';
    grid[5][6] = '#';
    grid[6][6] = '#';
    grid[7][6] = '#';
    grid[8][6] = '#';
    displayGrid();
    break;
  }
}

bool AdaShipGrid::detectWin() //Scan the grid for a surviving ship character (#). If it contains none, return true
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (grid[i][j] == '#') {
        return false;
      }
    }
  }
  return true;
}

bool AdaShipGrid::detectCross(AdaShip s) //Detect whether passed ship object would cross any ships already placed
{
  bool overlap = false;

  //Get the AdaShip's coordinates
  int x1 = charToInt(s.getx1());
  int y1 = s.gety1();
  int x2 = charToInt(s.getx2());
  int y2 = s.gety2();

  x1--;
  y1--;
  x2--;
  y2--;

  if (x1 == x2) //If AdaShip is horizontal
  {
    do {
      if (grid[x1][y1] == '#') {
        //cout << "Cross detected at" << x1 << ", " << y1 << endl;
        overlap = true;
      }
      y1++;

    } while (y1 <= y2 && overlap != true);
  }

  if (y1 == y2) //If AdaShip is vertical
  {
    do {
      if (grid[x1][y1] == '#') {
        //cout << "Cross detected at" << x1 << ", " << y1 << endl;
        overlap = true;
      }
      x1++;
    } while (x1 <= x2 && overlap != true);
  }

  return overlap;
}

void AdaShipGrid::placeAdaShip(AdaShip s) //Place passed ship object into grid
{
  int x1 = charToInt(s.getx1());
  int y1 = s.gety1();
  int x2 = charToInt(s.getx2());
  int y2 = s.gety2();

  if (x1 == x2) {
    do {
      editGrid(y1, x1, '#');
      y1++;
    } while (y1 <= y2);
  }

  if (y1 == y2) {
    do {
      editGrid(y1, x1, '#');
      x1++;
    } while (x1 <= x2);
  }

  cout << endl << "AdaShip placed sucessfully!" << endl;
}

void AdaShipGrid::aiShot() //Computer takes a shot at player grid
{
  int x;
  int y;
  bool newShot = true; //Bool to determine wheter the Computer chose a new spot to - at
  string status; //Holds whether Computer hit or missed

  do {
    rand();
    rand();
    rand(); //Generate a random coordinate on the grid 
    x = rand() % 10;
    rand();
    rand();
    rand();
    y = rand() % 10;

    //Prevent the Computer from firing at a square they've already shot at
    if (grid[x][y] == 'X' || grid[x][y] == 'H') {
      newShot = false;
    } else if (grid[x][y] == ' ') //If it's an empty spot, Computer missed
    {
      grid[x][y] = 'M';
      status = BOLD(FRED("The Computer has missed their fired torpedo at your AdaShip Fleet."));
      newShot = true;
    } else if (grid[x][y] == '#') //if there was a AdaShip there, Computer hit
    {
      grid[x][y] = 'H';
      status = BOLD(FGRN("The Computer has successfully fired a torpedo that has struck your AdaShip Fleet."));
      newShot = true;
    }

  } while (newShot == false); //Repeat until Computer hits a spot it hasn't tried

  char xTemp = intToChar(x + 1); //Convert coordinate to char so it can be displayed
  cout << "Computer fired at " << xTemp << y + 1 << ". " << endl << status << endl;

  string xStr(1, xTemp);
}

AdaShipGrid AdaShipGrid::playerShot(AdaShipGrid blankGrid) //Lets player take shot at Computer grid
{
  char xTemp;
  int x;
  int y;

  bool newShot = false;

  cout << "Enter where you want the torpedo to fire (e.g. F7): " << endl;
  
  while (newShot == false) {
    cin >> xTemp;
    cin >> y;
    xTemp = toupper(xTemp);

    while (cin.fail() || y > 10 || y < 1 || xTemp < 'A' || xTemp > 'J') //Validate the user's input
    {
      cin.clear();
      cin.ignore(256, '\n');
      cout << BOLD(FRED("Error: please enter a valid coordinate."))<< endl;
      cin >> xTemp >> y;
      xTemp = toupper(xTemp);
    }

    cout << endl << "You have fired at " << xTemp << y << endl;

    cin.clear();
    cin.ignore(256, '\n');

    //Reduce the y by one to account for the grid array starting at 0, not 1
    y--;

    x = charToInt(xTemp);
    x--;

    //If the player shoots at a space they already shot at, ask them to choose a different one
    if (grid[x][y] == 'H' || grid[x][y] == 'H' || grid[x][y] == 'M') {
      cout << BOLD(FRED( "Error: You've already shot there! Please enter a different coordinate.")) << endl;
      newShot = false;
    } else if (grid[x][y] == '#') //If hit an enemy AdaShip, display hit, change Computer grid and blankGrid to reflect changes
    {
      cout << BOLD(FGRN("Your fired torpedo has successfully hit an enemy AdaShip.")) << endl;
      blankGrid.editGrid(y + 1, x + 1, 'H');
      grid[x][y] = 'H';

      string xStr(1, xTemp);
      newShot = true;
    } else if (grid[x][y] == ' ') //Same as above, except for a miss
    {
      cout << BOLD(FRED("Your fired torpedo has failed to hit an enemy AdaShip.")) << endl;
      grid[x][y] = 'M';
      blankGrid.editGrid(y + 1, x + 1, 'M');

      string xStr(1, xTemp);
      newShot = true;
    }
  }

  return blankGrid; //Return the updated blankGrid
}
