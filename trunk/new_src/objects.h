#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include "position.h"

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
protected:
	SDL_Surface * image;
	Position position;
	int hit_points,ticks; //zdravie a interval, po jakom sa naplanuje dalsia akcia
public:
	Object();
//	virtual void damage(Object * sender) = 0;
//	virtual void action(Walls *** game) = 0;
	SDL_Surface * show();
};
#endif
