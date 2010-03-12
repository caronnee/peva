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
	/* object seen */
	std::list<ObjectRelation> visibleObjects;

	/* maximum  sight */
	size_t size;

	/* angle to first border of circular sector, angle of right, in radians */
	float angleLeft, angleRight;

	/* marking object as visible */
	void addToVisible(ObjectRelation& rel);

public:
	Seer();
	void setEyes(int angle, int defaultVisibility);
	void setEyes(Position eyeDimension_);
	void reset( );
	Object * getObject(size_t index);
	void output();
	void fill(Object * o, Position position);
	int checkVisibility();
};

#endif
