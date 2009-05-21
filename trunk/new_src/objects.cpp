#include "objects.h"

Object::Object()
{
	ticks = 100; //blablalb, TODO
}
SDL_Surface * Object::show()
{
	return image; //read-only premenna
}
