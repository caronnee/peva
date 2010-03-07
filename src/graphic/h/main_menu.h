#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <vector>
#include "menu.h"
#include "graphic.h"

class Main: public Menu
{
	std::vector<std::string> files;
	Window * w;
	Menu * menus[NUMBEROFMENUS]; 
	int iterator;
public:
	Main(Window * w_, int argn, char* args[]);
	void process(void);
	void draw();
	void init();
	void clean();
	virtual ~Main();
};
#endif
