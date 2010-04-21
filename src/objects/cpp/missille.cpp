#include "../h/missille.h"
#include "../../add-ons/h/macros.h"

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
void Missille::bounce(Object * o)
{
	Object::bounce(o);
	nowhereToRun = false;
}
bool Missille::is_blocking()
{
	return false;
}

void Missille::dead()
{
	owner->addAmmo(this);
}
void Missille::hit(Object * o)
{
	nowhereToRun = true; //ak sa nezavola bounce, tato hodnota
	o->hitted(this, movement.direction, attack_);
	if (nowhereToRun)
	{
		hitpoints =0;
		movement.steps = 0; //zabili sme, mapa to ostravi a priradi ownerovi
	}
}
void Missille::hitted(Object * o, Position d, int attack)
{
	hit(o);
}
void Missille::move()
{
	Object::move();
	hitpoints = movement.steps;
}
Missille::~Missille() 
{} 
