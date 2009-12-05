#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../add-ons/h/position.h"
#include "../../graphic/h/images.h"

struct Map;

struct Type_bot
{
	int sigth, angle, defense, misille; //kolko toho vidi, aku ma obranu, aku zbran, kde je jeho exit, sila utoku
};

struct Type_missille
{
	int attack, hitpoints; //a tak podobne, TODO!
};

struct ObjectMovement
{
	Position old_pos;
	Position position_in_map;
	Position direction;
	float fps; //maximalne rychlost
};

class Object // abstraktna klassa, ktora je predkom botov, strely aj Walls 
{
protected:
	ImageSkinWork * skinWork;
public:
	Map * map;
	virtual bool is_blocking();
	ObjectMovement movement; //kde sa prave nachadza na mape
	std::string name;
	int defense, attack;
	int hitpoints;
	Uint32 ticks; //zdravie a interval, po jakom sa naplanuje dalsia akcia
	Object();
	Position get_pos() const;
//	virtual void damage(Object * sender) = 0;
	SDL_Surface * show();
	virtual void action(Map * m);
	void collision(Position collidedVector);
	bool collideWith(Object * o, Position& pos);
	Position get_size();


	int IsMoving();
	int IsWall();
	int IsPlayer();
	int IsMissille();
	SDL_Rect get_rect();
	Position Locate();
	int Hit();
};
class Nullable : public Object
{
};

#endif
