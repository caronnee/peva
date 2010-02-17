#include "../h/missille.h"

Missille::Missille(Skin*s, Body * body):Object(s)
{
	substance = Miss;
	owner = body;
	movement.position_in_map = Position (0,0);
	movement.speed = 100;
	milisec = 0;
	name = "Missille";
//	skinWork = new ImageSkinWork(s);
}
Missille::Missille(Position P, Position dir, Skin* s):Object(s)
{
	substance = Miss;
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
