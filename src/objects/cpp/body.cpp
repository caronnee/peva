#include "../h/body.h"

Body::Body()
{
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
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
	return 0;
}
