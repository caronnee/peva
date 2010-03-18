#ifndef ___SEER____
#define ___SEER____

#include <iostream>
#include <list> //kvoli efektivnemu odoberaniu
#include "../../add-ons/h/position.h"
#include "objects.h"
#include "seer.h"

struct ObjectRelation
{
	/* object of interest */
	Object * object;

	/* relative rectangle to seer center*/
	Rectangle rect;

	/* circular sector bordered by two angles */
	float angleBegin, angleEnd;

	/* distance from center */
	size_t distance;
};

/* class representing eyes of robot */
class Seer
{
	/* object seen */
	std::list<ObjectRelation> visibleObjects;

	/* angle to first border of circular sector, angle of right, in radians */
	float angleBegin_, angleEnd_, angleBegin, angleEnd;

	/* marking object as visible */
	void addToVisible(ObjectRelation& rel);

public:
	/* constructor, set class to be blind */
	Seer();

	/* setting eye constraint with given angle and size */
	void setEyes(int angle, int defaultVisibility);

	/* maximum  sight */
	size_t size;

	/* return angle cco*/
	static int getDegree(Object *o, Position point );
	static float getRadian(Object *o, Position point );

	/* setting eye with given triagle (0,0),(0,x),(0,y)*/
	void setEyes(Position eyeDimension_);

	/* reseting to default state */
	void reset( float angle );

	/* returns object, that is viible at position index */
	Object * getObject(size_t index);

	/* prints to default output information about visible objects */
	void output();

	/* determies, wheather an object is in seeable angle */
	void fill(Object * o1, Object * o2);

	/* removing objects that are covered by another objects */
	int checkVisibility();
};

#endif
