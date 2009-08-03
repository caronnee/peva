#ifndef ___MAP____
#define ___MAP____

#include <SDL/SDL.h>
#include <vector>
#include "position.h"
#include "wall.h"
#include "robot.h"

class Scheduller
{

};

class Map
{
public:
	Object *** map;
	Position resolution;
	
//	void collision(Object * o1; Object * o2);
	int begin_x, begin_y; //odkial sa ma vykreslovat
	Map(Position resolution);
//	int move(Object * o); //ak sa chce object pohnut, vracia ako moc sa to pokazilo
//	~Map();
//	void draw();
//	void update(SDL_Rect rec);
//	int process();
//	void generate_positions();
};


#endif
