#ifndef ___SNAKE____
#define ___SNAKE____

#include "movement.h"
#include "../../add-ons/h/position.h"

#define MOVEMENTS 4
#define LAST_VISITED 4

class Snake
{
	void Init();	
	int fatness;
	int health;
	int * visited; //zapamataj si predposledne 4 policka

	Position position;
	Position resolution;
	Position direction;
public:
	Snake(const Snake& a);
	Snake(Position resolution_);

	int max_interval;


	Movement movements[MOVEMENTS]; //zoradenie zmeny oproti resolution		
	bool move();

	int get_x();
	int get_y();
	int get_fat();
	int alive();
	Position get_dir();
	Position get_pos();
};

#endif
