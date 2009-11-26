#ifndef ___BODY_INTERFACE____
#define ___BODY_INTERFACE____

#include "../../objects/h/objects.h"

class Body : public Object
{
	int default_steps;
public:
	/* return number of objects, that can robot see */
	int See();
	/* return object that can robot see at index position */
	Object * Eye(int index);
	/* Return an indication, wheter robot can be moved steps steps */
	int Step(int steps);
	int Step();
	/* for later use */
	int Wait(int x = 0);
	/* Shoots a missille in the direction dir, if any left */
	int Shoot(int x, int y);
	/* turn in the direction dir */
	int Turn(int angle);
	/* turns left*/
	int TurnL();
	int TurnR();
	virtual bool is_blocking();
};
#endif
