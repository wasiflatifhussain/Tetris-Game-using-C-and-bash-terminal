#include "io.h"
mutex mut; //used to make sure the two thread will not read/write at the same time
using namespace std;

//Function: grows the list when the size exceeds maximum size of current list
void GrowthList(Shape * &ls,int &size,int n){
    Shape * new_ls = new Shape[size+n]; //create a new list with added length
    if(ls != nullptr){
        for(int i=0;i<size;i++){
            new_ls[i] = ls[i]; //copy data from the old list to new list
        }
        delete [] ls; //delete the old list
    }
    ls = new_ls; //set the pointer point to the new list
    size += n; // give the new size
}

//Function: gets the shape from the shapels.txt using ifstream and ofstream
//Input: a shape class object to store the shape
int GetShape(Shape * &ls){
    int size(0),pos(0);//init. size and pos
    char temp; //create a temp char. for indicating begin of a shape
    ifstream fin;
    fin.open("./dependence/shapels.txt");
    if (fin.fail()){
        return -1; //if no unable to open file return -1 for error control
    }
    while (fin >> temp){//in this loop get data from the txt to a char array then append the shape ls
        char **temp_ls = new char* [shapesize];
        for(int i=0;i<shapesize;i++){
            temp_ls[i] = new char [shapesize];
            for(int j=0;j<shapesize;j++){
                fin >> temp_ls[i][j];
            }
        }
        if (pos>=size){
            GrowthList(ls,size,increasesize);
        }
        ls[pos++] = Shape(temp_ls);
    }
    return pos;
}

//Function: when the player wants to load an older game status, this function runs
//Input: name of the file to be accessed and used as current game
//Output: initiate game with this board with the score stored in this .txt file also
int ReadGameFromFile(Games &game, std::string fname){
    ifstream fin;
    fname = "./saves/" + fname;
    fin.open(fname.c_str());
    if (fin.fail()){
        cout<<"Error in file opening" << endl;
        return 1; //return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<MaxHeight;i++){
        for(int j=0;j<MaxWidth;j++){
            char temp;
            fin >> temp;
            game.board[i][j] = temp;
        }
    }
    fin >> game.score;
    fin.close();
    return 0;
}

//Function: used to store the data of the game when the player decides to save the game status
//Input: name of the file which will be used to store the game status
//Output: game data stored into the desired .txt file
//        .txt file for saving game status saved in the ./saves directory
int WriteGameToFile(Games &game, string fname){
    ofstream fout;
    fname = "./saves/" + fname;
    fout.open(fname.c_str());
    if (fout.fail()){
        cout << "Error in file opening" << endl;
        return 1;//return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<MaxHeight;i++){
        for(int j=0;j<MaxWidth;j++){
            fout << game.board[i][j];
        }
        fout << endl;
    }
    fout << game.score << endl;
    fout.close();
    return 0;
}

//Function: takes in moves from the active keyboard defined in the game and use the moves to
//          move the shape inside the board.
//Output: sends the shape movement data to BoardPrinter function to print the move
void MoveInTake(Shape &shape,Games & game, int &userend){
    char c;
    while (userend){ //for ever loop
        //input
        cin >> c;
        c = tolower(c); //to make it work for both upper and lower cases
        while(!mut.try_lock()); //try to lock the mut lock so that this thread is safe to operate on the variables
        if(userend){
            if ('d'==c && shape.x != 15){  //if player presses 'd' key, this loop runs
                if(shape.x<15){
                    int temp=1;
                    for(int i=0;i<3;i++){
                        if(shape.y+i<MaxHeight && shape.y+i>=0){
                            if(game.board[shape.y+i][shape.x+1] != '0')
                                temp = 0;
                        }
                    }
                    if (temp)
                        shape.x+=1;
                }
            }else if ('a'== c && shape.x != 0){   //if player presses 'a' key, this loop runs
                if(shape.x>0){
                    int temp=1;
                    for(int i=0;i<shapesize;i++){
                        if(shape.y+i<MaxHeight && shape.y+i>=0){
                            if(game.board[shape.y+i][shape.x-1] != '0')
                                temp = 0;
                        }
                    }
                    if (temp)
                        shape.x-=1;
                }
                
            }else if ('w' == c) {  //if player presses 'w' key, this rotation function is called
                shape.SetRotation(shape.i+1);
            }
            else if ('s' == c) {
                shape.SetRotation(shape.i-1);
            }else if ('e' == c){   //if player presses 'e', game has to end so flag made to 0
                userend = 0;
            }
        }
        mut.unlock(); //unlock the mut lock
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
    }
}

//Function: prints both the board and the shape at the same time on the terminal using looping.
//          this also checks for shape collisions and when to remove matches from the board and saves shapes into board
void BoardPrinter(Shape & shape,Games &game,int &userend,int &contin, Shape * &ls, int &len){
    while (userend){ //for ever loop
        while(!mut.try_lock()); //try to lock the mut lock so that this thread is safe to operate on the variables
        for (int i=0;i<MaxWidth+2;i++){  //to print the board outline
            cout << "-";
        }
        cout << endl;
        for (int s1 = 0; s1 < MaxHeight;++s1) {
            cout << "|";  //printing board outline
            for (int s2 = 0; s2 < MaxWidth; ++s2) {  //check if the shape coordinates exist in this iteration of the loop
                if ((s1 == shape.y && s2 == shape.x) || (s1 == shape.y && s2 == shape.x+1) || (s1 == shape.y && s2 == shape.x+2) || (s1 == shape.y+1 && s2 == shape.x) || (s1 == shape.y+1 && s2 == shape.x+1) || (s1 == shape.y+1 && s2 == shape.x+2) || (s1 == shape.y+2 && s2 == shape.x) || (s1 == shape.y+2 && s2 == shape.x+1) || (s1 == shape.y+2 && s2 == shape.x+2)) {
                    if(shape.board[s1-shape.y][s2-shape.x] != '0'){  //ignores all the 0s in the shape
                        cout<<shape.board[s1-shape.y][s2-shape.x];   //prints only x's in the shape
                    }
                    else {
                        if(game.board[s1][s2] != '0')
                            cout << game.board[s1][s2];
                        else
                            cout << " ";
                    }
                    }
                    else {
                        if(game.board[s1][s2] != '0')
                            cout << game.board[s1][s2];
                        else
                            cout << " ";
                    }
            }
            cout << "|" <<endl;
        }
        for (int i=0;i<MaxWidth+2;i++){
            cout << "-";
        }
        cout << endl;
        cout<<"score: " << game.score <<endl;
        //checks if the shape has contacted with any of the other shapes or edges of the board and then adds shape to board
        //also calls RemoveMatches function to remove matched line when found
        if(Contact(game,shape)){
            ShapeToBoard(game,shape);   //adds shape into the board
            RemoveMatches(game);  //removes matches from the board
            contin = !(shape.y<0);
            if(contin){
                shape = ls[rand()%len];
                shape.x = rand()%(MaxWidth-shapesize+1); //prevent the block born at the edge
            }else{
                cout << "game over press e to exit!" << endl;
                mut.unlock();
                return;
            }
        }else
            shape.y += 1;
        mut.unlock();//unlock the mut lock
        this_thread::sleep_for(chrono::duration<int, std::milli>( 400 ) );    //controlling the droppping speed of the shapes into the board
        for(int i=0;i<MaxHeight+3;i++){ //2 for the board wall 1 for the score line
            cout <<  "\033[1A";
            cout << "\033[K";
        }
    }
}
