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
	Position& operator+=(const Position &a);
	bool operator>=(Position &a);
};

struct Rectangle
{
	int x,y,width,height;
	Rectangle(Position begin, Position dimension);
	Rectangle(int x_,int y_,int width_,int heigth_);
	Rectangle();
};

#endif
