#include "../h/missille.h"

Missille::Missille(Skin*s)
{
	movement.direction = Position (0,0);
	movement.position_in_map = Position (0,0);
	milisec = 0;
	ticks = SDL_GetTicks();
	name = "Missille";
	skinWork = new ImageSkinWork(s);

}
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
//	this->hitpoints -= sender->attack;
}
void Missille::defense() //zkladne sa a odide, odkial prisla
{
	movement.direction.x *=-1;
	movement.direction.y *=-1; //TODO to sa vrati odkial prisla
}

void Missille::action()
{
	movement.old_pos = movement.position_in_map;
	milisec = SDL_GetTicks() - ticks;
	if (milisec == 0)
		milisec = 1;
	movement.fps = 1000.0f / milisec;
//	std::cout << "fps" << fps <<std::endl;
	if(movement.fps == 0)
		movement.fps = 1;
	movement.fps = 30; //TODO napevno dana fps!
//	std::cout << "pozicia pred:" << movement.position_in_map << std::endl;
	movement.position_in_map.x += movement.direction.x/movement.fps;
	movement.position_in_map.y += movement.direction.y/movement.fps;
//	std::cout << "pozicia po:" << movement.position_in_map << std::endl;
//	getc(stdin);
	ticks = SDL_GetTicks();
}
Missille::~Missille() 
{} 
