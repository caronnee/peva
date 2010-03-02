#include <cmath>
#include  "../h/position.h"
#include  "../h/macros.h"

#define PI 3.14159265

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
size_t Position::getDistance(Position p) 
{
	Position pos = substractVector(p);
	return pos.x*pos.x+pos.y*pos.y; //su to dostatocne male cisla, aby sa to sem voslo
}

bool Position::operator==(Position& p)
{
	if ((x !=p.x)||( y!=p.y))
		return false;
	return true;
}
bool Position::operator!=(Position& p)
{
	return !((*this)==p);
}
Position& Position::substractVector( Position p2 )
{
	x-=p2.x;
	y-=p2.y;
	return (*this);
}
Position& Position::turn(int degree)
{
	return turn(degree, sqrt(x*x + y*y));
}
Position& Position::turn(int degree, int size)
{
	x = sin (degree * PI/180) * size;
	y = -cos (degree * PI/180) * size;
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
bool Rectangle::overlaps(Rectangle & rectangle) const
{
	bool a =  (!(x >= rectangle.x + rectangle.width) && !(x + width <= rectangle.x) && !(y >= rectangle.y + rectangle.height) && !(y + height <= rectangle.y));
	if (a)
		return true;
	return false;

}
std::ostream& operator<<(std::ostream& o, const Position p)
{
	o<<"x:" << p.x <<", "<< "y:" << p.y;
	return o;
}
