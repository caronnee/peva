#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include <list>
#include "graphic.h"
#include "position.h"
#include "objects.h"

class Box
{
	Rectangle bounds;
	public:
	Box(Rectangle rect);
	Position box_resolution;
	std::list<Object *> objects; //objects in area
};

class Map
{
public:
	Box *** map;
	ImageTile m;
	SDL_Rect** rects;
	Position resolution; //velkost mapy v pixeloch
	Position tiles; //kolko policok sa zmesti
	std::vector<Position> bot_begins;
	//Position begin_draw_at;	
	void collision(Object * o1, Object * o2);
	Map(Position resolution);
	void move(ObjectMovement& m, Object * o); //ak sa chce object pohnut, vracia ako moc sa to pokazilo
	~Map();
	void redraw(Window * , Position begin_draw_at); //ked ma vykreslit vsetko
	void update(Window *, Position);
	void add(Object * o); //object si uz drzi informacie o svojej pozicii, je private a
//	void update(SDL_Rect rec);
//	void move(Position p, Position p2);
};


#endif
