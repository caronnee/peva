#include "../h/body.h"

Body::Body()
{
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
}

void Body::addAmmo( Object * o)
{
	ammo.add(o->item);
	o->owner = this;
}
void Body::addAmmo( Item * i)
{
	ammo.add(i); //owner jw spravny
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
int Body::shoot(int angle)
{
	std::cout << "Shooting at angle [ " << angle <<std::endl;
//	getc(stdin);
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

	Object * o= ammo.data->value;
	ammo.data->value->movement.steps = 50;
	ammo.data->value->movement.angle = movement.angle;
	ammo.data->value->hitpoints = 50;
	ammo.data->value->movement.direction = movement.direction;
	std::cout << "PRED:" << ammo.data->value->movement.direction<< " ";
	ammo.data->value->movement.speed = 50;
	ammo.data->value->movement.position_in_map = mP;
	ammo.data->value->movement.realX = 0;
	ammo.data->value->movement.realY = 0;
	o->turn(angle);
	std::cout << "PO:" << ammo.data->value->movement.direction<< " ";
	ammo.moveHead(map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects);
	std::cout << "shooted!"<<mP<< " "<<ammo.size()<<" "<<o->alive();
//	getc(stdin);
	return 0;
}
