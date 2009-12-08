#ifndef ___MISILLE____
#define ___MISILLE____
#include "../../map/h/map.h"
#include "../../graphic/h/images.h"
#include "objects.h"

class Missille : public Object
{
	float fps;
	Uint32 milisec;
//	Uint32 hlp;
public:
	virtual bool is_blocking();
	virtual void damage(Object* sender);
	virtual void action(); 
	virtual void defense();
	Missille(Position p, Position dir, Skin*s);
	~Missille();
};

#endif
