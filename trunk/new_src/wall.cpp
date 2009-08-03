#include "wall.h"
#include <iostream>

Tile::Tile() 
{
	image = IMG_Load("../images/FreeTile.png");
} 
bool Tile::is_blocking()
{
	return true;
}

SolidWall::SolidWall()
{
	image = IMG_Load("../images/SolidWall.png");//kedze je to iba v konstruktore, mozno si to mozem dovolit
	if (image == NULL) //crash!
	{
		std::cerr << "Image of solid wall not found!)";
	}
}
TrapWall::TrapWall()
{
	image = IMG_Load("../images/TrapWall.png");
	if (image == NULL) //crash!o
	{
		std::cerr << "Image of trap wall not found!)";
	}
}
PushableWall::PushableWall()
{
	image = IMG_Load("../images/PushableWall.png");
	if (image == NULL) //crash!o
	{
		std::cerr << "Image of pushable wall not found!)";
	}
}
ExitWall::ExitWall()
{
	image = IMG_Load("../images/ExitWall.png");
	if (image == NULL) //crash!o
	{
		std::cerr << "Image of exit wall not found!)";
	}
}
