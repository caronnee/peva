#include "../h/missille.h"

Missille::Missille(Skin*s, Body * body)
{
	owner = body;
	movement.position_in_map = Position (0,0);
	movement.speed = 100;
	milisec = 0;
	name = "Missille";
	skinWork = new ImageSkinWork(s);
}
Missille::Missille(Position P, Position dir, Skin* s)
{
	owner = NULL;
	movement.direction = dir;
	movement.position_in_map = P;
	movement.old_pos = P;
	milisec = 0;
	movement.angle = 50;
	movement.steps = 0;
	movement.speed = 100;
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

void Missille::stoppedMoving()
{
	std::cout << "MYbegin!"<<owner;
	getc(stdin);
	std::cout << " " << owner->ammo.data  << ":";
	owner->addAmmo(item);
	std::cout << " " << owner->ammo.size()  << std::endl;
	std::cout << "MYenda!";
	getc(stdin);
}
//TODO zmazat a dat do ineho listu, kde nebude action
void Missille::action()
{
	hitpoints = movement.steps;
}
	/*
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
}*/
Missille::~Missille() 
{} 
