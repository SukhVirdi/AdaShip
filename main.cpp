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