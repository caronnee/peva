#include "objects.h"

Object::Object()
{
	ticks = 100; // TODO
	name =" Object";
}

bool Object::is_blocking()
{
	return false;
}

Position Object::get_pos() const
{
	return movement.position_in_map;
}

SDL_Surface * Object::show()
{
	return image; 
}

void Object::action(Map * m) {}

int Object::IsMoving(){
	return 0;
}
int Object::IsWall()
{
	return 0;
}
int Object::IsPlayer()
{
	return 0;
}
int Object::IsMissille()
{
	return 0;
}
int Object::Locate() //TODO bude vraciac position
{
	return 0;
}
int Object::Hit()
{
	return 0;
}
