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
	/* object speed, pixels per turn */
	size_t speed;

	/* used when moving for determinig old position, not necessary */
	Position old_pos;

	/* actual positio in map */
	Position position_in_map;

	/* direction */
	Position direction;

	/* frame per second */
	float fps; 

	/* how many steps is object allowed to take */
	int steps;
	
	/* actual angle */
	int angle;
};

class Object // abstraktna klassa, ktora je predkom botov, strely aj Walls 
{
protected:
public:
	/* who cause the object to live, animate etc. */
	size_t owner;

	/* name of th object, for debugging purposes */
	std::string name;

	/* Worker with the inages representing states of object */
	ImageSkinWork * skinWork;

	/* object properties */
	int defense, attack, hitpoints;

	/* find out how much tim e passed since last blit */
	Uint32 ticks;
public:
	/* constructor */
	Object();

	/* moves in the desired direction, not mentioning obstacles */
	void move();

	/* turn sin desired position */
	void turn(int angle);

	/* do an action, change state or so */
	virtual void action();

	/* for visibility, it is good to know whether object is transparent */
	virtual bool is_blocking();

	/* data considering move action, public because of map correction */
	ObjectMovement movement; 

	/* return acual position from movement, just user friendly function */
	Position get_pos() const;

	/* for drawing purposes, function return image of object in all states */
	SDL_Surface * show();

	void collision(Position collidedVector);
	bool collideWith(Object * o, Position& pos);

	/* returns size of image that should be visible */
	Position get_size();

	/* return width of image being drawn */
	size_t width();

	/* return height of image being drawn */
	size_t height();

	/* for robot questioning state of object */
	Position Locate();

	/* for robot questioning state of object */
	int Hit();

	/* check, whether objcet is moving for optimalization and robot instruction purposes */
	int isMoving();

	/* for robot questioning state of object */
	int isWall();

	/* for robot questioning state of object */
	int isPlayer();

	/* for robot questioning state of object */
	int isMissille();

	/* return SDL rectangle information about inage to be blit */
	SDL_Rect get_rect();
};

/* dummy object used as singleton representing NULL */
class Nullable : public Object
{
};

#endif
