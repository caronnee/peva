#ifndef __WALLS__
#define __WALLS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "objects.h"

// public Tile len pre zachovanie urovne abstrakcie, aby bolo ajsne, ze chceme iba steny a pri prepisovani kodu sa tam nepchali nejake ine objekty, viz bot alebo strela

enum WallType
{
	FreeTile = 0,
	SolidWall_, //o okolo sa to maposutu doprava pre masku
	PushableWall_,
	TrapWall_,
	NumberOfWalls_
};
class ImageTile
{
	public:
		SDL_Surface ** tiles;
		ImageTile(); //naloaduje vsetky obrazky
		SDL_Surface * get_image(WallType);
};
class Tile:public Object 
{
public:
	Tile();
	Tile(ImageTile *);
	virtual bool is_blocking();
//	virtual void damage(Object * sender);
};
class SolidWall:public Tile //nic specialneho, proste sten a s nejkou odolnostou
{
public:
	SolidWall(ImageTile *);
	//virtual void damage(Object * sender); 
};

class PushableWall:public Tile //da sa nou pohnut
{
	int shift; //o kolko sa posunie
public:
	PushableWall(ImageTile *);
//	virtual void damage(Object * sender);
	virtual void action();
};
class TrapWall:public Tile // opstey na zemi sa vystrkujuce:)
{
public:
	TrapWall(ImageTile *);
//	virtual void damage(Object * sender);
};
#endif
