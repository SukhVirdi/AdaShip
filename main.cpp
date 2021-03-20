//Play a game of AdaShip against the computer!
#include <iostream>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "INIReader.h"

using namespace std;

//Function prototypes
int displayGreeting();

class ship //The ship class is not used extensively in actual gameplay - when the grid object is passed a ship object, it places the ships coordinates into the grid
{
  private:
    //This pair make up the coordinates for one end of the ship
    char x1;
  int y1;
  //This pair make up the coordinates for the other end
  char x2;
  int y2;

  int size; //The length of the ship
  string name; //Type (destroyer, submarine, etc.)

  public:
    void inputShip(int s, string n); //Allows the player to input their coordinates for the ship
  //Getter functions
  char getx1() {
    return x1;
  };
  int gety1() {
    return y1;
  };
  char getx2() {
    return x2;
  };
  int gety2() {
    return y2;
  };
};

//Lets the player place their own ships
void ship::inputShip(int s, string n) //When inputing, this function is passed the length of the ship and its name
{
  cout << "Entering coordinates for: " << n << " (" << s << " units)" << endl;
  name = n;
  size = s;

  cout << "Enter the coordinates where you would like to place one end of this ship." << endl;
  cout << "The format is [Letter][Number] of your desired move, e.g. \"F2\"." << endl;
  
  cin >> x1; //x1 is a char, y1 is an int
  cin >> y1;
  x1 = toupper(x1);
  

  //Filter the input for valid numbers!
  while (cin.fail() || y1 > 10 || y1 < 1 || x1 < 'A' || x1 > 'J') //Validates the coordinates entered, reprompts if invalid
  {
    cin.clear();
    cin.ignore(256, '\n');
    cout << "Error: please enter a valid coordinate" << endl;
    cin >> x1 >> y1;
    x1 = toupper(x1);
  }

  cout << "You entered " << x1 << y1 << endl;

  cin.clear();
  cin.ignore(256, '\n');

  cout << "Now, would you like to orient the other end of the ship up, down, left, or right?" << endl;
  string input;
  bool validated = false;

  do {
    getline(cin, input); //Get which direction to orient from the user	
    for (int i = 0; input[i]; i++) input[i] = tolower(input[i]); //Convert the string to all lowercase

    while (input != "up" && input != "down" && input != "left" && input != "right") //Validate the user's input, reprompt if necessary
    {
      cin.clear();
      cin.ignore(256, '\n');
      cout << "Error: please enter up, down, left, or right:" << endl;
      getline(cin, input);
      for (int i = 0; input[i]; i++) input[i] = tolower(input[i]);
    }

    //Length variable is used for checking that the ship fits in the direction it was placed
    int length = size - 1;

    //The following if statements check to make sure the ship fits on the grid when oriented in the selected direction
    if (input == "left") {
      if ((x1 - length) < 'A') {
        cout << "There is no room that direction, please enter a different one" << endl;
      } else {
        x2 = x1 - length;
        y2 = y1;
        validated = true;
      }
    }

    if (input == "right") {
      if ((x1 + length) > 'J') {
        cout << "There is no room that direction, please enter a different one" << endl;
      } else {
        x2 = x1 + length;
        y2 = y1;
        validated = true;
      }
    }

    if (input == "up") {
      if ((y1 - length) < 1) {
        cout << "There is no room that direction, please enter a different one" << endl;
      } else {
        y2 = y1 - length;
        x2 = x1;
        validated = true;
      }
    }

    if (input == "down") {
      if ((y1 + length) > 10) {
        cout << "There is no room that direction, please enter a different one" << endl;
      } else {
        y2 = y1 + length;
        x2 = x1;
        validated = true;
      }
    }
  } while (validated != true);

  //Ensures that x1 and y1 will always be the lesser values of the two
  if (x1 > x2)
    swap(x1, x2);
  if (y1 > y2)
    swap(y1, y2);

}
//END OF SHIP CLASS DECLARATION

class shipGrid //The game board grid - 4 are created: 2 per player
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
    shipGrid(); //Constructor, fills grid array with empty spaces
  void clearGrid(); //Erases grid
  void displayKey(); //Displays info for the player
  void displayGrid(); //Displays grid object
  void generateGrid(); //Generates random Computer Grid
  void editGrid(int index1, int index2, char symbol); //Edits single char in grid array
  bool detectCross(ship s); //Detects whether passed ship conflicts with ships alredy placed
  bool detectWin(); //Scans the board to look for any remaining ship characters - if none exist, returns true
  void placeShip(ship s); //Places passed ship into the game board
  shipGrid playerShot(shipGrid blankGrid); //Lets player shoot at Computer board - blankGrid is passed to update with result of player's shot
  void aiShot(); //Lets the Computer shoot at the player's grid
};

shipGrid::shipGrid() //Constructor, fills grid array with empty spaces
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j] = ' ';
    }
  }
}

void shipGrid::clearGrid() //Resets all grid data to default
{
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      grid[i][j] = ' ';
    }
  }
}

void shipGrid::displayKey() //Simple display function to help the player
{
  cout << "***SYMBOL KEY***" << endl <<
    "#: Your AdaShips    M: Misses    H: Hits" << endl;
}

void shipGrid::displayGrid() //Displays all data in the grid
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

int shipGrid::charToInt(char c) //Used for converting player input
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

char shipGrid::intToChar(int i) //Used for converting array subscript to char for displaying
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

void shipGrid::editGrid(int index1, int index2, char symbol) //Edit a single element in the grid
{
  //Pass the actual point you want to edit - this adjust automatically for off-by-one
  if (index2 == 0) //If this function is passed a 0, it aborts the edit
    return;
  index1--;
  index2--;
  grid[index1][index2] = symbol;
}

void shipGrid::generateGrid() //Generates a random preset Computer grid
{
  //Get random number between 1 and 3
  int map = rand() % 5 + 1;

  //Places ships based on random int
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

bool shipGrid::detectWin() //Scan the grid for a surviving ship character (#). If it contains none, return true
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

bool shipGrid::detectCross(ship s) //Detect whether passed ship object would cross any ships already placed
{
  bool overlap = false;

  //Get the ship's coordinates
  int x1 = charToInt(s.getx1());
  int y1 = s.gety1();
  int x2 = charToInt(s.getx2());
  int y2 = s.gety2();

  x1--;
  y1--;
  x2--;
  y2--;

  if (x1 == x2) //If ship is horizontal
  {
    do {
      if (grid[x1][y1] == '#') {
        //cout << "Cross detected at" << x1 << ", " << y1 << endl;
        overlap = true;
      }
      y1++;

    } while (y1 <= y2 && overlap != true);
  }

  if (y1 == y2) //If ship is vertical
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

void shipGrid::placeShip(ship s) //Place passed ship object into grid
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

  cout << endl << "Ship placed sucessfully!" << endl;
}

//Program greeting and menu
int displayGreeting() {
cout << "░█████╗░██████╗░░█████╗░░██████╗██╗░░██╗██╗██████╗░"<< endl;
cout << "██╔══██╗██╔══██╗██╔══██╗██╔════╝██║░░██║██║██╔══██╗"<< endl;
cout << "███████║██║░░██║███████║╚█████╗░███████║██║██████╔╝"<< endl;
cout << "██╔══██║██║░░██║██╔══██║░╚═══██╗██╔══██║██║██╔═══╝░"<< endl;
cout << "██║░░██║██████╔╝██║░░██║██████╔╝██║░░██║██║██║░░░░░"<< endl;
cout << "╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═╝╚═╝░░░░░"<< endl;
  char userInput;
  cout << "\nHello, and welcome to AdaShips! Select an Option from the Game Menu!" << endl;
  cout << "\n1. One player v computer game." <<
    "\n2. Quit. \n";
  cin >> userInput;
  if (userInput == '1') {
    return 1;
  } else if (userInput == '2') {}
  return 0;
}