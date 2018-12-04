#pragma once



#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

using namespace std;

//https://stackoverflow.com/questions/2392093/searching-and-inserting-in-a-map-with-3-elements-in-c
typedef map< int, pair<char, pair<int, bool> > > Maptype;

class fishes{
public:
	char chooseFish(int randNo);
};

class mapStatus : public fishes{
public:
	void initMap();//generate the random num inside initmap
	char getMyFish();
	map< int, int > fishSpecieMap(char);
	int moveFish(int, bool, bool, bool, int, int, int);
	int resultantMove(int key, char fish, int randMove);

	//Changes to be made in keys after the move
	bool consumptionStatus(char keyFish, char nextKeyFish);
	char keyType(char keyFish, char nextKeyFish, int keyCount, bool arrival);
	int countFish(char keyFish, char nextKeyFish, int keyCount, int nextKeyCount, bool arrival, bool consumption);

	void updateArrivalSite(int key, char keyFishBefore, int randMove);
	void killAll(int key);
	void feedingFrenzy(int key, char keyFish, int randMove);

	bool SWEEP();
	void getRunning();

private:
	int sweepCount = 0;
};

#endif /* FUNCTIONS_H_ */
