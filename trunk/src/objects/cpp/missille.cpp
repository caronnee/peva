#include "../h/missille.h"
#include "../../add-ons/h/macros.h"

Missille::Missille(Skin*s, List * list):Object(s,list)
{
	substance = Miss;
	movement.position_in_map = Position (0,0);
	movement.speed = 100;
	name = "Missille";
}

/*void Missille::bounce(Object * o)
{
	Object::bounce(o);
	//nowhereToRun = false;
}*/

bool Missille::is_blocking()
{
	return false;
}

void Missille::hit(Object * o)
{
	//nowhereToRun = true; //ak sa nezavola bounce, tato hodnota
	o->hitted(this, movement.direction, attack);
	bounce(o);

/*	if (nowhereToRun)
	{
		hitpoints =0;
		movement.steps = 0; //zabili sme, mapa to ostravi a priradi ownerovi
	}*/
}

void Missille::hitted(Object * o, Position d, int attack)
{
	hit(o); //never 
}
void Missille::move(size_t fps)
{
	Object::move(fps);
	hitpoints = movement.steps;
}
Missille::~Missille() 
{} 
