#include "../h/missille.h"

Missille::Missille(Position P, Position dir, Skin* s)
{
	movement.direction = dir;
	movement.position_in_map = P;
	movement.old_pos = P;
	milisec = 0;
	ticks = SDL_GetTicks();
	name = "Missille";
	skinWork = new ImageSkinWork(s);
}
bool Missille::is_blocking()
{
	return false;
}
void Missille::damage(Object * sender)
{
//	Position p = sender->position_in_map;
	this->hitpoints -= sender->attack;
}
void Missille::defense() //zkladne sa a odide, odkial prisla
{
	movement.direction.x *=-1;
	movement.direction.y *=-1; //TODO to sa vrati odkial prisla
}

void Missille::action(Map * m)
{
	movement.old_pos = movement.position_in_map;
	milisec = SDL_GetTicks() - ticks;
	if (milisec == 0)
		milisec = 1;
	fps = 1000.0f / milisec;
//	std::cout << "fps" << fps <<std::endl;
	if(fps == 0)
		fps = 1;
	fps = 30; //TODO napevno dana fps!
//	std::cout << "pozicia pred:" << movement.position_in_map << std::endl;
	movement.position_in_map.x += movement.direction.x/fps;
	movement.position_in_map.y += movement.direction.y/fps;
//	std::cout << "pozicia po:" << movement.position_in_map << std::endl;
//	getc(stdin);
	ticks = SDL_GetTicks();
	m->move(movement, this);
}
Missille::~Missille() {} //zatial nic specialne nerobi
