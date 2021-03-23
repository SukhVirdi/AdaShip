#include <iostream>
#include "headers/Colours.h"
#include "headers/INIReader.h"
#include "headers/AdaShipGrid.h"

using namespace std;

//Lets the player place their own AdaShips
void AdaShip::inputAdaShip(int s, string n) //When inputing, this function is passed the length of the ship and its name
{
  name = n;
  size = s;
  cout << "\nEnter your coordinates for the " << n << " (" << s << " units) to place one end of this AdaShip."<< endl;

  cout << "The format is [Letter][Number] of your desired move, e.g. \"F2\"." << endl;
  
  cin >> x1; //x1 is a char, y1 is an int
  cin >> y1;
  x1 = toupper(x1);
  

  //Filter the input for valid numbers!
  while (cin.fail() || y1 > 10 || y1 < 1 || x1 < 'A' || x1 > 'J') //Validates the coordinates entered, reprompts if invalid
  {
    cin.clear();
    cin.ignore(256, '\n');
    cout << BOLD(FRED("Error: please enter a valid coordinate.")) << endl;
    cin >> x1 >> y1;
    x1 = toupper(x1);
  }

  cout << "You entered " << x1 << y1 << endl;

  cin.clear();
  cin.ignore(256, '\n');

  cout << "Now, would you like to orient the other end of the AdaShip up, down, left, or right?" << endl;
  string input;
  bool validated = false;

  do {
    getline(cin, input); //Get which direction to orient from the user	
    for (int i = 0; input[i]; i++) input[i] = tolower(input[i]); //Convert the string to all lowercase

    while (input != "up" && input != "down" && input != "left" && input != "right") //Validate the user's input, reprompt if necessary
    {
      cin.clear();
      cin.ignore(256, '\n');
      cout << BOLD(FRED("Error: please enter up, down, left, or right:")) << endl;
      getline(cin, input);
      for (int i = 0; input[i]; i++) input[i] = tolower(input[i]);
    }

    //Length variable is used for checking that the AdaShip fits in the direction it was placed
    int length = size - 1;

    //The following if statements check to make sure the AdaShip fits on the grid when oriented in the selected direction
    if (input == "left") {
      if ((x1 - length) < 'A') {
        cout << BOLD(FRED("Error: There is no room that direction, please enter a different one." )) << endl;
      } else {
        x2 = x1 - length;
        y2 = y1;
        validated = true;
      }
    }

    if (input == "right") {
      if ((x1 + length) > 'J') {
        cout << BOLD(FRED("Error: There is no room that direction, please enter a different one." )) << endl;
      } else {
        x2 = x1 + length;
        y2 = y1;
        validated = true;
      }
    }

    if (input == "up") {
      if ((y1 - length) < 1) {
        cout << BOLD(FRED("Error: There is no room that direction, please enter a different one." )) << endl;
      } else {
        y2 = y1 - length;
        x2 = x1;
        validated = true;
      }
    }

    if (input == "down") {
      if ((y1 + length) > 10) {
        cout << BOLD(FRED("Error: There is no room that direction, please enter a different one." )) << endl;
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