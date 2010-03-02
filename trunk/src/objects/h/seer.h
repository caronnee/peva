#ifndef ___SEER____
#define ___SEER____

#include <iostream>
#include <list> //kvoli efektivnemu odoberaniu

#include "../../add-ons/h/position.h"
#include "objects.h"

class Seer
{
	Position eyeDimension;
	std::list<Object *> visibleObjects;
	int aLeft,bLeft,cLeft;
	int aRight,bRight,cRight;
public:
	Seer(int angle, int defaultVisibility);
	Seer(Position eyeDimension_);
	void reset();
	bool isVisible(Object *o, Position position, int visibleAngle);
	Object * getObject(size_t index);
	void output();
	void checkVisible(Object * o, Position position, int angle);

};

#endif
