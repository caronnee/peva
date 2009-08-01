#ifndef __POSITION_____
#define __POSITION_____

#include <cstdlib> 
#include <iostream>

class Position
{	
public:
	int x,y;
	Position();
	Position(int x_,int y_);
	Position& operator=(const Position &a);
	bool operator>=(Position &a);
};

#endif
