#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "position.h"

struct Map;

struct Type_bot
{
	int sigth, angle, defense, misille; //kolko toho vidi, aku ma obranu, aku zbran, kde je jeho exit, sila utoku
};
struct Type_missille
{
	int attack, hitpoints; //a tak podobne, TODO!
};

class Object // abstraktna klassa, ktora je predkom botov, strely aj Walls 
{
public:
	Position old_pos;
	Map * map;
	virtual bool is_blocking();
	SDL_Surface * image;
	Position position_in_map, direction; //kde sa prave nachadza na mape
	std::string name;
	int defense, attack;
	int hitpoints;
	Uint32 ticks; //zdravie a interval, po jakom sa naplanuje dalsia akcia
	Object();
	Position get_pos() const;
//	virtual void damage(Object * sender) = 0;
//	virtual void action() = 0;
	SDL_Surface * show();
	virtual void action();
	int IsMoving();
	int IsWall();
	int IsPlayer();
	int IsMissille();
	int Locate();
	int Hit();
};

class Missille : public Object
{
	float fps;
	Uint32 milisec;
//	Uint32 hlp;
public:
	virtual bool is_blocking();
	virtual void damage(Object* sender);
	virtual void action(); //penalizacia
	virtual void defense();
	Missille(Position p, Position dir);
};
#endif
