#include <cassert>
#include <iostream>
#include <cstdlib>
#include "functions.h"

using namespace std;

board::board(int level, int move){//initiate board with no place
  this->level = level;
  this->move = move;
  this->place.assign(level, vector<int>(move, 0));
}

board& board::operator=(board& c){//copy board
  this->level = c.level;
  this->move = c.move;
  this->place = c.place;
  return *this;
}

void func::display(int level, int move, vector<vector<int> >place) {//to display the board
  cout << "~~~~~~~~~~~~" << endl;
  for(int i = 0; i < level; i++){
    for(int j = 0; j < move; j++){
	cout << place[i][j] << " ";
    }
    cout << endl;
  }
}

void board::setVal(int level, int move, board& b, int val){//set the place in board to the given value
  place[level][move] = val;
}

int board::getPlace(int move, board& b){//returns the value at a place in board
  int p = 5;
  while(((place[p][move])!=0)){  
    p--;  
    if(p < 1) { return 0; }  //Declare 10 for full column
  }
return p; //return 10 in case of filled column
}

int board::colFilled(int j){//returns 10 if the columns is filled
   int i=5;
   while((i>=0)&&(place[i][j]!=0)){ i--; }
   i = (i < 0) ? 10 : 0; //Declare 10 for column filled
return i; //if return 10 then column is filled and zero if not
}

int board::redMove(){//user input of the red move
  int move;
  cout << "Player One's turn:";//get move
  cin >> move ;
  while(colFilled(move)==10){  return redMove();  }
return move; 
}

int board::boardFilled(){//returns 70 if the column is filled, 10 for each column
  int i=0;
  for(int j = 0; j < move; j++){  i+=colFilled(j);    }
return i; //sum of all col filled = 70
}

int func::equals(int a, int b, int c, int d){//returns the value if all four input values are same
  int ret;
  if(a==b && a==d && a==c){//comparison
    ret= a;
  }else{
    ret = 0;
  }
return ret;
}

int board::checkWinner(){//checks if there is any winner on the board or returns 0, meaning either draw of game is still on
  int i, j, res = 0;//, id, jd, dir;
  //Set directions
//  board d(4,2); //four rows for four directions d.setDirexn(d.place); 
/*    | 1  0|
      | 0  1|
      | 1  1|
      |-1 -1|    */
/*  d.setVal(0,0,d,1);  //Horizontal
  d.setVal(1,1,d,1);  //Vertical
  d.setVal(2,0,d,1);  d.setVal(2,1,d, 1); //Positive slope
  d.setVal(3,0,d,-1); d.setVal(3,1,d, -1); //Negative slope
  for(dir=0; dir<4;dir++){//for each direction
     id = d.place[dir][0]; jd = d.place[dir][1]; 
*/
       	for(i=0; i<level;i++){//Horizonatal
         for(j=0; j<4;j++){
            int a=place[i][j];
	    int b=place[i][j+1];
	    int c=place[i][j+2];
	    int d=place[i][j+3];
            res = equals(a,b,c,d); //returns the value, if at four consequtive place, values are same 
	    if((res==1)||(res==2)){return res;}
	  }
	    if((res==1)||(res==2)){return res;}
	}
	    if((res==1)||(res==2)){return res;}
       for(j=0; j<move;j++){
         for(i=0; i<3;i++){//Vertical
            int a=place[i][j];
	    int b=place[i+1][j];
	    int c=place[i+2][j];
	    int d=place[i+3][j];
            res = equals(a,b,c,d); //returns the value, if at four consequtive place, values are same 
	    if((res==1)||(res==2)){return res;}
	  }
	    if((res==1)||(res==2)){return res;}
	}
	    if((res==1)||(res==2)){return res;}
       for(i=0; i<3;i++){//Negative Slant
         for(j=0; j<4;j++){
            int a=place[i][j];
	    int b=place[i+1][j+1];
	    int c=place[i+2][j+2];
	    int d=place[i+3][j+3];
            res = equals(a,b,c,d); //returns the value, if at four consequtive place, values are same 
	    if((res==1)||(res==2)){return res;}
	  }
	    if((res==1)||(res==2)){return res;}
	}
	    if((res==1)||(res==2)){return res;}
       for(i=3; i<level;i++){//Positive Slant
         for(j=3; j<move;j++){
            int a=place[i][j];
	    int b=place[i-1][j-1];
	    int c=place[i-2][j-2];
	    int d=place[i-3][j-3];
            res = equals(a,b,c,d); //returns the value, if at four consequtive place, values are same 
	    if((res==1)||(res==2)){return res;}
	  }
	    if((res==1)||(res==2)){return res;}
	}
	    if((res==1)||(res==2)){return res;}
return res; //will return 0 or 1 or 2
}

void board::randMove(int played){//random move generator
    int move = rand()%7;
    int p = getPlace(move, *this);
    while((p >6)||(p<0)){ return randMove(played);}
    setVal(p, move, *this, played);
}

int board::winner(int move, board& c){
  int w = 0;
  int p = 1;
  int min = 71;
  int played;
  while((w==0)&&(c.boardFilled() < min)){//no winner OR //all columns are not filled=> draw : not yet
    played=p;//Switch to current place
    c.randMove(played);
    p=(played==1) ? 2 : 1;
    w =c.checkWinner(); //0 has two meanings :game is still on, OR : draw
    if(c.boardFilled() == 70) { return w;  }
  }
return w;
}

int board::chanceWin(int limit, int move, board& b){//returns the chances to win for each move
  int w, diff; 
  int winR = 0;  int winB = 0; int draw = 0;
  
  for(int l=0; l<limit; l++){// run simulation
    board c=b; //copy board
    w = c.winner(move, c);
    //cout << "game status:" << w << endl;
    ((w==0) ? draw++ : ( (w==1) ? winR++ : winB++ ) );
  }
  
  //cout << "winB:" << winB << endl;
  //ratio = (winB-winR)/limit; return ratio;
  
  diff = winB-winR-draw;

return diff;
}

int board::mcmcMove(int limit, board& b){//suggests the move //should be in board or func

  int win=0, winPrev=-limit;
  int winningMove=3;//being center position, increases chances of winning

  for(int j=0; j<move; j++){ //for every move
      win = chanceWin(limit, j, b) ;
      //cout << "Winning chance of playing " << j << " are:" << win << endl;

      if(win > winPrev ) { 
          winPrev = win;
          winningMove = j;
      } 

  }

return winningMove;
}//shouldnt suggest the move if the column if is full

void Game::play(){//playes the game //Game can access private and public of class board

  int R = 6; int C = 7; 
  board b(R,C);  
  b.display(R, C, b.place);//display the game

  int first; //initiate the first player
  int limit ; //initiate the MCMC simulation limit
  int moveRed, levelRed, moveBlu, levelBlu; //initiate moves 
  int Red = 1, Blu = 2; //give values to the moves
  int noWinner = 0; //state winner status

  cout << "Who goes first, computer(press 2 for that) or you(press 1 for that)" << endl;
  cin >> first;

  cout << "State MCMC Simulation limit" << endl;
  cin >> limit;

  if(first == 1){
    while((noWinner==0)&&(b.boardFilled()<71)){
      //Red play
       moveRed = b.redMove();
       levelRed =b.getPlace(moveRed, b);
       levelRed = (levelRed < 10) ? levelRed : 0;
       b.setVal(levelRed, moveRed, b, Red);
       b.display(R, C, b.place);//display the game
       noWinner = b.checkWinner(); ///board filled...is there a draw
  
      //Computer play
      cout << "Player Two's Turn: wait it takes time!" << endl;
      moveBlu = b.mcmcMove(10000, b);
      levelBlu =b.getPlace(moveBlu, b);
      levelBlu = (levelBlu < 10) ? levelBlu : 0;
      b.setVal(levelBlu, moveBlu, b, Blu);
      b.display(R, C, b.place);//display the game
      noWinner = b.checkWinner(); ///board filled or not...is there a draw
    }

  }else{
    while((noWinner==0)&&(b.boardFilled()<71)){
  
      //Computer play
      cout << "Player Two's Turn: wait it takes time!" << endl;
      moveBlu = b.mcmcMove(limit, b);
      levelBlu =b.getPlace(moveBlu, b);
      levelBlu = (levelBlu < 10) ? levelBlu : 0;
      b.setVal(levelBlu, moveBlu, b, Blu);
      b.display(R, C, b.place);//display the game
      noWinner = b.checkWinner(); ///board filled or not...is there a draw

      //Red play
      moveRed = b.redMove();
      levelRed =b.getPlace(moveRed, b);
      levelRed = (levelRed < 10) ? levelRed : 0;
      b.setVal(levelRed, moveRed, b, Red);
      b.display(R, C, b.place);//display the game
      noWinner = b.checkWinner(); ///board filled...is there a draw
    }

  }
  
  printWinner(noWinner, Red, Blu);

}//void function returns nothing



void Game::printWinner(int res, int redVal, int bluVal){//prints the results
   if(res==redVal){
     cout << "Player One Wins: increase the limit if you want computer to win" << endl;
   }else if(res==bluVal){
     cout << "Player Two Wins" << endl;
   }else{
    cout << "No winning position, it's a draw!!" << endl;
   }
}


