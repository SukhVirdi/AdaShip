//Play a game of AdaShip against the computer!

//importing libraries
#include <iostream>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <string>
#include <stdlib.h>

//importing files
#include "headers/Colours.h"

using namespace std;

int displayGreeting();
bool onePlayerVComputer();
bool endGame = false; //When true, program terminates

int main() {
  srand(time(NULL));

  while (!endGame) {
    if (displayGreeting() == 0) {
      return 0;
    };
    endGame = onePlayerVComputer();
  }
}

//Program greeting and menu
int displayGreeting() {
  cout << "░█████╗░██████╗░░█████╗░░██████╗██╗░░██╗██╗██████╗░" << endl;
  cout << "██╔══██╗██╔══██╗██╔══██╗██╔════╝██║░░██║██║██╔══██╗" << endl;
  cout << "███████║██║░░██║███████║╚█████╗░███████║██║██████╔╝" << endl;
  cout << "██╔══██║██║░░██║██╔══██║░╚═══██╗██╔══██║██║██╔═══╝░" << endl;
  cout << "██║░░██║██████╔╝██║░░██║██████╔╝██║░░██║██║██║░░░░░" << endl;
  cout << "╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═╝╚═╝░░░░░" << endl;
  char menuDecision;
  cout << "\nHello, and welcome to AdaShips! Select an Option from the Game Menu!" << endl;
  cout << "\n1. One player v computer game." <<
    "\n2. Quit. \n";
  cin >> menuDecision;
  if (menuDecision == '1') {
    return 1;
  } else if (menuDecision == '2') {} else {
    cout <<  BOLD(FRED("\nError: Please Select an Option from the In-Game Menu")) << endl;
    displayGreeting();
    return 1;
  }
  return 0;
}