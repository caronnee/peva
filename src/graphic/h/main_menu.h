#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <vector>
#include "menu.h"
#include "window.h"

/* default class for defining crossmenu */
class Main: public Menu
{
	std::vector<std::string> files;
protected:
	Window * w;
	int iterator;
	Menu ** menus; 
	int size;

public:
	Main(Window * w_, int argn, char* args[]);
	virtual void init();
	virtual void resume();
	void resize();
	void process();
	void draw();
	void clean();
	virtual ~Main();
};
/* menu for showing a string on screen */
class ShowMenu : public Menu
{
	Window * w;
	std::string strToshow;
	size_t iter;
	size_t size;
	std::vector<SDL_Surface *> images;
public:

	ShowMenu(Window * w, std::string str);
	void init();
	void process();
	void resume();
	void draw();
	void clean();
	void resize();
	virtual ~ShowMenu();
};
#endif
