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
	SDL_Surface * render(std::string str);
	SDL_Surface * renderLight(std::string str);
	bool Init(); //initne screen, nacita background a pod.
	void Destroy();

	void set_resolution(std::string r);
	void set_font(std::string res);
	void set_font_size(std::string res);
	void waitKeyDown();
	//TODO take veci ako napriklad vykreslovanie
};
#endif
