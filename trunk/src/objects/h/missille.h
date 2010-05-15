#ifndef ___MISILLE____
#define ___MISILLE____
#include "../../graphic/h/images.h"
#include "objects.h"

class Missille : public Object
{
//	bool nowhereToRun;
public:

	Missille(Skin * s, List * list);
	virtual bool is_blocking();
	void move(size_t fps);
	virtual void hitted(Object *o, Position dir, int attack);
	virtual void hit(Object *o);
	~Missille();
};

#endif
