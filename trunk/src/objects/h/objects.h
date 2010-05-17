//VIRTUALNE JE LEN KOLIZIA, OVE PREBOEHA STEJNE
#ifndef __OBJECTS__
#define __OBJECTS__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <list>
#include "../../add-ons/h/position.h"
#include "../../add-ons/h/macros.h"
#include "../../graphic/h/images.h"

#define PROBABILITY 10
#define MY_INFINITY ~0

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
	int speed;

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
public:
	/* checks if iobject intersection, if so, returning in p, coords */
	bool intersection(Object *o, Position &p1, Position& coords);

	/* where an object should go after dead */
	List * abyss_;

	/* id of type of object*/
	size_t type;

	/* name of the object, for debugging purposes */
	std::string name;

	/* Worker with the inages representing states of object */
	ImageSkinWork * skinWork;

private:
	/* information about object fo later resurrection from file */
	std::string saveInfo();

	/* number of enemies killed by this object */
	size_t numberOfKilled;
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
		Missille_ = 4 
	};

	/* for saving purposes, object ID */
	ObjectsToSave objectSaveId;

	/* for debugging purposes, return information about the object */
	std::string info() const;

	/* tells tha graphic if there is
	 * something changed in picture that should be redrawed */
	virtual bool changed();

	/* substance *///TODO privat a vlastna funkcia
	Substantial substance;

	/* object properties */
	int defense, attack, hitpoints;

	/* from which object should attacker bounce */
	virtual void bounce(Object * from);

	/* who cause the object to live, animate etc. */
	Object * owner;

	/* what will object do when is finished movement */
	virtual void dead();

	/* returns whether is object alive */
	bool alive();

	/* constructor */
	Object(Skin * s, List * abyss_);

	/* for optimaliozation */
	bool blocksMove();

	/* where exactly is the object, filling movement */
	void setPosition(Position p, int angle = 0);

	/* moves in the desired direction, not mentioning obstacles */
	virtual void move(size_t fps);

	/* returns direction of robot in degrees */
	int getAngle()const;

	/* what happens after finishing movement, should be virtual? *///FIXME
	void endMove();

	/* turn to desired position according to direction*/
	int turn(int angle);

	/* turn to desired position */
	int absoluteTurn(int angle);

	/* for visibility, it is good to know whether object is transparent */
	virtual bool is_blocking();

	/* data considering move action, public because of map correction */
	ObjectMovement movement; 

	/* return actual position from movement */
	virtual Position get_pos() const;

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

	/* checks if ther is a collision */
	virtual void hitted(Object * o, Position direction, int attack);

	/* returns size of image that should be visible */
	Position get_size();

	/* returns size of image that should be visible */
	Position get_begin();

	/* return width of image being drawn */
	size_t width();

	/* return height of image being drawn */
	size_t height();

	/* for robot questioning state of object */
	virtual int Hit()const;

	/* check, whether objcet is moving for optimalization and robot instruction purposes */
	virtual bool isMoving();

	/* for robot questioning state of object */
	int typeObject()const;

	/* return SDL rectangle information about image to be blit */
	SDL_Rect get_rect();
};

class Dummy : public Object
{
public: 
	/* constructor */
	Dummy();

	/* return rndom value up to 100 */
	int Hit()const;

	/* returns radom bool */
	bool isMoving();

	/* returns random position, no need to be valid */
	Position get_pos()const;
};
#endif
