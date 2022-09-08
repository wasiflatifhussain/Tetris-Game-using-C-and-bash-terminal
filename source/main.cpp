#include "io.h"
#include <stdlib.h> //for srand and rand
#include <time.h> //for time(NULL)
using namespace std;

int Menu ();
void CheckOption (string & option);
void readRules ();
void newGame ();
void loadGame ();
int main () {
  while(Menu());
  return 0;
}
void trim(string & s){
  while(isspace(s[0])){
      s = s.substr(1,s.size()-1);
  }
  while(isspace(s[s.size()-1])){
      s = s.substr(0,s.size()-1);
  }
}

//Function: prints main menu and all the functions.
//Input: Integer input determining the option the user chooses
//Output: calls the CheckOption function to check option user selected.
int Menu () {
  string option;
  cout<<"Welcome to Tetris!"<<endl;
  cout<<"Select Option: "<<endl;
  cout<<"1. Start New Game"<<endl;
  cout<<"2. Last Game Status"<<endl;
  cout<<"3. Game Rules"<<endl;
  cout<<"4. Exit"<<endl;
  cout<<"Enter Option Number: ";
  cin>>option;
  trim(option);
  while (option != "4") {
    if (option == "1" || option == "2" || option == "3"){
      cout<<endl;
      CheckOption (option);  //function to check option selected
      return 1;
    }
    cout<<"Invaild input! Try again: ";
    cin>>option;
    trim(option);
  }
  cout<<"Game Exited."<<endl;
  return 0;
}

//checks the option the user selected.
void CheckOption (string & option) {
  if (option == "1") {
    newGame ();
  }
  else if (option == "2") {
    loadGame ();
  }
  else if (option == "3") {
    readRules ();
  }
}

//Function: Reads the rules of the game from a file named gameRules.txt
//Inputs the name integer input from main and outputs contents of the gameRules.txt
//file
void readRules () {
  ifstream fin;
  fin.open("./dependence/gameRules.txt");
  if (fin.fail()) {
    cout<<"Error in file opening"<<endl;
    exit(1);   ///UNSURE IF TO PUT return 1 or exit(1) here!!
  }

  string line;
  while (getline(fin,line)) {
    cout<<line<<endl;
  }
  fin.close();
}


//Function: initiates a game class and calls main game to start the game
//          when game is over, it outputs out the game data allowed to be stored in
//          a .txt file to be stored in the ./saves/ directory.
void newGame () {
  Games game;//Since it is a new game we create a new game with type Games
  if(GameMain(game)){ //This will be the part where the game process take places.
    string fname; //after the game is done ask for the name of save file
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1) //if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}

//Function: Reads the board from the last game and outputs
//          the result.

void loadGame () {
  Games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  //cout<<"after close"<<fname<<endl;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  while (ReadGameFromFile(game,fname)){
    cout << "Error. Please Enter a valid file name:";
    cin >> fname;
    //cout<<"after close"<<fname<<endl;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
  }
  if(GameMain(game)){
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}

