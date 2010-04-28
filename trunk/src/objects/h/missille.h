#ifndef ___MISILLE____
#define ___MISILLE____
#include "../../graphic/h/images.h"
#include "objects.h"
#include "body.h"

class Missille : public Object
{
	Uint32 milisec;
	bool nowhereToRun;
	Body * owner;
public:

	virtual bool is_blocking();

	void move(int fps);
	virtual void dead();
	virtual void bounce(Object * o);
	virtual void hitted(Object *o, Position dir, int attack);
	virtual void hit(Object *o);
	Missille(Skin * s, Body *);
	~Missille();
};

#endif
