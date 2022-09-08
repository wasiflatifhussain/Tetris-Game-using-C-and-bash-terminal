#ifndef __Game__
#define __Game__
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>
const int MaxHeight = 17;  //stores height of game board
const int MaxWidth = 18;  //stores width of game board
const int shapesize = 3;  //stores size of shapes in game board

//class ti store the game board and score for each game played by the player
class Games{
    public:
        char **board;
        int score;
        Games();
        ~Games();
};

//class used to control the keyboard function to allow user to control movement of shapes in the game
class Keyboard{//a class for easy management of input method
    private:
        struct termios setting;// a variable storing the orginal setting
    public:
        void off();//turn off echo for input and cancell the need of enter for input
        void on();//turn the setting back to the orginal
        Keyboard();// a constructor to init. the setting variable
};

//used to extract each shape for dropping during playing the game
class Shape{
    public:
        char **board; // a pointer to a 2D array that represent the board
        int x,y; //location ref to the larger game board
        void SetRotation(int number); //rotation function of the board
        void PrintBoard();//print the board
        void operator=(Shape const &a); //operator = when dealing with shape
        Shape(char **p); //a constructor for the shape when provided a char array
        Shape(); //empty constructor
        ~Shape();//deconstructor for the shape
        int i;
};

void RemoveMatches (Games &game);
bool Contact(Games &game, Shape &shape);
void ShapeToBoard(Games &game, Shape &shape);
int GameMain(Games &game);
#endif
