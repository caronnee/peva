#ifndef __WALLS__
#define __WALLS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <list>
#include "../../add-ons/h/macros.h"
#include "objects.h"

// public Tile len pre zachovanie urovne abstrakcie, aby bolo ajsne, ze chceme iba steny a pri prepisovani kodu sa tam nepchali nejake ine objekty, viz bot alebo strela

class Wall:public Object //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	Wall(Skin * skin, List * abyss);
	virtual void hitted(Object * attacker, Position p, int attack); 
	virtual void hit(Object * o);
	~Wall();
};

class BreakableWall:public Wall //da sa nou pohnut
{
public:
	BreakableWall(Skin * skin, List * abyss);
	void hitted(Object * o, Position p, int attack);
	~BreakableWall();
};
class PushableWall:public Wall //da sa nou pohnut
{
	size_t defaultStep;
public:
	PushableWall(Skin * skin, List * abyss);
	void hit(Object *o);
	void hitted(Object *o, Position p, int attack);
	~PushableWall();
};
class TrapWall:public Wall // ostepy na zemi sa vystrkujuce:)
{
	bool invisible;
public:
	TrapWall(Skin * skin, List * abyss);
	bool is_blocking();
	void hitted(Object *o, Position p, int attack);
	~TrapWall();
};
#endif
