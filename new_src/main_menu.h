#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "menu.h"
#include "draw.h"

class Main:public Menu
{
	Window * w;
	Menu * menus[NUMBEROFMENUS]; 
public:
	Main(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Main()throw();
};
#endif
