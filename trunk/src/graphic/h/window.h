#ifndef __WINDOW__
#define __WINDOW__

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "graphic.h"
#include "menu.h"
#include "../../language/h/instructions.h"

#define NUMBEROFMENUS 3
#define NUMCHARS 11
#define SECTIONS 2

struct Setting
{
	/* how low should simulation go */
	size_t delay;

	/* penalization for instructions, as were set last time when 
	 * program succesfully finished or recently changed */
	std::vector<int> penalizes;

	/* type of scheduller and addition flags */
	int scheduller;

	/* maps that should be performed, as were set last time when 
	 * program succesfuly finished, or recently changed */
	std::vector<std::string> maps;

	/* robots program inputs */
	std::vector<std::string> inputs;

	/* division of section, as were set last tim e succesfully */
	GamePoints gamePoints;

	/* constructor check existence of last.data file and tries to load it */
	Setting();

	/* destructor saves data to last.data, effectively destroying any changes made prebiously */
	~Setting();
};

class Window 
{
private:
	/* default surface background for menu */
	SDL_Surface * background; //background pre hlavne okno 

	/* menu first created */
	Menu * main_menu;

	/* menus invoked */
	std::stack<Menu *> state;

public:
	/* class doing graphical operation with this window */
	Graphic * g;

	/* constructor, sets grapic that should be used and load settings */
	Window(Graphic * g_);

	/* last succesfully set settings */
	Setting * settings;

	/* draw while place with default tapesry */
	void tapestry(SDL_Rect rect);

	/* resize last active menu */
	void resize();

	//FIXME not used
	int toggle_screen(); //change from full screen to window screen and vice-versa

	/* adds menu to stack */
	void add(Menu * m);

	/* inits graphic and windows */
	bool Init(int argc, char * argv[]);

	/* destroys graphic and window */
	void Destroy();

	/* returns last menu on stack */
	Menu * top()const;

	/* returns true if no menu is on stack */
	bool empty();

	/* removes last menu on stack and calls its cleaing method */
	void pop();	

	/* blits default background */
	void set_background(std::string res);

	/* destructor */
	~Window();
};
#endif
