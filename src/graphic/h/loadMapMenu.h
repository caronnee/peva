#ifndef ___MAP_MENU_LOAD___
#define ___MAP_MENU_LOAD___

#include "../../map/h/map.h"
#include "graphic.h"

class LoadMapMenu : public Menu
{
	Map * mapToFill;
public:
	std::string path;
	LoadMapMenu(Window * window, Map * map);
	Window * w;
	void process();
	void draw();
	void init();
	void clean();
};

#endif
