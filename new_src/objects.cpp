#include "objects.h"

Object::Object()
{
	ticks = 100; //blablalb, TODO
	name =" Object";
}

bool Object::is_blocking()
{
	return false;
}

SDL_Surface * Object::show()
{
	return image; //read-only premenna
}

Missille::Missille()
{
	name = "Misille";
}
bool Missille::is_blocking()
{
	return false;
}
