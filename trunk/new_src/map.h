#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include "position.h"
#include "wall.h"
#include "robot.h"
#include "draw.h"

class Map
{
public:
	Object *** map;
	ImageTile m;
	SDL_Rect** rects;
	Position resolution; //kolko policok sa zmesti do mapy
	std::vector<Position> bot_begins;
	Position begin_draw_at;	
//	void collision(Object * o1; Object * o2);
	int begin_x, begin_y; //odkial sa ma vykreslovat
	Map(Position resolution);
//	int move(Object * o); //ak sa chce object pohnut, vracia ako moc sa to pokazilo
	~Map();
	void redraw(Window * w); //ked ma vykreslit vsetko
//	void update(SDL_Rect rec);
//	int process();
//	void generate_positions();
};


#endif
