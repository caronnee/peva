#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <vector>
#include "menu.h"
#include "window.h"

class Main: public Menu
{
	std::vector<std::string> files;
	Window * w;
	Menu * menus[NUMBEROFMENUS]; 
	int iterator;
public:
	Main(Window * w_, int argn, char* args[]);
	void process();
	void resume();
	void draw();
	void init();
	void clean();
	virtual ~Main();
};
#endif
