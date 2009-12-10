#ifndef ___BODY_INTERFACE____
#define ___BODY_INTERFACE____

#include "../../objects/h/objects.h"

class Body : public Object
{
	int default_steps;
public:
	/* Constructor */
	Body();

	/* return number of objects, that can robot see */
	int see();
	
	/* return object that can robot see at index position */
	Object * eye(int index);

	/* Return an indication, wheter robot can be moved steps steps */
	int step(int steps);

	/* set movement to default steps */
	int step();
	
	/* for later use */
	int wait(int x = 0);
	
	/* Shoots a missille in the direction dir, if any left */
	int shoot(int x, int y);
	
	/* turns left*/
	int turnL();
	
	/* turns right*/
	int turnR();

	/* returns true, becuse it is not transparent */
	virtual bool is_blocking();
};
#endif