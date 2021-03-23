#ifndef ADASHIP_H
#define ADASHIP_H

#include <string>

using namespace std;

class AdaShip //The ship class is not used extensively in actual gameplay - when the grid object is passed a ship, it places the ships coordinates into the grid
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
    void inputAdaShip(int s, string n); //Allows the player to input their coordinates for the ship
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

#endif