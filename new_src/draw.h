#include <iostream>
#include <stack>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

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
#define DEFAULT_WIN_WIDTH 500
#define DEFAULT_WIN_HEIGTH 480
#define DEFAULT_FONT "./fonts/sfd/DejaVuSansCondensed.ttf"
#define DEFAULT_FONT_SIZE 12
#define DEFAULT_BACKGROUND "../images/background.png"
#define DEFAULT_TIMEOUT 100

class Window;
//-------------------- Draw variables-----------
enum Menus
{
	SETTINGS,
	CREATE_MAP,
	PLAY,
	JOIN,
	HOST,
	GAME_EXIT
};

class Menu
{
	public:
		int iterator;//kolko sme toho naalokovali
		std::string name;
		Window * w;
		std::string get_name();
		virtual void process(void) = 0;
		virtual void draw()=0; //skuska dedicnosti! par potomkov bude pouzit stejnu fciu ako Menu
};
class Main:public Menu
{
	Menu * menus[4]; 
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

/*class Map: public Menu //vytvaranie mapy
{
	int creation;//ci bolo zadane resolution alebo nie;
public:
	Map(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Map()throw();
};*/

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
	unsigned int convert(std::string);
	void set_resolution(std::string res);
	void set_timeout(std::string res);
	void set_font(std::string res);
	void set_font_size(std::string res);
	void set_background(std::string res);
	std::stack<Menu *> state;
};
