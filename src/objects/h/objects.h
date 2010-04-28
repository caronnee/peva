//VIRTUALNE JE LEN KOLIZIA, OVE PREBOEHA STEJNE
#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../../add-ons/h/position.h"
#include "../../graphic/h/images.h"

#define PROBABILITY 10
#define MY_INFINITY ~0
#define MAX_PX_PER_SECOND 100

enum ObjectsToSave
{
	SaveDummy = -1,
	SaveWall = 0,
	SaveBreakableWall, 
	SaveTrapWall,
	SavePushableWall,
	SaveStart,
	SaveTarget,
	NumberOfObjectToSave
};
struct ObjectMovement
{
	/* real x coord*/
	float realX;

	/* real y coord*/
	float realY;

	/* object speed, pixels per turn */
	size_t speed;

	/* actual position in map */
	Position position_in_map;

	/* used when moving for determinig old position, not necessary */
	Position old_pos;

	/* direction */
	Position direction;

	/* how many steps is object allowed to take */
	int steps;
	
	/* actual angle of robot */
	int angle;

	/* sets to default value */
	void clean();
};

class Object
{

private:
	/* last object that attacked this */
	Object * last_attack;

protected:
	/* checks if iobject intersection, if so, returning in p, coords */
	bool intersection(Object *o, Position &p1, Position& coords);

	/* id of type of object*/
	size_t type;

public:
	enum Substantial
	{
		Miss = 0,
		Solid = 1 //solid + miss = solid
	};
	enum Objects
	{
		Nothing = 0,
		Player = 1,
		Wall_ = 2,
		Missille = 4 
	};
	/* for saving purposes, object ID */
	ObjectsToSave objectSaveId;

	/* tells tha graphic if ther i something changed in picture that should be redrawed */
	virtual bool changed();

	/* information about object fo later resurrection from file */
	std::string saveInfo();

	/* name of the object, for debugging purposes */
	std::string name;

	/* Worker with the inages representing states of object */
	ImageSkinWork * skinWork;

	/* number of enemies killed by this object */
	size_t numberOfKilled;
public:
	/* for debugging purposes, return information about the object */
	std::string info() const;

	/* substance *///TODO privat a vlastna funkcia
	Substantial substance;

	/* object properties */
	int defense, attack_, hitpoints;

	/* from which object should attacker bounce */
	virtual void bounce(Object * from);

	/* who cause the object to live, animate etc. */
	Object * owner;

	/* what will object do when is finished movement */
	virtual void dead();

	/* returns whether is object alive */
	bool alive();

	/* constructor */
	Object(Skin * s);

	/* for optimaliozation */
	bool blocksMove();

	/* where exactly is the object, filling movement */
	void setPosition(Position p, int angle = 0);

	/* moves in the desired direction, not mentioning obstacles */
	virtual void move(int fps);

	/* returns direction of robot in degrees */
	int getAngle()const;

	/* what happens after finishing movement, should be virtual? *///FIXME
	void endMove();

	/* turn to desired position according to direction*/
	int turn(int angle);

	/* turn to desired position */
	int absoluteTurn(int angle, size_t size = MAX_PX_PER_SECOND);

	/* for visibility, it is good to know whether object is transparent */
	virtual bool is_blocking();

	/* data considering move action, public because of map correction */
	ObjectMovement movement; 

	/* return actual position from movement, just user friendly function */
	Position get_pos() const;

	/* return acual position from movement, just user friendly function */
	Position get_old_pos() const;

	/* for drawing purposes, function return image of object in all states */
	SDL_Surface * show();

	/* ~Setting skin */
	void setSkin(Skin * s);

	/* asking about skin */
	bool hasSkin();

	/* returns rectagle of image with collision */
	Rectangle collisionSize() const;

	/* sets object ast he oe responsible for object death */
	virtual void killed(Object * o);

	/*resolves item behaviour if it is hit */
	virtual void hit(Object * o);

	virtual void hitted(Object * o, Position direction, int attack);
	/* checks if ther is a collision */


	/* returns size of image that should be visible */
	Position get_size();

	/* returns size of image that should be visible */
	Position get_begin();

	/* return width of image being drawn */
	size_t width();

	/* return height of image being drawn */
	size_t height();

	/* for robot questioning state of object */
	int Hit();

	/* check, whether objcet is moving for optimalization and robot instruction purposes */
	bool isMoving();

	/* for robot questioning state of object */
	int typeObject()const;

	/* return SDL rectangle information about image to be blit */
	SDL_Rect get_rect();

};

#endif
