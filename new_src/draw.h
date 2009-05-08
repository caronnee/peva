#include <iostream>
#include <string>

//send a messages during a game?In play method

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO
#define WIN_BPP 0
#define WIN_WIDTH 500
#define WIN_HEIGHT 480
#define WIN_TITLE "Codewars"
#define WIN_FLAGS SDL_HWSURFACE|SDL_RESIZABLE
#define WIN_MAX_WIDTH 1280
#define WIN_MAX_HEIGHT 1024

#define IMG_WIDTH 50
#define IMG_HEIGHT 50
//-------------------- Draw variables-----------
SDL_Surface * g_screen;
TTF_Font * g_font;//main font
SDL_Surface * background; //background pre hlavne okno 
SDL_Event event;

//--------------------draw procedures------------
bool Init(); //initne g_screen a pod
void Toggle_screen(); //change from full screen to window screen and vice-versa
bool Destroy();
//------------types od 'menus'----------
enum Menus
{
	SET_RESOLUTION,
	CREATE_MAP,
	PLAY,
	JOIN,
	HOST,
	EXIT
}
class Game
{
	int state;
	int res_y, res_x;
//	Board gameboard;
	int set_resolution();
	int play();
	int join();
	int host();
public:
	Game();
	int user_input(); //vracia do ktoreho menu sa mame dostat, 0 ak zostat
}
