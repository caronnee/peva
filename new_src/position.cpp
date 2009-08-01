#include  "position.h"

Position::Position()
{
	x=rand();
	y=rand();
}
Position::Position(int x_,int y_)
{
	x=x_;
	y=y_;
}
Position& Position::operator=(const Position &a)
{
	this->x=a.x;
	this->y=a.y;
	return *this;
}
bool Position::operator>=(Position &a)
{
	return ((this->x>=a.x)||(this->y>=a.y));
}
