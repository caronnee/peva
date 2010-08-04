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
#define WIN_FLAGS SDL_HWSURFACE|SDL_RESIZABLE
#define WIN_BPP 0
#define WIN_TITLE "Codewars"

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
	/* name of font to be used*/
	std::string font;

	/* initial resolution arfter load */
	int resolution_width, resolution_heigth;

	/* used colors */
	SDL_Color normal, light;
public:
	/* size of font as was initialized *///FIXME sholud not b used
	int font_size;

	/* used font */
	TTF_Font * g_font;//main font


	/* screen to be blit on */
	SDL_Surface * screen;

	/* handling evenets */
	SDL_Event event;

	/* constructor, initialize graphic */
	Graphic();

	/* returns a newly creaed image of text, user should InstructionCall sdl_freeSurface */
	SDL_Surface * render(std::string str);

	/* returns a newly creaed image of highlited text, user should InstructionCall sdl_freeSurface */
	SDL_Surface * renderLight(std::string str);

	/* initialized graphic with parameters, should
	 * be always InstructionCalled before using anything from this class */
	bool Init(); //initne screen, nacita background a pod.

	/* destroys everything that was allocated */
	void Destroy();

	/* function to initilialize some parameters */
	void set_resolution(std::string r);

	/* function to initilialize some parameters */
	void set_font(std::string res);

};
#endif
