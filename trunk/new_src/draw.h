#include <iostream>
#include <stack>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "wall.h"

//send a messages during a game?In play method

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
#define DEFAULT_FONT "./fonts/sfd/DejaVuSansCondensed.ttf"
#define DEFAULT_FONT_SIZE 16
#define DEFAULT_BACKGROUND "../images/background.png"
#define DEFAULT_TIMEOUT 100

#define NUMBEROFMENUS 5
#define NUMCHARS 11
class Window;
//-------------------- Draw variables-----------

unsigned int convert(std::string); //TODO do help functions

class Menu
{
	public:
		int iterator;//kolko sme toho naalokovali
		std::string name;
		Window * w;
		std::string get_name();
		void tapestry();
		virtual void process(void) = 0;
		virtual void draw()=0; //skuska dedicnosti! par potomkov bude pouzit stejnu fciu ako Menu
};
class Main:public Menu
{
	Menu * menus[NUMBEROFMENUS]; 
public:
	Main(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Main()throw();
}; //----------
class Settings:public Menu
{
	std::string names[3]; //nastavit timeouti, resolution, background. TODO!
public:
	Settings(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Settings()throw();
};

class Host:public Menu
{
public:
	Host(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Host()throw();
};
class Join:public Menu
{
public:
	Join(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Join()throw();
};
class Play:public Menu
{
public:
	Play(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Play()throw();
};
class Create_map:public Menu
{
	bool set,x; //x = oddelovac u resolution
	bool mouse_down; //bola vybrana/ uklada sa tile

	int begin_x, begin_y;
	int window_begin_x, window_begin_y; //centrovanie do stredu

	SDL_Surface * text;
	SDL_Surface * selected;
	int text_width;
	int selected_x, selected_y;

	Tile * tiles[NumberOfWalls_];
	unsigned int ** map; //maximalne 32 druhov stien, na mape prave 1object, take to nevadi
	SDL_Surface * resol[NUMCHARS]; //0-9+x
	int resol_width[NUMCHARS];
	int resolX,resolY, number_written; //max 5x5 cifier?
	std::string written_x, written_y;
	void process_map();
	void process_resolution();
	void draw_resol();
	void reset();
public:
	Create_map(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Create_map()throw();
};

class Window
{
	std::string font;
	unsigned int timeout;
	int resolution_width, resolution_heigth;
	// pomocne funkcie
//	Board gameboard;
	void set_resolution();
	void play();
	void join();
	void host();
	Main* main_menu;
public:
	int font_size;
	SDL_Surface * background; //background pre hlavne okno 
	TTF_Font * g_font;//main font
	SDL_Event event;
	Window();
	bool Init(); //initne g_screen, nacita background a pod.
	int Toggle_screen(); //change from full screen to window screen and vice-versa
	void Destroy();
	void Init_default();
	void set_resolution(std::string res);
	void set_timeout(std::string res);
	void set_font(std::string res);
	void set_font_size(std::string res);
	void set_background(std::string res);
	SDL_Color normal, light;
	std::stack<Menu *> state;
};
