#include "../h/movement.h"
Movement::Movement()
{
	addiction=x=y=interval=0;
}
Movement::Movement(int v,int x,int y)
{
	this->addiction=v;
	this->x=x;
	this->y=y;
}
/*Movement::Movement(const Movement& a)
{
	addiction=a.addiction;
	x=a.x;
	y=a.y;
	interval = a.interval;
}*///staci nam defaultny
void Movement::swap(Movement &a)
{
	Movement pom(*this);
	this->addiction = a.addiction;
	this->x = a.x;
	this->y = a.y;
	this->interval = a.interval; //FIXME light, spravit cez metody SET
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

