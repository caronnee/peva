#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include <vector>
#include "menu.h"
#include "window.h"

struct Setting
{
	std::vector<int> penalizes;
	int scheduller;
	std::vector<std::string> maps;
	std::vector<std::string> inputs;
};
class Main: public Menu
{
	std::vector<std::string> files;
protected:
	Setting * settings;
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
#endif
