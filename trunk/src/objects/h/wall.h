#ifndef __WALLS__
#define __WALLS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "objects.h"

// public Tile len pre zachovanie urovne abstrakcie, aby bolo ajsne, ze chceme iba steny a pri prepisovani kodu sa tam nepchali nejake ine objekty, viz bot alebo strela

class Wall:public Object //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	Wall();
	Wall(Position mapPosition, WallSkin * skin);
	//virtual void damage(Object * sender); 
};

class PushableWall:public Object //da sa nou pohnut
{
public:
	PushableWall();
//	virtual void damage(Object * sender);
};
class TrapWall:public Object // opstey na zemi sa vystrkujuce:)
{
public:
	TrapWall();
//	virtual void damage(Object * sender);
};
#endif
