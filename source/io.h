#ifndef __io__
#define __io__
#include <fstream>
#include "game_type.h"
using namespace std;
const int increasesize = 3;
void GrowthList(Shape * &ls,int &size,int n);
int GetShape(Shape *&ls);
int ReadGameFromFile(Games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(Games &game, std::string fname); //return 1 if error occurs else 0
void MoveInTake(Shape &shape, Games &game, int &userend);
void BoardPrinter(Shape & shape,Games &game, int &userend,int &contin,Shape * &ls, int & len);
#endif 