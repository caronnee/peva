#include "objects.h"

Object::Object()
{
	ticks = 100; //blablalb, TODO
}

bool Object::is_blocking()
{
	return false;
}

SDL_Surface * Object::show()
{
	return image; //read-only premenna
}
