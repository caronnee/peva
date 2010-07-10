#include <iostream>
#include "../h/wall.h"

Wall::Wall(Skin * s, List * abyss):Object(s,abyss)
{
	name = "Wall";
	objectSaveId = SaveWall;
	type = Wall_;
	attack = 10;
	movement.angle = 0;
	movement.direction = Position (0,0);
	movement.position_in_map.x = 0;
	movement.position_in_map.y = 0;
	movement.steps = 0;
}
void Wall::hit(Object * o)
{
	throw "No way! How a static wall can hit something!";
}
void Wall::hitted(Object * attacker, Position p, int attack)
{
//	attacker->bounce(this);
	Object::hitted(attacker,p, attack);
} 

Wall::~Wall() { }

BreakableWall::BreakableWall( Skin * s, List * abyss):Wall(s, abyss)
{
	objectSaveId = SaveBreakableWall;
	type = Wall_;
	hitpoints = 50;
	attack = 0;
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
	movement.speed = 10;
}
void BreakableWall::hitted(Object * o, Position p, int attack)
{
	hitpoints -= attack;
}

BreakableWall::~BreakableWall() { }

PushableWall::PushableWall( Skin * s, List * abyss):Wall(s, abyss)
{
	objectSaveId = SavePushableWall;
	type = Wall_;
	defaultStep = 10;
	attack = 10;
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
void PushableWall::hit(Object * attacked)
{
	attacked->hitted(this,movement.direction,0);
	Object::bounce(attacked);
}
void PushableWall::hitted(Object * o, Position dir, int attack)
{
	movement.steps = o->attack * defaultStep;
	movement.direction += dir;
	movement.direction.x /= 2;
	movement.direction.y /= 2;
}

PushableWall::~PushableWall() { }

TrapWall::TrapWall(Skin * s, List * abyss) : Wall(s, abyss)
{
	objectSaveId = SaveTrapWall;
	type = Wall_;
	defense = 0;
	attack = 10;
	hitpoints = 100;
	invisible = rand()%2;
	name = "TrapWall";	
}
bool TrapWall::is_blocking()
{
	return invisible;
}

//FIXME nesmu sa prekryvat
void TrapWall::hitted(Object *o, Position p, int oAttack)
{
	invisible = rand()%3;
	if (invisible)
		return;
	o->hitted(this, movement.direction, attack);
	hitpoints -= oAttack/2;
}

TrapWall::~TrapWall() {}
