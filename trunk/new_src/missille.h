#ifndef ___MISILLE____
#define ___MISILLE____
#include "objects.h"
#include "map.h"

class Missille : public Object
{
	float fps;
	Uint32 milisec;
//	Uint32 hlp;
public:
	virtual bool is_blocking();
	virtual void damage(Object* sender);
	virtual void action(Map * m); //penalizacia
	virtual void defense();
	Missille(Position p, Position dir);
};

#endif
