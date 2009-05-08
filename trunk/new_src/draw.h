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
bool Destroy();
void Toggle_screen(); //change from full screen to window screen and vice-versa
//------------types od 'menus'----------

class Set_Map_Resolution:Menu_item
{
};
class Create_map:Menu_item
{
	int create_map(int x, int y);
};
class Menu_item
{
	std::string name;
	Menu * next_menu;
public:
	Menu_item(std::string name, Menu * next);
	int User_input();//determine what to do after user input (keyboard, mouse )
	void Draw_menu();
	virtual void choosed() = 0; //co spravi, ak je volba tymto potvrdena
}
class Menu
{
	std::vector <Menu_item *> items;
public:
	Menu();
	void add(Menu_item* it);
}
class Main_manu:Menu_item
{
	std::string menu[] = {"Play","Host","Join","Create_map","Settings","Exit"};
	int Host(); //hostovanie hry
	int Play();//draws a game
	int Join_game();//joins a game on some port
	int Settings();//user can change initial resolution, fullscren resolution, keyboard event(????);timeout
	int End();//do you really want to quit?
public:
}


class Game_state //abstract class
{
public:
	Game_state();
	virtual Draw() = 0;
	virtual User_input() = 0;	
	virtual Switch_menu() = 0;
};
class Game : game_statea //obsahuje vsetky veci pre hru, gameboard atd;
{
};
