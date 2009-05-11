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
#define DEFAULT_BACKGROUND "./images/background.png"
#define DEFAULT_TIMEOUT 100

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

struct Window_state
{
	void (* process)();
};

class Window
{
	std::string font;
	SDL_Surface * g_screen;
	TTF_Font * g_font;//main font
	int font_size;
	SDL_Surface * background; //background pre hlavne okno 
	SDL_Event event;
	int resolution_width, resolution_heigth;
	// pomocne funkcie
//	Board gameboard;
	void set_resolution();
	void play();
	void join();
	void host();
	void main();
public:
	void Default(); //vytvori defaultnu sirku, dlzku, jazyk a pod.
	bool Init(); //initne g_screen, nacita background a pod.
	int Toggle_screen(); //change from full screen to window screen and vice-versa
	void Destroy();
public:
	void Init_default();
	unsigned int convert(std::string);
	void set_resolution(std::string res);
	void set_timeout(std::string res);
	void set_font(std::string res);
	void set_font_size(std::string res);
	void set_background(std::string res);
	std::stack<Window_state> state;
};
