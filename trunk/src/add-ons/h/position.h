#ifndef __POSITION_____
#define __POSITION_____

//TODO zovsebecnit ne vektory
#include <cstdlib> 
#include <iostream>

class Position
{	
public:
	int x,y;
	Position();
	Position(int x_,int y_);
	void absolute();
	Position& operator=(const Position &a);
	Position& operator+=(const Position &a);
	Position& substractVector(Position p1);
	bool operator>=(Position &a);
	bool operator==(Position &p);
	bool operator!=(Position &p);
	friend std::ostream& operator<<(std::ostream & o, const Position p);
	size_t getDistance(Position p);
	Position & turn(int degree, int size);
	Position & turn(int degree);
//	Position & turn(float degree, int size);
//	Position & turn(float degree);
};

struct Rectangle
{
	int x,y,width,height;
	Rectangle(Position begin, Position dimension);
	Rectangle(int x_,int y_,int width_,int heigth_);
	Rectangle();
	bool overlaps(Rectangle & rectangle ) const;
	bool overlaps(Position & position ) const;
};

#endif
