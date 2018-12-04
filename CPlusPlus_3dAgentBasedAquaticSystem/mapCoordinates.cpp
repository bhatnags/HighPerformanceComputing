#include "mapCoordinates.h"

int coordinates::xGetMove(char fish, int randMove){
	int xMove;
	if((fish=='m')&&(randMove==1)){
		xMove=1;
	}else if((fish=='t')&&(randMove!=2)){
		xMove=1;
	}else if((fish=='s')&&(randMove==1)){
		xMove=2;
	}else if((fish=='s')&&(randMove!=1)){
		xMove=1;
	}else{
		xMove=0;
	}
	return xMove;
}

int coordinates::yGetMove(char fish, int randMove){
	int yMove;
	if((fish=='m')&&(randMove==2)){
		yMove=1;
	}else if((fish=='t')&&(randMove!=3)){
		yMove=1;
	}else if((fish=='s')&&(randMove==2)){
		yMove=2;
	}else if((fish=='s')&&(randMove!=2)){
		yMove=1;
	}else{
		yMove=0;
	}
	return yMove;
}

int coordinates::zGetMove(char fish, int randMove){
	int zMove;
	if((fish=='m')&&(randMove==3)){
		zMove=1;
	}else if((fish=='t')&&(randMove!=1)){
		zMove=1;
	}else if((fish=='s')&&(randMove==3)){
		zMove=2;
	}else if((fish=='s')&&(randMove!=3)){
		zMove=1;
	}else{
		zMove=0;
	}
	return zMove;
}

int coordinates::xSetCoordinates(int key, bool xDir){ // need key and direction
  int x;
  x = key;
  if(xDir){ //positive => 1 to 2 => 0-24 -> 100-124
    if(key<100){x += 25;}
    else{x -=100;}
  }else{
    if(key<25){x += 100;}
    else{x -= 25;}
  }
return x;
}

int coordinates::ySetCoordinates(int key, bool yDir){
  int y;
  y = key;
  if(yDir){ //positive => 4 to 3 => mod = 0 to 4
   if(key%5<4){y ++;}
   else{ y -=4;}
  }else{
   if(key%5==0){y += 4;}
   else{ y --;}
  }
return y;
}

int coordinates::zSetCoordinates(int key, bool zDir){
  int z, mod;
  z = key;
  mod = key%5;
  if(zDir){ //positive => 6 to 5 => mod 0:4 to 20:24
    if((mod == 20)||(mod == 21)||(mod == 22)||(mod == 23)||(mod == 24)){z -= 20;}
    else { z+= 5;}
  }else{
    if((mod == 0)||(mod == 1)||(mod == 2)||(mod == 3)||(mod == 4)){ z+= 20;}
    else{z -= 5;}
  }
return z;
}
