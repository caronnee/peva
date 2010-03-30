#include "../h/loadMapMenu.h"

LoadMapMenu::LoadMapMenu(Window * window, Map * map)
{
	path = ".";
	map->clean();
	w = window;
}
void LoadMapMenu::process()
{
}
void LoadMapMenu::draw()
{
}
void LoadMapMenu::init()
{
	//not necessary
}
void LoadMapMenu:: clean()
{
	//nothing
}
