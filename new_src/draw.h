#ifndef __DRAWING__
#define __DRAWING__

#include <iostream>
#include <stack>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "wall.h"
#include "menu.h"

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO
#define WIN_FLAGS SDL_HWSURFACE|SDL_RESIZABLE //TODO! on resizeable
#define WIN_BPP 0
#define WIN_TITLE "Codewars"
#define WIN_MAX_WIDTH 1280
#define WIN_MAX_HEIGHT 1024

#define IMG_WIDTH 50
#define IMG_HEIGHT 50

#define ICON "./images/icon.png"

//defaults:
#define DEFAULT_WIN_WIDTH 600
#define DEFAULT_WIN_HEIGTH 480
#define DEFAULT_FONT "../fonts/sfd/DejaVuSansCondensed.ttf"
#define DEFAULT_FONT_SIZE 16
#define DEFAULT_BACKGROUND "../images/background.png"
#define DEFAULT_TIMEOUT 100

#define NUMBEROFMENUS 5
#define NUMCHARS 11
class Graphic
{
	std::string font;
	int resolution_width, resolution_heigth;
public:
	int font_size;
	TTF_Font * g_font;//main font
	SDL_Color normal, light;//TODO read_only
	SDL_Surface * g_screen; //TODO pridat funkciu get_screen
	SDL_Event event;

	Graphic();
	bool Init(); //initne g_screen, nacita background a pod.
	void Destroy();

	void set_resolution(std::string r);
	void set_font(std::string res);
	void set_font_size(std::string res);
};
//-------------------- Draw variables-----------

class Window
{
	unsigned int timeout;
//	Board gameboard;
	Menu * main_menu;
	std::string back;
public:
	Graphic * g;
	SDL_Surface * background; //background pre hlavne okno 
	Window(Graphic * g_);
	void tapestry();
	int Toggle_screen(); //change from full screen to window screen and vice-versa
	void add(Menu * m);
	bool Init();
	void Destroy();
	void set_timeout(std::string res);
	void set_background(std::string res);
	std::stack<Menu *> state;
};
#endif