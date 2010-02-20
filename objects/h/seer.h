#ifndef ___SEER____
#define ___SEER____

#include <iostream>
#include <vector>
#include "../../add-ons/h/position.h"

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
	Seer(Position eyeDimension);
	void set_masks();
	void see(Map * m);
	std::vector<Object *> objects;
	void output();
};

#endif
