# AdaShip
by Sukh Virdi
 
Locate to my AdaShip src code on the Repl.it compiler using this [link](https://repl.it/@SukhVirdi7/AdaShip) 

## Table of Contents
- [Challenge Outline](#1-challenge-outline)
  - [1a. Summary and review of the problem, overall proposed solution.](#-11-summary)
  - [1b. UML style diagram illustrating initial overall solution (linked to 1a)](#-12-uml-style-diagram)
  - [1c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a, 1b).](#-13-initial-working-plan)
  - [1d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c).](#-14-analysis-decomposition)
  - [1e. Initial object-oriented design ideas and plan of phased breakdown into smaller tasks (linked to 1d).](#-14-design-ideas)

 
## 1. Challenge Outline
 
### 1a. Summary and review of the problem, overall proposed solution.

Summary and review of the problem:
 
AdaShip is a command-line game, which is essentially a clone of the traditional board game "battleship". Players take turns trying to destroy each other's battleships placed along a grid. This means that the boards created will have to hold data relating to placed boats, fired shots and missed shots. The player (you) also needs to be able to fire torpedo shots, and receive information on the result of the shot (hit/miss). Once all of the AI/Computer ships are destroyed then the player wins the game or if the Computer destroys all of your ships they would win. The AI/Computer board is autocreated and their torpedo shots are fired at a random location on your playerboard. Hits/Misses for both your targetboard and the playerboard is displayed to the end-user to keep a log of the game progress. The game needs to prevent invalid input but also permit auto placing & manual placements when setting up the game.

---

My Overall Proposed Solution:

My solution implements all of the following requirements and represents a fully functional AdaShip Game, the screenshots provides evidence corresponding to the requirement it matches in that sub-section:

---

A usable, intuitive and highly efficient Set-Up interface in which a player can with minimal effort:
Select from a game menu to a start a:
One player v computer game
Quit

![menu](https://user-images.githubusercontent.com/56550489/112157955-9e9d2a00-8bdf-11eb-9aa3-0cba1414a50f.png)

----------------
Select and place any of their non-placed or placed ships at any valid position on their shipboard.
Clearly indicate the current non-placed and placed ships.
See their current shipboard.

![second](https://user-images.githubusercontent.com/56550489/112158512-2420da00-8be0-11eb-89af-caee6a5d0cf7.png)

-----------------
Be robust enough to prevent any invalid behaviours, prevent or correct any illegal placements and avoid system issues or errors related to user input.

![3](https://user-images.githubusercontent.com/56550489/112158825-73ffa100-8be0-11eb-960e-29450f5669bd.png)

-----------------

Auto-place all ships.

![4](https://user-images.githubusercontent.com/56550489/112161359-fbe6aa80-8be2-11eb-8af1-f76f60c9b45a.png)

--------
Support a ‘quit’ game and ‘reset’ shipboard option.
![5](https://user-images.githubusercontent.com/56550489/112161427-0bfe8a00-8be3-11eb-88e9-e38f47babd09.png)
-------

Support a ‘continue’ option if all ships have been placed and the user has confirmed they are happy with the current placements.

A computer-based opponent than can automatically complete a valid setup process using a random strategy (i.e., place all their ships at valid but constantly differing positions on their own shipboard); essentially this should utilise the auto-place feature outlined above.

![6](https://user-images.githubusercontent.com/56550489/112161672-45cf9080-8be3-11eb-94c2-cffc9877e0d5.png)
----------

A usable, intuitive and highly efficient Turn based process supported with a minimal user effort interface
in which game turns are played:

Player’s turn:
Their own, current and up to date ship and targetboards are displayed as well aligned tables
(rows and columns).
![13](https://user-images.githubusercontent.com/56550489/112164762-10787200-8be6-11eb-8fed-a43f0c556e22.png)
-

Players are able to ‘fire’ a single torpedo at a valid location (i.e., not previously targeted and within the board boundary) using the single notation coordinate (e.g., F2, etc.); if the location is invalid the player is asked to re-try.

![11](https://user-images.githubusercontent.com/56550489/112163756-3a7d6480-8be5-11eb-8219-dcbf2aafa8c9.png)
-
Players are clearly notified of a ‘hit’ or ‘miss’ (or win) based on the outcome of their turn.

![8](https://user-images.githubusercontent.com/56550489/112163226-baef9580-8be4-11eb-9cd2-d83986162fa0.png)
![9](https://user-images.githubusercontent.com/56550489/112163337-d8246400-8be4-11eb-8223-5f0abdeffbde.png)
-
Players are able to quit the game (if not already won).

![12](https://user-images.githubusercontent.com/56550489/112164238-a069ec00-8be5-11eb-939e-5f2585b62dbc.png)
-
Computer’s turn:
Its own, current and up to date ship and target boards are displayed as well aligned tables (rows and columns).
![10](https://user-images.githubusercontent.com/56550489/112163597-1883e200-8be5-11eb-8945-7bbf8425720c.png)
-
It uses its own up to date ‘targetboard’ to randomly ‘fire’ a torpedo at a valid location (i.e., not previously targeted and within the board boundary). A clear notification of a ‘hit’ or ‘miss’ (or win) based on the outcome is shown.
A user based ‘press a key’ interaction is required to end the computer’s turn.

![7](https://user-images.githubusercontent.com/56550489/112162885-62b89380-8be4-11eb-977b-767cfb956f70.png)

---

### 1b. UML style diagram illustrating initial overall solution (linked to 1a)

This is the Class Diagram for my AdaShip program illustrating all of the different classes present within the header files and my main.cpp file which acts as a controller retrieving the relevant attributes and methods from the game files. 

In theory, I designed the program to start with the INIReader file to retrieve the boat data from the INI config file. There is a one-to-one relationship between AdaShipGrid and INIReader, followed by another one-to-one relationship between AdaShip and AdaShipGrid.

The boat data is then meant to be parsed into the AdaShip file to hold within its class to then place the instructed ship coordinates into the grid, however it is not extensively used as most of the work is processed within the controller. 

AdaShipGrid attributes and methods are frequently used within the main file in order to make changes to the grid and continue with the game progress. 

The Colours header file is absent from the diagram as it does not contain a class however it is imported and used within some of the cpp files to improve the user interface.


![Untitled Diagram-Page-1]
(https://user-images.githubusercontent.com/56550489/112168012-d9579000-8be8-11eb-87cf-544b72c54dda.png)

---

### 1c. Initial working plan, overall approach, development strategy and approach to quality (linked to 1a, 1b).

![Untitled Diagram-Page-2](https://user-images.githubusercontent.com/56550489/112168095-ea080600-8be8-11eb-9347-7f23f635a60a.png)
-
### 1d. Analysis and decomposition of the overall problem into key ‘epic’ style tasks (linked to 1b, 1c).
---
### 1e. Initial object-oriented design ideas and plan of phased breakdown into smaller tasks (linked to 1d).


