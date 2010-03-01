#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "menu.h"
#include "graphic.h"

class Main: public Menu
{
	Window * w;
	Menu * menus[NUMBEROFMENUS]; 
	int iterator;
public:
	Main(Window * w_);
	void process(void);
	void draw();
	void init();
	void clean();
	virtual ~Main();
};
#endif
