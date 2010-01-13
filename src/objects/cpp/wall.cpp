#include <iostream>
#include "../h/wall.h"

Wall::Wall()
{
	name = "Wall";
}
Wall::Wall(Position p, WallSkin * s)
{
	name = "Wall";
	movement.angle = 0;
	movement.direction = Position (0,0);
	movement.position_in_map = movement.old_pos = p;
	movement.steps = 0;
	skinWork =  new ImageSkinWork(s);
}
BreakableWall::BreakableWall()
{
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
PushableWall::PushableWall()
{
	name = "Wall";
	movement.direction.x = 0;
	movement.direction.y = 0;
}
TrapWall::TrapWall()
{
	name = "TrapWall";	
}

