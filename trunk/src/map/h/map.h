#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include <list>
#include "../../graphic/h/graphic.h"
#include "../../add-ons/h/position.h"
#include "../../objects/h/objects.h"

/* structure hold object in area */

struct Box
{
	/* Contructor */
	Box();

	/* Bounds of  area*/
	Rectangle bounds; 

	/* Objects in area */
	std::list<Object *> objects; //objects in area
};

/* class resolving movement */

struct Map
{
	/* how many column boxes */
	float boxesInColumn;

	/* how many row boxes */
	float boxesInRow;

	/* where bot th initial positions of bots for fair play*/
	std::vector<Position> bot_begins;

	/* size of map in pixels */
	Position resolution; 

	/* map skin *///TODO je ho vlastne potreba?
	Skin * skin;

	/* skin worker */
	ImageSkinWork * skinWork;

	/* map is a join of areas */
	Box ** map;
	
	/* check whether actual position is legal */
	void resolveBorders(Object * o);

	/* resolves move actions, chek collision etc.*/
	void resolveMove(Object * o);

public:
	/* constructor defining map resolution in pixels and name of skin*/
	Map(Position resolution, std::string skinName);

	/* check and collision */
	Object * checkCollision(Object * o);

	/* checking for colision and resolving it*/
	void collision(Object * o1, Object * o2);


	/* map finds out the object movement*/
	void move(Object * o); 

	/* events in map */
	void performe();

	/* destructor destorying allocated space, no need to be virtual so far */
	~Map();

	/* draws all visible place */
	void redraw(Window * , Position begin_draw_at); //ked ma vykreslit vsetko

	/* add an object to the map, not walls */
	void add(Object * o); 
};
#endif
