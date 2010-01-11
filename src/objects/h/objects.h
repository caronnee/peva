//VIRTUALNE JE LEN KOLIZIA, OVE PREBOEHA STEJNE
#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../add-ons/h/position.h"
#include "../../graphic/h/images.h"
#include "../h/list.h"

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

	/* actual position in map */
	Position position_in_map;

	/* direction */
	Position direction;

	/* frame per second */ //TODO global
	float fps; 

	/* how many steps is object allowed to take */
	int steps;
	
	/* actual angle of robot */
	int angle;
};

class Object
{
protected:
public:
	/* name of th object, for debugging purposes */
	std::string name;

	/* Worker with the inages representing states of object */
	ImageSkinWork * skinWork;

	/* object properties */
	int defense, attack, hitpoints;

public:
	/* item containing this object */
	Item * item;

	/* who cause the object to live, animate etc. */
	Object * assistance;

	/* who cause the object to live, animate etc. */
	Object * owner;

	/* what will object do when is finished movement */
	virtual void dead();

	/* returns whether is object alive */
	bool alive();

	/* constructor */
	Object();

	/* for optimaliozation */
	bool blocksMove();
	/* where exactly is the object, filling movement */
	void setPosition(Position p, int angle = 0);

	/* moves in the desired direction, not mentioning obstacles */
	virtual void move();

	/* turn sin desired position */
	int turn(int angle);

	/* for visibility, it is good to know whether object is transparent */
	virtual bool is_blocking();

	/* data considering move action, public because of map correction */
	ObjectMovement movement; 

	/* return acual position from movement, just user friendly function */
	Position get_pos() const;

	/* for drawing purposes, function return image of object in all states */
	SDL_Surface * show();

	/* ~Setting skin */
	void setSkin(Skin * s);

	/* asking about skin */
	bool hasSkin();

//TODO
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
	bool isMoving();

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
