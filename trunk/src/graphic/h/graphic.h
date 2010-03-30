#ifndef __GRAPHIC__
#define __GRAPHIC__

/*
 * Interface for graphical events
 */

#include <iostream>
#include <stack>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO
#define WIN_FLAGS SDL_HWSURFACE|SDL_RESIZABLE //TODO! on resizeable
#define WIN_BPP 0
#define WIN_TITLE "Codewars"
#define WIN_MAX_WIDTH 1280
#define WIN_MAX_HEIGHT 1024

#define ICON "./images/icon.png"

//defaults:

#define DEFAULT_WIN_WIDTH 600
#define DEFAULT_WIN_HEIGTH 480
#define DEFAULT_FONT "./fonts/sfd/DejaVuSansCondensed.ttf"
#define DEFAULT_FONT_SIZE 16
#define DEFAULT_BACKGROUND "./images/background.png"
#define DEFAULT_TIMEOUT 100

#define NUMBEROFMENUS 5
#define NUMCHARS 11
class Graphic
{
public:
	std::string font;
	int resolution_width, resolution_heigth;
	int font_size;
	TTF_Font * g_font;//main font
	SDL_Color normal, light;//TODO read_only
	SDL_Surface * screen; //TODO pridat funkciu get_screen
	SDL_Event event;

	Graphic();
	bool Init(); //initne screen, nacita background a pod.
	void Destroy();

	void set_resolution(std::string r);
	void set_font(std::string res);
	void set_font_size(std::string res);
	//TODO take veci ako napriklad vykreslovanie
};
//-------------------- Draw variables-----------

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
