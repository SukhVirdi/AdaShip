//Play a game of AdaShip against the computer!
#include <iostream>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <string>
#include <stdlib.h>

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