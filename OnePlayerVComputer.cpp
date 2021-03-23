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
#include "headers/INIReader.h"
#include "headers/AdaShip.h"
#include "headers/AdaShipGrid.h"

using namespace std;

bool onePlayerVComputer() {

  AdaShipGrid playerGrid; //Holds the player's ships
  AdaShipGrid blankGrid; //Holds the screen the player sees when shooting at enemy ships
  AdaShipGrid aiGrid; //Holds the Computer's ships

  //Empty ship objects, to be placed by the player
  AdaShip playerDestroyer;
  AdaShip playerSub;
  AdaShip playerPatrolBoat;
  AdaShip playerBattle;
  AdaShip playerCarrier;

  bool overlap;
  bool endGame = false; //When true, program terminates

  //Keeps a running tally of wins by each player
  int playerWins = 0;
  int aiWins = 0;

  //Program will offer to place your AdaShips automatically
  cout << "Would you like to place your own AdaShips, or have them placed automatically for you?" << endl <<
    "Enter \"M\" to place manually, or \"A\" to autoplace." << endl;
  char manualOrAuto;
  cin >> manualOrAuto;
  manualOrAuto = toupper(manualOrAuto);

  while (cin.fail() || (manualOrAuto != 'M' && manualOrAuto != 'A')) {
    cin.clear();
    cin.ignore(256, '\n');
    cout << BOLD(FRED("Error: please \"M\" for manual placement or \"A\" for auto placement:")) << endl;
    cin >> manualOrAuto;
    manualOrAuto = toupper(manualOrAuto);
  }

  cin.clear();
  cin.ignore(256, '\n');

  if (manualOrAuto == 'A') {
    playerGrid.generateGrid();
    cout << "\nOkay! Player grid has been auto-generated!" << "\n" << endl;
    playerGrid.displayGrid();
  } else {
    playerGrid.displayGrid();

    //Create and place player's destroyer
    playerDestroyer.inputAdaShip(3, "Destroyer");
    playerGrid.placeAdaShip(playerDestroyer);
    playerGrid.displayGrid();

    //Create player submarine, and determine if it conflicts with another AdaShip already present in the grid
    playerSub.inputAdaShip(3, "Submarine");
    overlap = playerGrid.detectCross(playerSub);
    while (overlap == true) //if it conflicts, prompt user and re-input AdaShip coordinates
    {
      cout << BOLD(FRED("Error: Your AdaShip overlaps a AdaShip already placed! Please re-enter different coordinates.")) << endl;
      playerGrid.displayGrid();
      playerSub.inputAdaShip(3, "Submarine");
      overlap = playerGrid.detectCross(playerSub);
    }
    playerGrid.placeAdaShip(playerSub); //After AdaShips has been validated, place in grid, then display the grid
    playerGrid.displayGrid();

    //Repeat the process above for all other AdaShips
    playerPatrolBoat.inputAdaShip(2, "Patrol Boat");
    overlap = playerGrid.detectCross(playerPatrolBoat);
    while (overlap == true) {
      cout << BOLD(FRED("Error: Your AdaShip overlaps a AdaShip already placed! Please re-enter different coordinates.")) << endl;
      playerGrid.displayGrid();
      playerPatrolBoat.inputAdaShip(2, "PatrolBoat");
      overlap = playerGrid.detectCross(playerPatrolBoat);
    }
    playerGrid.placeAdaShip(playerPatrolBoat);
    playerGrid.displayGrid();

    playerBattle.inputAdaShip(4, "Battleship");
    overlap = playerGrid.detectCross(playerBattle);
    while (overlap == true) {
      cout << BOLD(FRED("Error: Your AdaShip overlaps a ship already placed! Please re-enter different the coordinates.")) << endl;
      playerGrid.displayGrid();
      playerBattle.inputAdaShip(4, "Battleship");
      overlap = playerGrid.detectCross(playerBattle);
    }

    playerGrid.placeAdaShip(playerBattle);
    playerGrid.displayGrid();

    playerCarrier.inputAdaShip(5, "Carrier");
    overlap = playerGrid.detectCross(playerCarrier);
    while (overlap == true) {
      cout << BOLD(FRED("Error: Your AdaShip overlaps a ship already placed! Please re-enter coordinates.")) << endl;
      playerGrid.displayGrid();
      playerCarrier.inputAdaShip(5, "Carrier");
      overlap = playerGrid.detectCross(playerCarrier);
    }
    playerGrid.placeAdaShip(playerCarrier);
    playerGrid.displayGrid();
  }

  cout << endl << "Generating a Computer grid...\n" << endl;

  aiGrid.generateGrid();
  cout << "Computer Grid has been created! Let's start AdaShip!" << endl;

  //Display this message only if one party has won at least once
  if (playerWins != 0 || aiWins != 0) {
    cout << "Player wins: " << playerWins << endl << "Computer Wins: " << aiWins << endl;
  }

  char playAgain; //Holds players input when asking to play again
  //When either of these are true, terminate current game
  bool playerWin = false;
  bool aiWin = false;
  int turns = 1; //Holds turn number
  int firstTurn = true;
  string gameFlowUserDecision;
  string happyOrQuit;

  cout << "\nPress \"H\" if you are you happy with all of your AdaShip Positions or press \"Q\" to quit the program";
  cin >> happyOrQuit;
  if (happyOrQuit == "H" || happyOrQuit == "h") {
    playerGrid.displayKey();
    firstTurn = false;
  } else if (happyOrQuit == "q" || happyOrQuit == "Q") {
    return 1;
  }

  while (!playerWin && !aiWin) {
    //Improves game flow
    if (firstTurn) {
      cout << "\nPress \"E\" to end the computer's turn to continue or press \"Q\" to quit the program or press \"C\" to reset your grid" << endl;
      cin >> gameFlowUserDecision;
      if (gameFlowUserDecision == "e" || gameFlowUserDecision == "E") {
        playerGrid.displayKey();
      } else if (gameFlowUserDecision == "c" || gameFlowUserDecision == "C") {
        onePlayerVComputer();
        return 0;
      } else if (gameFlowUserDecision == "q" || gameFlowUserDecision == "Q") {
        return 1;
      }
    }

    firstTurn = true;

    //Displays a map of your shots every turn before you shoot
    cout << BOLD(FRED("\n           Player Target Board\n")) << endl;
    blankGrid.displayGrid();
    cout << "\nTurn " << turns << endl;

    cout << "***YOUR TURN***" << endl;
    blankGrid = aiGrid.playerShot(blankGrid); //Let the player shoot
    playerWin = aiGrid.detectWin(); //Check to see if they won

    if (!playerWin) //if the player didn't just win..
    {
      cout << endl << "***Computer's TURN***" << endl;
      playerGrid.aiShot(); //Have the AI shoot
      aiWin = playerGrid.detectWin(); //Check if they won
      //Display the computer's shots (with your AdaShips) after the computer's turn
      cout << BOLD(FGRN("\n              Your Board\n")) << endl;
      playerGrid.displayGrid();
      turns++;
    }
  }

  if (playerWin) {
    cout << "Player Wins! Congratulations!" << endl;
    playerWins++;
  } else {
    cout << "Computer Wins! Better luck next time!!" << endl;
    aiWins++;
  }

  //Program asks user to play again, validates input and reacts accordingly
  cout << "Would you like to play again? Y/N:" << endl;
  cin >> playAgain;
  playAgain = toupper(playAgain);

  while (cin.fail() || (playAgain != 'Y' && playAgain != 'N')) {
    cin.clear();
    cin.ignore(256, '\n');
    cout << BOLD(FRED("Error: please type \"Y\" for Yes or \"N\" for No:")) << endl;
    cin >> playAgain;
    playAgain = toupper(playAgain);
  }

  if (playAgain == 'N') {
    endGame = true;
  }
  cout << "Thank you for playing!" << endl;
  return 0;
}