#include "io.h"
Games::Games(){
    this->board = new char * [MaxHeight]; //create a array of pointer
    for(int i=0;i<MaxHeight;i++){
        this->board[i] = new char [MaxWidth]; //for each pointer create an array it points to
        for(int j=0;j<MaxWidth;j++){
            this->board[i][j] = '0';
        }
    }
    this->score = 0;
}
Games::~Games(){
    for(int i=0;i<MaxHeight;i++){
        delete [] this->board[i]; //delete the array the pointer pointing to
    }
    delete [] this->board; //delete the array of pointer
}
//Function: this is a special function that will temporarily take over the user's keyboard and change keyboard settings
//          so that settings are defined by this function. this function stops the keyboard is turned off and vicerversa.
void Keyboard::off(){ //turn off echo for input and cancell the need of enter for input
    struct termios t=setting;
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what we want it to do
    t.c_lflag &= ~ECHO;
    t.c_lflag |= ECHONL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}
void Keyboard::on(){//turn the setting back to the orginal
    tcsetattr(STDIN_FILENO, TCSANOW, &setting); //Apply the orginal settings
}
Keyboard::Keyboard(){// a constructor to init. the setting variable
    tcgetattr(STDIN_FILENO, &setting); //get the current terminal I/O structure
}

//Function: rotaes the board when the function is called; it uses pointers and
//          iterators to rotate the shapes
void Shape::SetRotation(int number){
    if(this->board == nullptr)
        return;
    int target = (number-this->i)%4; //calc. how many rotation needed and perform the according rotation
    this->i = number%4;
    if (target == 0)
        return;
    char **p = new char *[shapesize]; //create a array of pointer
    for(int i=0;i<shapesize;i++){
        p[i] = new char [shapesize]; //for each pointer create an array it points to
    }
    if (target == 1){
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[shapesize-j-1][k] = this->board[k][j];
            }
        }
    }else if (target == 2){
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[j][k] = this->board[shapesize-j-1][k];
            }
        }
    }else { //either -1 or 3
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[k][j] = this->board[shapesize-j-1][k];
            }
        }
    }
    for(int i=0;i<shapesize;i++){
        delete [] this->board[i]; //delete the array the pointer pointing to
    }
    delete [] this->board; //delete the array of pointer
    this->board = p; //set the pointer pointing to the new array.
}
void Shape::PrintBoard(){
    for(int i=0;i<shapesize;i++){ //print the board
        for(int j=0;j<shapesize;j++){
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Shape::operator=(Shape const &a){
    for(int i=0;i<shapesize;i++){
        memcpy(this->board[i],a.board[i],shapesize*sizeof(char)); //copy board for each pointer
    }
    this->i = a.i;//copy i
    this->x = a.x;
    this->y = a.y;
}

//used to allocate memory for board as well as declare x,and y coordinates for shape.
Shape::Shape(char **p){
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
    this->board = p; //give the value of the pointer p to board
}

//used to allocate memory for board as well as declare x,and y coordinates for shape.
Shape::Shape(){
    this->board = new char* [shapesize]; //create array of pointer
    for(int i=0;i<shapesize;i++){
        this->board[i] = new char [shapesize]; // for each pointer create a array it points to
    }
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
}

//destroys the board when releases memory
Shape::~Shape() {
    for(int i=0;i<shapesize;i++){ //deconstructor release the memory holding by the board when the class is destroyed
        delete [] this->board[i]; //delete all the array
    }
    delete [] this->board; //delete the pointer array
}

//Function: searches for matches inside the board. if a full horizontal line of x's form on the screen,
//          this function looks for that line and removes that line from main board and prints remaining lines
//          by shifting lines one line down.
void RemoveMatches (Games &game) {
    char tempo[MaxHeight][MaxWidth];
    int xIdx = MaxHeight-1;
    for (int i = MaxHeight - 1; i >= 0; --i) {
        int counter = 0;
        for (int j = 0; j < MaxWidth; ++j) {
            if (game.board[i][j] == 'x') {
                counter += 1;
            }
        }
        if (counter < MaxWidth) {
            for (int m = 0; m < MaxWidth; ++m) {
                tempo[xIdx][m] = game.board[i][m];
            }
            xIdx -= 1;
        }
    }
    while(xIdx >= 0) {
        for (int m = 0; m < MaxWidth; ++m) {
            tempo[xIdx][m] = '0';
        }
        xIdx -=1;
    }
    for (int i = 0; i < MaxHeight; ++i) {
        for (int j = 0; j < MaxWidth; ++j) {
            game.board[i][j] = tempo[i][j];
        }
    }
    game.score += 1;
}

//Function: checks to see if the shape hits another shape or if shape reaches end-line of the board
//Input: game and shape arrays
//Output: finds where the shape collides/contacts
bool Contact(Games &game, Shape &shape){
    if(shape.y+2 == MaxHeight-1)
        return true;
    for(int i=0;i<3;i++){
        if(shape.y+i+1>=0 && shape.y+i+1<MaxHeight){
            for(int j=0;j<3;j++){
                if (shape.board[i][j] !='0' && game.board[shape.y+i+1][shape.x+j]!= '0')
                    return true;
            }
        }
    }
    return false;
}

//Function: function used to save each shape into the board after the shape settles into the board
//Input: takes in the shape and game board
//Output: stores the shape in exact coordinates of the game board as shown to user on screen
void ShapeToBoard(Games &game, Shape &shape) {   //to be used to add the shape into the main board
  int xIdx = 0, yIdx = 0;
  for (int s1 = 0; s1 < MaxHeight;++s1) {
    for (int s2 = 0; s2 < MaxWidth; ++s2) {
      if ((s1 == shape.y && s2 == shape.x) || (s1 == shape.y && s2 == shape.x+1) || (s1 == shape.y && s2 == shape.x+2) || (s1 == shape.y+1 && s2 == shape.x) || (s1 == shape.y+1 && s2 == shape.x+1) || (s1 == shape.y+1 && s2 == shape.x+2) || (s1 == shape.y+2 && s2 == shape.x) || (s1 == shape.y+2 && s2 == shape.x+1) || (s1 == shape.y+2 && s2 == shape.x+2)) {
        if(shape.board[yIdx][xIdx] != '0' && game.board[s1][s2]=='0'){
          game.board[s1][s2] = shape.board[yIdx][xIdx];    //FIX IN MAIN
        }
        xIdx+=1;
        if (xIdx>2) {
          yIdx+=1;
          xIdx=0;
        }
      }
    }
  }
}

//Function: main function that loads the keyboard function as well as initiates
//          the functions to move shapes and print board and shape
//Input: it takes in input of game class by reference
//Output: it modifies the board by saving shapes to board as well as removing matches lines
//        in the board.
//Special: uses multi-threading to print the board and shape into board and move the shape around in
//         the board
int GameMain(Games &game){
    int len;
    Keyboard kb;
    Shape * ls = nullptr;  //dynamic array declared here
    srand(time(NULL));   //use of random function using time parameter
    kb.off();
    len = GetShape(ls);
    int userend(1),contin(1);
    Shape temp;
    temp = ls[rand()%len];
    temp.x = rand() % (MaxWidth-2);
    thread th1(MoveInTake,ref(temp),ref(game),ref(userend));  //thread to handle the moves given by key movements of a,s,d,w,e
    thread th2(BoardPrinter,ref(temp),ref(game),ref(userend),ref(contin),ref(ls),ref(len)); //thread to print the board and erase previous boards continuously
    th1.join();
    th2.join();
    delete [] ls;
    kb.on();
    if (contin) //if it is stop by the user
        return 1;
    return 0;
}
