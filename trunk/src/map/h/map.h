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
#include "../../objects/h/list.h"
#include "../../language/h/targets.h"

//width of box in pixels
#define BOX_WIDTH 400
//height of box in pixels
#define BOX_HEIGHT 400


/* structure for objects in area */

struct Box
{
	/* Contructor */
	Box();

	/* Bounds of  area*/
	Rectangle bounds; 

	/* Objects in area */
	List objects; 
};

/* class resolving movement */
struct Place
{
	size_t id;
	size_t numberImage;
	SDL_Surface * img;
	Rectangle r;
};

struct Map
{
	/* structure holdin images of wall */
	std::vector<WallSkin *> wskins;
	std::list<Place> places; //starts and targets

	/* draws background*/
	void background(Window *w);

	/* draws only visible objects*/
	void draw(Window *w);

	Position getChangeableArea();

	/* draw map including non-participating objects */
	void drawAll(Window * w);

	/* removes object at position p and udate the screen */
	Object * removeShow(Position position, bool all, Window*w);

	/* removes object at position p*/
	Object * removeAt(Position position, SDL_Rect & r);

	/* how many column boxes */
	float boxesInColumn;

	/* adding special place to map */
	void addPlace(Window* w, Place p);
	/* adding target places */
	void addTarget(Window* w, size_t x, size_t y);
	void addStart(Window* w, size_t x, size_t y);

	/* how many row boxes */
	float boxesInRow;

	/* where bot th initial positions of bots for fair play*/
	std::vector<Position> bot_begins;

	/* size of map in pixels */
	Position resolution; 

	void update(SDL_Rect rect, bool all , Window * w);
	/* map skin *///TODO je ho vlastne potreba?
	Skin * skin;

	/* skin worker */
	ImageSkinWork * skinWork;

	/* map is a join of areas */
	Box ** map;
	
	/* check whether actual position is legal */
	void resolveBorders(Object * o);

	/* resolves move actions, check collision etc.*/
	void resolveMove(Object * o);
	
	/* drawing boundaries, rectangel, where its safe to draw */
	Rectangle boundaries;
public:
	/* constructor defining map resolution in pixels and name of skin*/
	Map(Position resolution, std::string skinName);

	void shift(int shiftLeft, int shiftUp);

	/* returns size of map */
	Position size()const;

	/* constructor from config file */
	Map(std::string file, std::string skinName);

	/* check and collision */
	Object * checkCollision(Object * o);

	//TODO dat do rectangle
	bool collideWith(Object * o1, Object * o2);

	/* checking for colision and resolving it*/
	void collision(Object * o1, Object * o2);

	/* map finds out the object movement*/
	void move(Object * o); 

	/* events in map */
	bool performe();

	/* destructor destorying allocated space, no need to be virtual so far */
	~Map();

	/* removes from map an object, but do not destroys it */
	void remove(Object * o);

	/* removes all object from map and destroys them*/
	void clean();

	/* sets beoundaries of map according to size of solid wall*/	
	void setBoundary(int w, int h);

	/* draws all visible place */
	void redraw(Window * window); //ked ma vykreslit vsetko

	/* add an object to the map */
	void add(Object * o); 
};
#endif
