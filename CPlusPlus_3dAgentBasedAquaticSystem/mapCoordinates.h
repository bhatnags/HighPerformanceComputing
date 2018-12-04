#pragma once

#ifndef MAPCOORDINATES_H_
#define MAPCOORDINATES_H_

using namespace std;

class coordinates{
public:
	int	xGetMove(char, int);
	int	yGetMove(char, int);
	int	zGetMove(char, int);
	int xSetCoordinates(int , bool );
	int ySetCoordinates(int , bool );
	int zSetCoordinates(int , bool );
};

#endif /* MAPCOORDINATES_H_ */
