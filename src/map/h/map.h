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

/* for all animated object we need to have information */

struct MapData
{
	Object * o;
	Position positionInMap; //or which map  we are in
};

/* class resolving movement */

class Map
{
	/* data about positions of object in map */
	std::list<MapData> activeObjects;	

	/* where bot th initial positions of bots for fair play*/
	std::vector<Position> bot_begins;

	/* size of map in pixels */
	Position resolution; 

	/* map skin */
	Skin * skin;

	/* skin worker */
	ImageSkinWork * skinWork;

	/* map is a join of areas */
	Box ** map;

public:
	/* checking for colision and resolving it*/
	void collision(Object * o1, Object * o2);

	/* constructor defining map resolution in pixels and name of skin*/
	Map(Position resolution, std::string skinName);

	/* map finds out */
	void move(ObjectMovement& m, Object * o); 

	/* destructor destorying alocated space, no need to be virtual so far */
	~Map();

	/* draws all visible place */
	void redraw(Window * , Position begin_draw_at); //ked ma vykreslit vsetko
	/* add an object to the map, not walls */
	void add(Object * o); 
};


#endif
