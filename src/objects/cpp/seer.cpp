#include "../h/seer.h"

Seer::Seer(int angle, int defaultVisibility)
{
	eyeDimension.turn(angle,defaultVisibility);
	reset();
}
Seer::Seer(Position eyeDimension_) 
{
	eyeDimension = eyeDimension_;
	reset();
}
void Seer::reset()
{
	visibleObjects.clear();
	//rovnica, v tvare 0 = Ax + By + C pre jednu aj pre druhu stranu
	int xn = eyeDimension.x, yn = eyeDimension.y;
	aLeft = yn; 
	bLeft = xn;
	cLeft = 0;
	aRight = -yn;
	bRight = xn;
	cRight = 0;
}
void Seer::checkVisible(Object * o, Position position, int angle)
{
	bool visible = true;
	Position objectPosition = o->get_pos();
	objectPosition.substractVector(position);
	objectPosition.turn(-angle); //zpat do pozicie 0
	if(aLeft * objectPosition.x + bLeft * objectPosition.y > 0)
		return;
	if(aRight * objectPosition.x + bLeft * objectPosition.y < 0)
		return;
	//zorad do pola zotriedene podla x-ovej osy
}
