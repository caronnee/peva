#include "movement.h"
Movement::Movement()
{
	addiction=x=y=interval=0;
}
Movement::Movement(int v,int x,int y)
{
	this->addiction=v;this->x=x;this->y=y;
}
Movement::Movement(const Movement& a)
{
	addiction=a.addiction;
	x=a.x;
	y=a.y;
}
void Movement::swap(Movement &a)
{
	Movement pom(*this);
	*this=a;
	a=pom;
}
Movement& Movement::operator=(const Movement& a) 
{
	this->x=a.x;
	this->y=a.y;
	this->interval=a.interval;
	this->addiction=a.addiction;
	return *this;
}

