//=========================================================================
// Name	 	: main.cpp
// Author	: Saumya Bhatnagar
// Description	: This header fill will explain the classes and functions
//=========================================================================


#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class func{
public:
   void display(int, int, vector<vector<int> >);//to display the board. //has to be accessed by board in play(in Game class)
   int equals(int, int, int, int);//returns the value, if all four input integers are same
};

class board : public func {//struct class board
friend class Game;
private:
   int level;//rows, the lowest and initiating row being 5
   int move;//columns
   vector<vector<int> > place;//player's place in board
public:
   board(int, int);//initiate board with zero
   board& operator=(board& b);//for copying board
   void setVal(int,int, board& b, int);//set the value in board to given value 
   int getPlace(int, board& b);//returns the value at a place
   int colFilled(int);//return the filledup status of the column
   int redMove();//plays red move
   int boardFilled();//returns, the status of the board
   int checkWinner();//returns the winner
   void randMove(int);//random move generator for mcmc
   int winner(int, board& b);//generates the winner for mcmc
   int chanceWin(int,int,board& b);//get the chances of winning for each move, when played
   int mcmcMove(int, board& b);//suggests the move to be played based on chanceWin
};

class Game {
public:
   void play(); //playes the game
   void printWinner(int, int, int);//prints the winner
};

