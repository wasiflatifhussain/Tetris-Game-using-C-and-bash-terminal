# ENGG1340
## Group information
- Group number: 74
- Member 1.
  * Wong Tsz Hin
  * UID- 3035927489
  * Github account: Hugo1205
- Member 2.
  * HUSSAIN Wasif Latif 
  * UID- 3035834577
  * Github account: wasiflatifhussain
            

## Description and Game Information:
### Game Name
# Tetris
           
* We will have a menu which will act as a loading screen, allowing the player to start new game, load pre-saved game, end a game, and display rules for the game.
* The game will have a rectangular 17 x 18 dimensional board, where, the player will have to fit randomly generated shapes, generated using rand() and srand() functions.
The rand() and srand() functions are used to pick up the shape and orientation from a set of pre-stored shapes.
<ins> **Note that, the board is represented by borders made using '|' and '-' and any shape in the board is represented by x's** </ins>
* The target of the player is to prevent a single column of tetris blocks from reaching the top edge of the rectangular border board.
* When the player successfully fits the tetris blocks in such a way that a horizontal row x's are formed at any row of the board, that row of x's are removed and replaced by an empty row.
* The player can use the 'w/W' or 's/S' keys to change the rotation/orientation of the shape, while the 'a/A' or 'd/D' keys can be used to move the shape left or right along the board.
And the game continues on. The speed for drop of tetris blocks is kept constant for ease of player.

## Key Features and Options:

* Game Menu as an interface to lead to game options
* Option 1: Start New Game: Allows user to start new game with a fresh board.
* Option 2: Load Exisitng Game. Allows user to enter name of a saved game file, and continue left-off game.
* Option 3: Read Game Rules. Displays Rules to allow user to read game rules.
* Option 4: Exit Game and end program.

* The Game allows user to save the game data at any point in time, simply by clicking the 'e/E' key on their keyboard. They are then prompted to save the game using any file name they want and can load this game by entering this file name in Load Exisitng Game option later.

### Sample Input/Output:
* The input for the game is the shapels.txt and gameRules.txt files stored in the directory named 'dependence'.
* Whenever the user saves a game file, the game file gets stored in a separate directory named 'saves'. We have attached a sample save file that would have been saved if the user played a game, and saved the gamefile with name 'temp'/'temp.txt'. Our program manually adds the .txt extension if it is not added by the user.
* Press 'e'/'E' to pause and save game at any point of playing the game.

## Compilation and execution instructions:
To compile the program and play the game, please launch the linux terminal, go to this game's directory and enter the following codes:
```
make game
./game
```

## Visual Representation of game in play: 
```
- - - - - - - - - - - - - -      
|  x                   x  | 
|  x                   x  |        
|                      x  |   
|  x                   x  |
|  x                   x  |
|      xxxx            x  |
|  x         xxxxxxxxxxx  |
|                         |
|  x            xxxxxxx   |
|  xxxxxxxxx    xxxxx     |
|xxxxxxxxxxxxxxxxxxxxxxxxx|
- - - - - - - - - - - - - -
```
This is a visual representation of the game during play.
Here, the 0s represent the board while the x's represent any of the shape blocks falling inside the board.
Notice that the last line at lower edge of the board has a line/row of x's, which will mean that this row will now get eliminated and all rows will now move one row down, and the game will continue.

#### Game Lose Condition:
```
- - - - - - - - - - - - - -      
|  x                   x  | 
|  x                   x  |        
|  x                   x  |   
|  x                   x  |
|  x                   x  |
|  x    xxxx           x  |
|  x         xxxxxxxxxxx  |
|  x                      |
|  x                      |
|  x     xxx    xxxxx     |
|  xxx   xxx   x  xxxx xxx|
- - - - - - - - - - - - - -
```
If the player ends up having a single column of x's(tetris blocks) spanning from the lower edge of the board to the upper edge of the board, this will cause the player to lose the game. 

## Features and implementation of the coding requirements:
### 1. Generation of random game sets or events: 
   * The tetris block is randomly generated from a pre-made set which will contain all the shapes which can be generated to be used by the player during
a single game of tetris. Each time, a shape will be picked out of the set randomly, along with a random orientation, and the player has to fit the 
block into the rectangular n x m board. srand and rand functions are used here to achieve random shapes.
   * rand and srand are also used to make sure that our shapes will be originated at different points along the top edge of board and start falling downwards from a random point of the top board edge. This will make the game more challenging for the players and more fun.

### 2. Data Structures and tehc:
   * The game uses structs, classes, simple arrays and dynamic arrays to store.
   * Separate classes are made for storing the shapes and to rotate them, to store the game board and a separate class called Keyboard is used to store the keyboard keys to be used during the program. It allows the keyboard to be turned on and off when needed.
   * Score, board,shapes are stored in data structures during game-time also.
   * The game uses multi-threading to take continuous key inputs and print the dropping of the shapes as well as the board simultaneously.
    
### 3. Dynamic Memory Management:
   * Memory is allocated to storing the game data and for storing the high score for the game. We will also be allocating memory to allow the player to save
load game and load it whenever they want to play the game. To save memory, we will overwrite existing memory to save new data. Furthermore, we will also only 
store a fixed number of shapes in a dynamic array so to fit all shape in the txt file and rotate them during the game, instead of generating and storing a new shape everytime. This is likely 
to help save memory and manage the data better.
   * We also use dynamic arrays to allocate memory for board and shapes and delete them when we need to generate new shapes.
   * Furthermore, the array is grown whenever needed using a GrowthList() function whenever needed.

### 4. File input/output (e.g. for loading/saving game status)

  * A .txt file is used to store all the shapes used by the program. The program reads shapes out of this file and places it in a dynamic array to be used by the game.
   * The data of a played game is stored in a .txt file when the player decided to save the game data. This file is saved in the "saves" directory and can be accessed by the user to load this game again and continue playing. This .txt file will store both the game board as well as the score of the user for that game.
   * At the beginning of the game, if the player decided to play a new game, then a new game begins and the shape storing file, shapels.txt is used to take in shapes. The board is generated in game, and a series of functions are used to make the moves and store the moves into the board. If the user decided to stop at any time, then the player gets to save this game with any name. Then the data is stored into a .txt file with that name and stored in the "saves" directory, available for the user to access later on.
   * If instead the player decided to start with a saved game, then they have to enter name of the gamefile they want to load. Then the text gamefile as well as the shapels.txt are used as input files using ifstream and the process of game saving, etc remain similar to that used for a new game.
   
### 5. Program codes in multiple files
   * Program is stored in three main code files named- main.cpp, gametype.cpp and io.cpp. io.h and gametype.h are header files for gametype.cpp and io.cpp.
      - main.cpp is the main file that displays the menu, and the options to choose from including new game, load game, game rules, and exit.
      - selecting any option in main.cpp will direct/connect to io.cpp which is mainly used to handle all inputs and outputs of the game.
      - io.cpp will call to gametype.cpp and its header files. gametype.cpp and its heeader mainly handles all the classes for storing gameboard, game shapes and keyboard function. The rotation of the shapes in the game, turning the special keyboard function on and off where necessary, printing the shape into the board after the shape has dropped into the board, removing a full horizontal line of tetris blocks is also handled by this file.
      - io.cpp simply acts as a pathway to take in input from the gametype.cpp and use it to print the materials on the terminal and handle all user moves and sends these back to the gametype.cpp to be saved into the board and to continue the game.

### Non-Standard C/C++ Libraries:
  * unistd.h and termios.h used to disable the echo of keyboard input and the end the press enter during input.
  * unistd.h is also used to access the rand() and srand() functions.

### Problem Statement and learning scope:
Tetris requires the program to be made such that, each of the user's input of the moving keys gives an immediate response without user having to constantly press Enter. Furthermore, it involves implementation of moving shapes and objects on the terminal. The main object of taking up this game idea was mainly for us to learn how to make shapes and objects fall or move on the terminal and control their movements elegantly. 
We learnt how to coordinate resources between the two threads. So that they will not read/write to the same variable and cause memory errors. And we learnt how to implement a good class, so that in further programming we no longer need to care what is inside the class. We can just call the functions.
We learnt about multi-threading and sleep functions and erasing information from terminal and immediately printing new information to view as if the shapes in the terminal are moving.

