#include "../h/body.h"

Body::Body()
{
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
}

void Body::addAmmo(Object * o)
{
	ammo.add(o);
	o->owner = this;
}

bool Body::is_blocking()
{
	return true;
}
int Body::see()
{
	std::cout << "Filling in object see area";
	return 0;
}
Object * Body::eye(int index)
{
	std::cout << "Getting object from fills";
	return this;
}
void Body::place (Map * m, Position p, int angle)
{
	Object::setPosition(p, angle);
	map = m;
}
int Body::step(int steps)
{
	//TODO presunut to do movmentu
	movement.steps = steps * movement.speed;
	skinWork->switch_state(ImageSkinWork::StatePermanent, ActionHit);
	return 0;
}
int Body::step()
{
	step(default_steps);
	return 0;
}
int Body::turnL()
{
	turn(90);
	return 0;
}
int Body::turnR()
{
	std::cout << "Turning right";
	turn(-90);
	return 0;
}
int Body::wait(int x)
{
	std::cout << "Waiting " << x << "times" ;
	return 0;
}
int Body::shoot(int x, int y)
{
	std::cout << "Shooting at direction [ " << x << "," <<y<<"]" ;
	if (ammo.empty())
	{
		std::cout << "Prazdne ammo!";
		getc(stdin);
		return 0;
	}
	skinWork->switch_state(ImageSkinWork::StateTemporarily, ActionAttack);
	Position mP = this->get_pos();
	
	Position p = skinWork->head();
	if (ammo.data->value == NULL)
		ammo.next();
	mP.x += p.x;
	mP.y += p.y;

	ammo.data->value->movement.steps = 100;
	ammo.data->value->movement.direction = movement.direction;
	ammo.data->value->movement.speed = 50;
	ammo.data->value->movement.position_in_map = mP;
	ammo.moveHead(map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects);

	std::cout << "done!"<< ammo.size();
//	getc(stdin);
	return 0;
}
