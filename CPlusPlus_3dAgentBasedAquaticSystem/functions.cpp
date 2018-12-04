//=======================================================================================================================================================================
// Name	 	: main.cpp
// Author	: Saumya Bhatnagar
// Description	: Agent based model of Aquatic System
// Ref Link	: https://stackoverflow.com/questions/25932545/3d-grid-of-bins-nested-stdvector-vs-stdunordered-map
//========================================================================================================================================================================

#include <cassert>
#include <iostream>
#include <string.h>
#include <cassert>
#include <map>
//#include <random>
//#include <functional>
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>
#include "functions.h"
#include "myrand.h"
#include "mapCoordinates.h"

#define SIZE 5
#define SYSTEM_SIZE 5*5*5
using namespace std;

Maptype my_map;

char fishes::chooseFish(int randNo){
  char fish;
  int putVal;
  putVal = randNo % 3;
  switch(putVal){
    case 0 : fish = 'm'; break;
    case 1 : fish = 't'; break;
    case 2 : fish = 's'; break;
    default : fish = 'b';
  }
return fish;
}

void mapStatus::initMap(){
	fishes f;
	randFunctions r;
	int i, dist_mt;
	char fishType;
	fishType ='b';
	int FishCount = 1; //initialize every fish site with 1 fish count
	bool ate = false;

	for (i=0; i<SYSTEM_SIZE; i++){ //create the system //insert to map
		dist_mt = r.mersenneRand(100);
		fishType = f.chooseFish(dist_mt);
		my_map.insert( make_pair( i, make_pair(fishType, make_pair(FishCount, ate) ) ) );
	}
	/* get prints for checking the stored values
	//	for(auto &i: my_map)
	//	cout << i.first << "\t" << i.second << endl;
	//	cout << "~~~~~~~~~~~~~~~~~~~~~~`" << endl;
	*/
}

char mapStatus::getMyFish(){

	char fishType = 'b';
	int dist_mt;
	randFunctions r;

	//a single fish from that specie is chosen at random
	while(fishType == 'b'){
		dist_mt = r.mersenneRand(100);
		fishType = chooseFish(dist_mt); //gives character
	}
	return fishType;
}

map< int, int > mapStatus::fishSpecieMap(char fishType){
	
	int fish_num=0;

	map< int, int > fish_map;

	if(fishType=='b'){
		fishType = getMyFish(); //no fish
	}

	for(auto &i: my_map){
		if(i.second.first== fishType){
			fish_map.insert( make_pair( fish_num, i.first) );
			fish_num++;
		}
	}
	return fish_map;
}

int mapStatus::moveFish(int key, bool xDir, bool yDir, bool zDir, int xMove, int yMove, int zMove){//move 1 step in any direction
	coordinates c;
	int move, x = 1, y = 1, z = 1;
	move = key;
	while(x<xMove){
		move = c.xSetCoordinates(move, xDir); x++;
	}
	while(y<yMove){
		move = c.ySetCoordinates(move, yDir); y++;
	}
	while(z<zMove){
		move = c.zSetCoordinates(move, zDir); z++;
	}
return move;
}

int mapStatus::resultantMove(int key, char fish, int randMove){//randMove is a random number generated between 1:3
	coordinates c;
	randFunctions r;

	int move;
	bool xDir, yDir, zDir;
	int xMove, yMove, zMove;
	// Set directions
	xDir = r.randomBool();
	yDir = r.randomBool();
	zDir = r.randomBool();
	//Set movements
	xMove = c.xGetMove(fish, randMove);
	yMove = c.yGetMove(fish, randMove);
	zMove = c.zGetMove(fish, randMove);

	move = moveFish(key, xDir, yDir, zDir, xMove, yMove, zMove);
	return move;
}

bool mapStatus::consumptionStatus(char keyFish, char nextKeyFish){//will change for arrival site only
	bool nextKeyAte;
	if((nextKeyFish !='b' )||(keyFish != nextKeyFish)){
		nextKeyAte = true;
	}
	return nextKeyAte;
}

char mapStatus::keyType(char keyFish, char nextKeyFish, int keyCount, bool arrival){//get key type based on if the it's arrival site or not
	char type ;
	if(arrival){
		type = nextKeyFish;
		if((keyFish=='s')||(nextKeyFish=='s')){
			type = 's';
		}else if(nextKeyFish=='b'){
			type = keyFish;
		}else if(keyFish=='t'){
			type = keyFish;
		}
	}else{
		type = keyFish;
		if(keyCount==1){
			type = 'b';
		}
	}
	return type;
}

int mapStatus::countFish(char keyFish, char nextKeyFish, int keyCount, int nextKeyCount, bool arrival, bool consumption){
	char count ;
	if(arrival){
		count = nextKeyCount;
		if(nextKeyFish != keyFish){
			if((nextKeyFish=='b')||(nextKeyFish=='m')||((nextKeyFish=='t')&&(keyFish=='s'))){
				count = 1;
			}else{
				count = nextKeyCount;
			}
		}else if(nextKeyCount>1){
			if(nextKeyFish == 'm'){
				count = nextKeyCount+3;
			}else if((nextKeyFish == 't')&&(consumption)){
				count = nextKeyCount+2;
			}else if((nextKeyFish == 's')&&(consumption)){
				count= nextKeyCount+2;
			}else{
				count= nextKeyCount++;
			}
		}else{
			count= nextKeyCount++;
		}
	}else{
		count = keyCount--;
	}
	return count;
}

void mapStatus::updateArrivalSite(int key, char keyFishBefore, int randMove){

	/*Understanding
	//map< int,   pair<char,         pair<int,                 bool> > >
	//   key      my_map[key].first  my_map[key].second.first  my_map[key].second.second
	*/

	//key of the arrival site
	int nextKey;
	//fish type of the sites, before and after attack
	char keyFishAfter, nextKeyFishBefore, nextKeyFishAfter;
	//count of fishes at the sites, before and after attack
	int keyCountBefore, nextKeyCountBefore,keyCountAfter, nextKeyCountAfter;
	//consumption status of arrival site before and after attack
	bool consumptionBefore, consumptionAfter;

	//Before attack
	nextKey = resultantMove(key, keyFishBefore, randMove); 
	nextKeyFishBefore = my_map[nextKey].first;
	keyCountBefore = my_map[key].second.first;
	nextKeyCountBefore = my_map[nextKey].second.first;
	consumptionBefore =  my_map[nextKey].second.second;

	//After attack 
	keyFishAfter = keyType(keyFishBefore, nextKeyFishBefore, keyCountBefore, false);
	nextKeyFishAfter = keyType(keyFishBefore, nextKeyFishBefore, keyCountBefore, true);
	keyCountAfter = countFish(keyFishBefore, nextKeyFishBefore, keyCountBefore, nextKeyCountBefore, false, consumptionBefore);
	nextKeyCountAfter = countFish(keyFishBefore, nextKeyFishBefore, keyCountBefore, nextKeyCountBefore, true, consumptionBefore);
	consumptionAfter = consumptionStatus(keyFishBefore, nextKeyFishBefore);//will change for arrival site only

	//UPDATE
	my_map[key].first =	keyFishAfter;
	my_map[nextKey].first = nextKeyFishAfter;
	my_map[key].second.first = keyCountAfter;
	my_map[nextKey].second.first = nextKeyCountAfter;
	my_map[nextKey].second.second = consumptionAfter;

}

void mapStatus::killAll(int key){
	my_map[key].first = 'b';
	my_map[key].second.first=0;
	my_map[key].second.second=false;
}

void mapStatus::feedingFrenzy(int key, char keyFish, int randMove){//update adjacent sites in case shark attacks a site with minnows
	coordinates c;

	int zP, zN, yP, yN, xP, xN;
	int nextKey;
	nextKey = resultantMove(key, keyFish, randMove);
	char nextKeyFish;
	nextKeyFish = my_map[nextKey].first;
	if((keyFish == 's')&&(nextKeyFish=='m')){
		zP = c.zSetCoordinates(key, true);// key in z positive direction
		zN = c.zSetCoordinates(key, false);// key in z negative direction
		yP = c.ySetCoordinates(key, true);// key in y positive direction
		yN = c.ySetCoordinates(key, false);// key in y negative direction
		xP = c.xSetCoordinates(key, true);// key in x positive direction
		xN = c.xSetCoordinates(key, false);// key in x negative direction

		if(my_map[zP].first=='m'){			killAll(zP);			}
		if(my_map[zN].first=='m'){			killAll(zN);			}
		if(my_map[yP].first=='m'){			killAll(yP);			}
		if(my_map[yN].first=='m'){			killAll(yN);			}
		if(my_map[xP].first=='m'){			killAll(xP);			}
		if(my_map[xN].first=='m'){			killAll(xN);			}
	}
}

bool mapStatus::SWEEP(){
	randFunctions r;

	int randFish ; //random fish specie selected
	int randMove ; //random move of the selected fish specie
	int key; //the map index of the fish site
	char fishType = 'b';
	int minnowSize, tunaSize, sharkSize; //Num of fishes
	bool alive = true; //if all 3 species have at lease 1 fish alive

	fishType = getMyFish(); //update the randomly selected fish specie Type
	map<int, int> fish_map;
	map<int, int> minnow_map;
	map<int, int> tuna_map;
	map<int, int> shark_map;
	
	fish_map = fishSpecieMap(fishType);
	minnow_map = fishSpecieMap('m');
	tuna_map = fishSpecieMap('t');
	shark_map = fishSpecieMap('s');
	

	//For understanding
	//get the second of randFish
	//use that as first and get the second of that,
	//should be equal to fishType
	randFish = r.mersenneRand(fish_map.size());
	
	minnowSize = minnow_map.size();	
	tunaSize = tuna_map.size();	
	sharkSize = shark_map.size();	

	/* get prints for checking the stored values
	//for(auto &i : fish_map)   cout << i.first << "\t" << i.second << endl;
	//cout << fish_map.size() << endl;
	//cout << my_map[fish_map[randFish]] << "\t" << fishType << endl;
	*/

	randMove = r.mersenneRand(4);
	key = fish_map[randFish];

	updateArrivalSite(key, fishType, randMove);//randMove is a random number generated between 1:3
	feedingFrenzy(key, fishType, randMove);
	if((minnowSize>0)&&(tunaSize>0)&&(sharkSize>0)){
		alive = true;
	}else{
		alive = false;
	}
return alive;
}


void mapStatus::getRunning(){

	int ITER=0;
	bool alive = true; //if all species have at least one fish alive

	initMap();
	for ( ; ITER<1000; ITER++){//Total Iterations = 1000
		cout << "(#Iteration=" << (ITER+1) << ", alive=" << alive << ")\n\n";
		/**********************SWEEP STARTS************************/
		for (sweepCount=0; sweepCount<SYSTEM_SIZE; sweepCount++){//SWEEP = one L^3 update

			alive = SWEEP();
			cout << "(#Sweep=" << sweepCount+1 << ", alive=" << alive << ")\t";
		
		}
		try{
			if(alive==0){throw false;}
		}catch(bool alive){
			cout << "NOT ALL ALIVE(" << alive << ", SYSTEM HALTS" << alive << endl; exit(1);
		}//catch(exception e){
		//	cout << "NOT ALL ALIVE, SYSTEM HALTS" << e.what() << endl; exit(1);
		//}
	
	}
}
