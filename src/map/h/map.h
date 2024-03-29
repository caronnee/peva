#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include <list>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../../graphic/h/graphic.h"
#include "../../add-ons/h/position.h"
#include "../../objects/h/objects.h"
#include "../../language/h/targets.h"

/* width of box in pixels */
#define BOX_WIDTH 400

/* height of box in pixels */
#define BOX_HEIGHT 400


/* structure for objects in area */
struct Box
{
	/* Contructor */
	Box();

	/* Bounds of  area*/
	Rectangle bounds; 

	/* Objects in area */
	std::list<Object *> objects[2]; 
};

/* class resolving movement */
struct Place
{
	/* id of group how sholud be saved */
	ObjectsToSave saveId;

	/* unique id for searching */
	int id;

	/* integer indentifier of appropriate type */
	size_t numberImage;

	/* generated image */
	SDL_Surface * img;

	/* position of place */
	Rectangle r;
};

class Map
{

	/* initialization common to all constructors */
	void commonInit(std::string name);

	/* where dead object go */
	std::list< Object *> abyss;

	/* help fnction to determnije nearest object */
	void checkNearest(Object * center, Object *objectToCheck, 
		size_t& distanceSoFar, Object * &nearestObjectSoFar );

	/* structure holdin images of wall */
	std::vector<WallSkin *> wskins;

	/* draws background*/
	void background(Graphic * g);

	/* adding special place to map */
	void addPlace(Graphic* w, Place p);

	/* size of map in pixels */
	Position resolution; 

	/* map finds out the object movement*/
	void move(Object * o); 

public:
	/* map is a join of areas */
	Box ** map;
	
	/* returns map resolution */
	Position getResolution()const;

	/* significant places*/
	std::list<Place> places; //starts and targets

	/* relative time, accordig to it it is map drawed */
	size_t ticks;

	/* iterator describing position 
	 * where are the object already 
	 * processed */
	int processing;

	/* last time the screen was updated */
	size_t time;

	/* return maximum bonding rectangl, for drawing purposes */
	SDL_Rect getBoundingRect(Object * o);

	/* creates map according to resolution */
	void create();

	/* map visibility */
	int visibility;

	/* returns start positions */
	std::list<Rectangle> getStarts();

	/* draws only visible objects*/
	void draw(Graphic *w);

	/* draw map including non-participating objects */
	void drawAll(Graphic * w);

	/* removes object at position p and udate the screen */
	Object * removeShow(Position position, bool all, Graphic*w);

	/* removes object at position p*/
	Object * removeAt(Position position, SDL_Rect & r);

	/* loads map from file */
	bool load(Graphic * w, std::string filename);

	/* save map to file */
	bool saveToFile(std::string filename);

	/* adding target places */
	void addTarget(Graphic* w, size_t x, size_t y);

	/* adding target places */
	void addStart(Graphic* w, size_t x, size_t y);

	/* adds boundary walls */
	void addBoundaryWalls();

	/* removes boundary walls */
	void removeBoundaryWalls();

	/* how many row boxes */
	float boxesInRow;

	/* how many column boxes */
	float boxesInColumn;

	void update(SDL_Rect rect, bool all , Graphic * w);

	/* updates area around one object */
	void update(Object * o, Graphic * w);

	/* check whether actual position is legal, should not be used in realeade */
	void resolveBorders(Object * o);

	/* resolves move actions, check collision etc.*/
	void resolveMove(Object * o);
	
	/* drawing boundaries, rectangel, where its safe to draw */
	Rectangle boundaries;

	/* constructor defining map resolution in pixels and name of skin*/
	Map(Position resolution, std::string skinName);

	/* shifts boundaries to be blit */
	void shift(int shiftLeft, int shiftUp);

	/* creates empty map */
	Map(std::string skinName);

	/* sets absolute shift */
	void setShift(int x, int y);

	/* check and collision */
	Object * checkCollision(Object * o);

	//TODO dat do rectangle
	bool collideWith(Object * o1, Object * o2);

	/* checking for colision and resolving it*/
	void collision(Object * o1, Object * o2);

	/* events in map */
	bool performe(Graphic * g);

	/* destructor destroying allocated space, no need to be virtual so far */
	~Map();

	/* updates all object in area */
	void updateScreen(Graphic * g);

	/* removes from map an object, but do not destroys it */
	void remove(Object * o);

	/* removes all object from map and destroys them*/
	void clean();

	/* sets beoundaries of map according to size of solid wall*/	
	Position setBoundary(int w, int h);

	/* draws all visible place */
	void redraw(Graphic * window); //ked ma vykreslit vsetko

	/* add an object to the map */
	void add(Object * o); 

};
#endif
