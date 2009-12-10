#ifndef ___SEER____
#define ___SEER____

#include <iostream>
#include <vector>
#include "../../add-ons/h/position.h"
#include "../../map/h/map.h"

struct Mask
{
	uint32_t ID;
	uint32_t mask;
	Object * object;
	Object * object_l;
};
class Seer
{
	public:
	enum Direction
	{
		UP,
		LEFT,
		RIGTH,
		DOWN
	};
	std::vector<Position> positions;
	Position resolution;
	Mask ** masks;
	Seer(Position p);
	void set_masks();
	void see(Direction d, Map * m, Position pos);
	std::vector<Object *> objects;
	void output();
};

#endif