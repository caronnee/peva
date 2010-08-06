#ifndef __CREATE_MAP__
#define __CREATE_MAP__

#include "window.h"
#include "menu.h"
#include "../../editor/h/snake.h"
#include "../../graphic/h/images.h"
#include "../../map/h/map.h"
#include "main_menu.h"
#include <map>

#define BUTTONS 7

/* struct for holding information which size (resolution) belongs to name */
struct Resolution
{
	/* surface to be blit whe not chosen */
	SDL_Surface * normal;
	
	/* surface to be lit when chosen */
	SDL_Surface * chosen;

	/* pre-defined resolution according to name */
	size_t value;
};

/* class processing the creation of map */
class Create_map:public Menu
{
private:
	/* map of resolutions according to name */
	std::map<std::string, Resolution> resolutions;

	/* iterator holding informatio abou resolution in X-axis */
	std::map<std::string, Resolution>::iterator resolutionIterFirst;

	/* iterator holding informatio abou resolution in Y-axis */
	std::map<std::string, Resolution>::iterator resolutionIterSecond;
	
	/* help menu*/
	Menu * help;

	/* division of screen, should be recomputed when fullscreened */
	enum Map_divide
	{
		MAP = 0,
		CLEAN,
		SAVE,
		LOAD,
		GENERATE,
		HELP,
		EXIT,
		VISIBILITY,
		CHOOSE,
		LEFT,
		UP,
		RIGHT,
		DOWN,
		NumberOfMapDivision
	};

	/* switch states */ //TODO zmenit na vlastne menu
	enum Win_type
	{
		RESOLUTION = 0,
		DRAW,
		SAVING
	};

	/* sets button fo visibility to actual visibility of load map */
	void setVisibility();

	/* menu showing saved maps */
	Menu * nextMenu;

	/* function handling resizing */
	void resize();

	/* images of buttons */
	SDL_Surface * buttonsImages [BUTTONS];

	/* precomputes allowed chars in resolution mode */
	SDL_Surface * resol[NUMCHARS]; //0-9+x

	/* precomputed info about what is ecpected on this screen */
	SDL_Surface * info_o;

	/* where to blit choosable object */
	SDL_Rect tile_rect[NumberObjectsImages];

	/* where to blit areas */
	SDL_Rect rects[NumberOfMapDivision];

	/* which state is this menu*/
	Win_type state;

	/* mthod to draw i-th panel to screen*/
	void drawPanel(int i);

	/* resolution deliminer flag*/
	bool x;

	/* flag if the mouse left button is pressed*/
	bool mouse_down; //bola vybrana/ uklada sa tile

	/* image og text to be shown in resolution screen */
	SDL_Surface * text;

	/* adds object to map */
	void addObj();

	/* flag determining which object was selected to be blit on map*/
	int select;

	/* graphic information  about the screen */
	Window * w;

	/* return position closest to the object */
	Position closest(Position point, Object * toClose);

	/* skins of the object that can be set to map*/
	std::vector<Skin*> skins;

	/* in resolution key handling*/
	void handleKey(SDLKey c);

	/* handling backspece in resolution state */
	void backspace();

	/* setting state to draw, if resolution correct */
	void drawInit();

	/* handling the key in resolution, checkging type */
	void keyDown(SDLKey c);

	/* returns index of area in position x, y, 
	 * where max is maximum number of areas */ //TODO position namiesto x, y
	int get_rect(int x, int y, SDL_Rect * r,int max);

	/* storing typed filename so far */
	std::string file_name;

	/* center of the screen */ //TODO naprosto nepotrebne, upravit
	SDL_Rect file_r;

	/* map being drawn */
	Map * map;

	/* width for every char in allowed char */
	int resol_width[NUMCHARS];

	/* map resolution as typed */ 
	std::string written_x, written_y;

	/* in drawing state process events */
	void process_map();

	/* in resolution state, process event */
	void process_resolution();

	/* drawing the resolution window, asking for typing resolution */
	void draw_resol();

	/* window to save map */
	void saving();

	void removeFromMap(Position p);

public:
	/* Constructor */
	Create_map(Window * w_);

	/* resumes window */
	void resume();
	
	/* init creates instances of elements immediately needed,
	 *  in passive state (not running), it needs only name 
	 *  for drawing */
	void init();

	/* event handling */
	void process(void);

	/* draws the screen again */
	void draw();

	/* goiing to passive state and cleaning variables */
	void clean();
	
	/* destructor, InstructionCalling function clean()*/
	virtual ~Create_map()throw();

	/*function to fill created map */
	void generuj();

	/* function to handle mouse strokes */
	void buttonDown(int rentangleId, int atX, int atY);
};
#endif
