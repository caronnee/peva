#ifndef __WALLS__
#define __WALLS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "objects.h"

// public Tile len pre zachovanie urovne abstrakcie, aby bolo ajsne, ze chceme iba steny a pri prepisovani kodu sa tam nepchali nejake ine objekty, viz bot alebo strela

class Wall:public Object //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	Wall(Skin * skin);
	void hitted(Object * attacker, Position p, int attack); 
	std::string saveInfo();
};

class BreakableWall:public Object //da sa nou pohnut
{
public:
	BreakableWall(Skin * skin);
	void hit(Object * o);
	void hitted(Object * o, Position p, int attack);
};
class PushableWall:public Object //da sa nou pohnut
{
	size_t defaultStep;
public:
	PushableWall(Skin * skin);
	void hit(Object *o);
	void hitted(Object *o, Position p, int attack);
};
class TrapWall:public Object // ostepy na zemi sa vystrkujuce:)
{
	bool invisible;
public:
	TrapWall(Skin * skin);
	bool is_blocking();
	void hit(Object *o);
	void hitted(Object *o, Position p, int attack);
};
#endif
