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
Position& Position::operator+=(const Position &p)
{
	x +=p.x;
	y +=p.y;
	return *this;
}
Rectangle::Rectangle()
{
	x = y = width = height = -1;
}

Rectangle::Rectangle(Position begin, Position dimension)
{
	x = begin.x;
	y = begin.y;
	width = dimension.x;
	height = dimension.y;
}
Rectangle::Rectangle(int x_, int y_, int width_, int height_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
}

