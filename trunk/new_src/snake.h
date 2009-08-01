#ifndef ___SNAKE____
#define ___SNAKE____

#include "movement.h"
#include "position.h"

#define MOVEMENTS 4
#define LAST_VISITED 4

class Snake
{
	void Init();	
	int fatness;
	int health;
public:
	Snake(const Snake& a);
	Snake(Position resolution_);

	int max_interval;

	int * visited; //zapamataj si predposledne 4 policka
	Position resolution;
	Position position;
	Position direction;

	Movement movements[MOVEMENTS]; //zoradenie zmeny oproti resolution		
	bool move();

	int get_x();
	int get_y();
	int get_fat();
	int get_direct_x();
	int get_direct_y();
};

#endif
