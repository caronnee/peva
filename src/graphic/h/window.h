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

struct Setting
{
	std::vector<int> penalizes;
	int scheduller;
	std::vector<std::string> maps;
	std::vector<std::string> inputs;
	GamePoints gamePoints;
	Setting();
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
	Graphic * g;
	Window(Graphic * g_);
	Setting * settings;
	void tapestry(SDL_Rect rect);
	void resize();
	int toggle_screen(); //change from full screen to window screen and vice-versa
	void add(Menu * m);
	bool Init(int argc, char * argv[]);
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
