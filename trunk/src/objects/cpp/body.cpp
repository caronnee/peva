#include "../h/body.h"
//TODO dopisat movement a pod
Body::Body(Skin * s)
{
	skinWork = new ImageSkinWork(s);
}
bool Body::is_blocking()
{
	return true;
}
int Body::See()
{
	std::cout << "Filling in object see area";
	return 0;
}
Object * Body::Eye(int index)
{
	std::cout << "Getting object from fills";
	return this;
}
int Body::Step(int steps)
{
	std::cout << "Go " << steps << " steps";
	return 0;
}
int Body::Step()
{
	Step(default_steps);
	return 0;
}
int Body::Turn(int angle)
{
	skinWork->turn(angle);
	return 0;
}
int Body::TurnL()
{
	std::cout << "Turning left";
	skinWork->turn(90);
	return 0;
}
int Body::TurnR()
{
	std::cout << "Turning reight";
	skinWork->turn(-90);
	return 0;
}
int Body::Wait(int x)
{
	std::cout << "Waiting " << x << "times" ;
	return 0;
}
int Body::Shoot(int x, int y)
{
	std::cout << "Shooting at direction [ " << x << "," <<y<<"]" ;
	return 0;
}
