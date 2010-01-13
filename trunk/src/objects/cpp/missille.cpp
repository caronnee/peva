#include "../h/missille.h"

Missille::Missille(Skin*s, Body * body)
{
	substance = 0;
	owner = body;
	movement.position_in_map = Position (0,0);
	movement.speed = 100;
	milisec = 0;
	name = "Missille";
	skinWork = new ImageSkinWork(s);
}
Missille::Missille(Position P, Position dir, Skin* s)
{
	substance = 0;
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

void Missille::dead()
{
	owner->addAmmo(this->item);
}
void Missille::move()
{
	Object::move();
	hitpoints = movement.steps;
}
Missille::~Missille() 
{} 
