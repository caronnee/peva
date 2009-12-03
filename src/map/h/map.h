#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include <list>
#include "../../graphic/h/graphic.h"
#include "../../add-ons/h/position.h"
#include "../../objects/h/objects.h"

struct Box
{
	Box();
	Rectangle bounds;
	Position box_resolution;
	std::list<Object *> objects; //objects in area
};

class Map
{
//	std::vector<Robot *> robots;
public:
	Skin * skin;
	Box ** map;
	SDL_Rect** rects;
	Skin * mapSkin;
	Position resolution; //velkost mapy v pixeloch
	Position tiles; //kolko policok sa zmesti
	std::vector<Position> bot_begins;
	//Position begin_draw_at;	
	void collision(Object * o1, Object * o2);
	Map(Position resolution, std::string name);
	void move(ObjectMovement& m, Object * o); //ak sa chce object pohnut, vracia ako moc sa to pokazilo
	~Map();
	void redraw(Window * , Position begin_draw_at); //ked ma vykreslit vsetko
	void update(Window *, Position);
	void add(Object * o); 
//	bool checkCollision(Object * def, Object * att);
//	void update(SDL_Rect rec);
//	void move(Position p, Position p2);
};


#endif
