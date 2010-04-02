#ifndef __WINDOW__
#define __WINDOW__

#include <iostream>
#include <stack>
#include <string>
#include "graphic.h"
#include "menu.h"

#define NUMBEROFMENUS 5
#define NUMCHARS 11

class Window 
{
private:
	SDL_Surface * background; //background pre hlavne okno 
	Menu * main_menu;
	std::stack<Menu *> state;
	std::string hlp;
	std::string back;
public:
	Graphic * g;
	Window(Graphic * g_);
	void tapestry(SDL_Rect rect);
	int toggle_screen(); //change from full screen to window screen and vice-versa
	void add(Menu * m);
	bool Init(int argc, char * argv[]);
	void Destroy();
	Menu * top()const;
	void process();
	bool empty();
	void pop();	
	void set_background(std::string res);
};
#endif
