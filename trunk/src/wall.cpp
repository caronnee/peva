#include "wall.h"
#include <iostream>

Tile::Tile(){

}
ImageTile::ImageTile()
{
	tiles = new SDL_Surface*[NumberOfWalls_];
	tiles[FreeTile] = IMG_Load("../images/FreeTile.png");
	tiles[SolidWall_] = IMG_Load("../images/SolidWall.png");
	tiles[PushableWall_] = IMG_Load("../images/PushableWall.png");
	tiles[TrapWall_] = IMG_Load("../images/TrapWall.png");
}
SDL_Surface * ImageTile::get_image(WallType t)
{
	return tiles[t];
}
Tile::Tile(ImageTile * t) 
{
	image = t->get_image(FreeTile); 
} 
bool Tile::is_blocking()
{
	return true;
}

SolidWall::SolidWall(ImageTile * t)
{
	name = "SolidWall";
	image = t->get_image(SolidWall_);
	if (image == NULL) //crash!
	{
		std::cerr << "Image of solid wall not found!)";
	}
}
PushableWall::PushableWall(ImageTile * t)
{
	name = "PushableWall";
	image = t->get_image(TrapWall_);
	if (image == NULL) //crash!o
	{
		std::cerr << "Image of pushable wall not found!)";
	}
	movement.direction.x = 0;
	movement.direction.y = 0;
	ticks = SDL_GetTicks() + 100;
}
void PushableWall::action(Map * m)
{

}
TrapWall::TrapWall(ImageTile * t)
{
	name = "TrapWall";
	image = t->get_image(TrapWall_);
	if (image == NULL) //crash!o
	{
		std::cerr << "Image of trap wall not found!)";
	}
}

