#include <iostream>
#include "../h/wall.h"

Tile::Tile(){

}
 
bool Tile::is_blocking()
{
	return true;
}

SolidWall::SolidWall()
{
	name = "SolidWall";
}
PushableWall::PushableWall()
{
	movement.direction.x = 0;
	movement.direction.y = 0;
	ticks = SDL_GetTicks() + 100;
}
void PushableWall::action(Map * m)
{

}
TrapWall::TrapWall()
{
	name = "TrapWall";	
}

