#include <iostream>
#include "../h/wall.h"

Wall::Wall(Skin * s, List * abyss):Object(s)
{
	abyss_ = abyss;
	name = "Wall";
	objectSaveId = SaveWall;
	type = Wall_;
	movement.angle = 0;
	movement.direction = Position (0,0);
	movement.position_in_map.x = 0;
	movement.position_in_map.y = 0;
	movement.steps = 0;
}
void Wall::hit(Object * o)
{
	Object::hit(o);
}
void Wall::hitted(Object * attacker, Position p, int attack)
{
	attacker->bounce(this);
	Object::hitted(attacker,p, attack);
} 
void Wall::dead()
{
	abyss_->push_back(this);
}

Wall::~Wall() { }

BreakableWall::BreakableWall( Skin * s, List * abyss):Wall(s, abyss)
{
	objectSaveId = SaveBreakableWall;
	type = Wall_;
	hitpoints = 50;
	attack_ = 0;
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
void BreakableWall::hit(Object * o)
{
	//nemalo by nic hitovat, teda zatial nic
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
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
void PushableWall::hit(Object * attacked)
{
	attacked->hitted(this,movement.direction,0);
	Rectangle r1 = collisionSize();
	r1.x += movement.position_in_map.x;
	r1.y += movement.position_in_map.y;

	Rectangle r2 = attacked->collisionSize();
	r2.x += attacked->movement.position_in_map.x;
	r2.y += attacked->movement.position_in_map.y;

	//zisti nablizsiu poziciu, kde nekolidoval a tam sa nastav
	Position xy,p;
	intersection(attacked, p, xy);
	int minum =(xy.y < xy.x)? xy.y:xy.x;
	if ((xy.y == minum)&&(xy.y != MY_INFINITY))
		movement.position_in_map.y += xy.y * p.y;
	if ((xy.x=minum)&&(xy.x != MY_INFINITY))
		movement.position_in_map.x += xy.x * p.x;
}
void PushableWall::hitted(Object * o, Position dir, int attack)
{
	movement.steps = attack*defaultStep;
}

PushableWall::~PushableWall() { }

TrapWall::TrapWall(Skin * s, List * abyss):Wall(s, abyss)
{
	objectSaveId = SaveTrapWall;
	type = Wall_;
	defense = 0;
	attack_ = 10;
	hitpoints = 100;
	invisible = random()%2;
	name = "TrapWall";	
}
bool TrapWall::is_blocking()
{
	return invisible;
}
void TrapWall::hit(Object * o)
{
	//Nemoze nic hittovat, takze tu zatial nic nie je
}

//FIXME nesmu sa prekryvat
void TrapWall::hitted(Object *o, Position p, int oAttack)
{
	invisible = random()%3;
	if (invisible)
		return;
	o->hitted(this, movement.direction, attack_);
	hitpoints -= oAttack/2;
}

TrapWall::~TrapWall() {}
