//send a messages during a game?In play method
#define SDL_SUBSYSTEMS SDL_INIT_VIDEO
#define WIN_BPP 0
#define WIN_TITLE "Codewars"
#define IMG_WIDTH 50
#define IMG_HEIGHT 50
#define WIDTH 500
#define HEIGHT 480

class Draw //singleton variable because of g_screen
{
//-------------------- Draw variables-----------
SDL_Surface * g_screen;//main window
TTF_Font * g_font;//main font
SDL_images ..//for drawing a scenes
SDL_Event event;
Uint32 win_flags = SDL_HWSURFACE|SDL_RESIZABLE;
Uint32 win_width=500;
Uint32 win_height=480;
Uint32 win_max_width=1280;
Uint32 win_max_height=1024;

//--------------------draw procedures------------
bool init();
bool destroy();
bool drawing();
bool switch_menu(); //changes menu, submenus,games
void toggle_screen(); //change from full screen to window screen and vice-versa
int user_input();//determine what to do after user input (keyboard, mouse )
//------------types od 'menus'----------
int play();//draws a game
int join_game();//joins a jame on some port
int settings();//user can change initial resolution, fullscren resolution, keyboard event(????);timeout, face of bot,map, it is before a game begins
int end();//do you really want to quit?
}
