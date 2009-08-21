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

SDL_Surface * Object::show()
{
	return image; 
}

Missille::Missille(Position P, Position dir)
{
	direction = dir;
	position_in_map = P;
	hlp = 100;
	milisec = 0;
	ticks = SDL_GetTicks();
	name = "Misille";
	image = IMG_Load("../images/Missille.png");
}
bool Missille::is_blocking()
{
	return false;
}
void Missille::damage(Object * sender)
{
	Position p = sender->position_in_map;
	this->hitpoints -= sender->attack;
}
void Missille::defense() //zkladne sa a odide, odkial prisla
{
	direction.x *=-1;
	direction.y *=-1;
}

void Object::action() {}

void Missille::action()
{
	old_pos = position_in_map;
	milisec = SDL_GetTicks() - ticks;
	ticks = SDL_GetTicks(); //ticks je last_time
	if (milisec == 0)
		milisec = 1;
	fps = 1000.0f / milisec;
	if(fps == 0)
		fps = 1;
/*	std::cout << "fps:" << fps <<std::endl;
	std::cout << "pozicia pred:" << position_in_map << std::endl;
	std::cout << "direction:" << direction << std::endl;
	std::cout << "delenie:" <<direction.y<<"/"<<fps<<"="<< direction.y/fps << std::endl;*/
	position_in_map.x += direction.x/fps;
	position_in_map.y += direction.y/fps;
//	std::cout << "pozicia po:" << position_in_map << std::endl;
	ticks = SDL_GetTicks();
}

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
