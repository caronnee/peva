#ifndef ___MAP_MENU_LOAD___
#define ___MAP_MENU_LOAD___

#include "../../map/h/map.h"
#include "graphic.h"
#include <vector>

struct MapRecord
{
	SDL_Surface * chosen;
	SDL_Surface * show;
	std::string name;
};
class LoadMapMenu : public Menu
{
	Map * mapToFill;
	size_t index, begin, end, size, vSkip;
	std::vector<MapRecord> maps;	
public:
	LoadMapMenu(Window * window, Map * map);
	Window * w;
	void process();
	void draw();
	void init();
	void choose(int index);
	void unchoose(int index);
	void clean();
	virtual ~LoadMapMenu();
};

#endif
