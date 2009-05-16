#include <SDL/SDL.h>
#include "object.h"

enum WallType
{
	SolidWall = 0, //o okolo sa to maposutu doprava pre masku
	PushableWall,
	TrapWall,
	ExitWall;
	NumberOfWalls;
}
class Tile:public Object //oddelenie urovne abstrakcie:)
{
public:
	Tile();
	//virtual void damage(Object * sender);
};
class SolidWall:public Tile //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	SolidWall();
	//virtual void damage(Object * sender); 
};

class PushableWall:public Tile //da sa nou pohnut
{
public:
	PushableWall();
	//virtual void damage(Object * sender);
};
class TrapWall:public Tile // opstey na zemi sa vystrkujuce:)
{
public:
	TrapWall();
	//virtual void damage(Object * sender);
};
class ExitWall:public Tile // opstey na zemi sa vystrkujuce:)
{
public:
	ExitWall();
	//virtual void damage(Object * sender);
};
