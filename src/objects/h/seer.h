#ifndef ___SEER____
#define ___SEER____

#include <iostream>
#include <list> //kvoli efektivnemu odoberaniu


#include "../../add-ons/h/position.h"
#include "objects.h"
#include "seer.h"

struct ObjectRelation
{
	Object * object;
	Rectangle rect;
	int dirty;
};

class Seer
{
	std::list<ObjectRelation> visibleObjects;
	//cez tangenty!
	int aLeft,bLeft,cLeft;
	int aRight,bRight,cRight;

public:
	Position eyeDimension;
	Seer();
	void setEyes(int angle, int defaultVisibility);
	void setEyes(Position eyeDimension_);
	void reset();
	Object * getObject(size_t index);
	void output();
	void fill(Object * o, Position position);
	int checkVisibility();
};

#endif
