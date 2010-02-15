#include <iostream>
#include "../h/wall.h"

Wall::Wall(Skin * s):Object(s)
{
	name = "Wall";
	movement.angle = 0;
	movement.direction = Position (0,0);
	movement.position_in_map.x = 0;
	movement.position_in_map.y = 0;
	movement.steps = 0;
	skinWork =  new ImageSkinWork(s);
}
BreakableWall::BreakableWall( Skin * s):Object(s)
{
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
PushableWall::PushableWall( Skin * s):Object(s)
{
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
TrapWall::TrapWall(Skin * s):Object(s)
{
	name = "TrapWall";	
}

