#include <SDL/SDL.h>
#include "object.h"

class Wall:public Object //oddelenie urovne abstrakcie:)
{
public:
	Wall();
	//virtual void damage(Object * sender);
};
class SolidWall:public Wall //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	SolidWall();
	//virtual void damage(Object * sender); 
};

class PushableWall:public Wall //da sa nou pohnut
{
public:
	PushableWall();
	//virtual void damage(Object * sender);
};
class TrapWall:public Wall // opstey na zemi sa vystrkujuce:)
{
public:
	TrapWall();
	//virtual void damage(Object * sender);
};
