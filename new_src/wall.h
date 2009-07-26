//TODO mozno este jedna treasurewall, cez kpru ide strielat a ktora pridava body,koniec vdety ked su pstatni mrtvi, ked sa vyzbiera vsetko a niekto zapadne do exitu, odomknuty exit po vyzbierani vsetkeho...uzivatelom toto definovane
//pri pisani kodu este jeda special funkcia exit(EXIT & Bonus <=30 & killed == 5). ALL_EXIT, (vsetky exity alebo navzialenejsi...
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
	ExitWall_,
	NumberOfWalls_
};
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
class ExitWall:public Tile // Kam sa ma robot dostat 
{
public:
	ExitWall();
	//virtual void damage(Object * sender);
};
#endif