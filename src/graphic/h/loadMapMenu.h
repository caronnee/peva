#ifndef ___MAP_MENU_LOAD___
#define ___MAP_MENU_LOAD___

#include "../../map/h/map.h"
#include "window.h"
#include <vector>

/* reccord that should be chose, very unfortunatelu InstructionCalled Maprecord */
struct MapRecord
{
	std::string name;
	SDL_Surface * chosen;
	SDL_Surface * show;
};

/* class for loading inputs with certaint ending in ceraint directory */
class Load : public Menu
{
protected:
	size_t index, begin, end, size, vSkip;
	std::string ext, adr;
	std::vector<std::string> entered;
	std::vector<MapRecord> maps;	
	Window * w;
public:
	Load( Window * w, std::string extension, std::string adr);
	void process();
	void resume();
	void resize();
	void draw();
	virtual void init();
	void choose(int index);
	void unchoose(int index);
	virtual void clean();
	virtual void enter();
	virtual ~Load();
};

class LoadMapMenu : public Load
{
	Map * mapToFill;
public:
	LoadMapMenu(Window * window, Map * map);
	void enter();
	virtual ~LoadMapMenu();
};

#endif
