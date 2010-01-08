#ifndef ___MISILLE____
#define ___MISILLE____
#include "../../graphic/h/images.h"
#include "objects.h"
#include "body.h"

class Missille : public Object
{
	Uint32 milisec;
public:
	
	Body * owner;
	virtual bool is_blocking();
	virtual void damage(Object* sender);
	virtual void action();
	virtual void defense();
	virtual void stoppedMoving();
	Missille(Skin * s, Body *);
	Missille(Position p, Position dir, Skin*s);
	~Missille();
};

#endif
