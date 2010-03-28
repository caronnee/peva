#ifndef __CREATE_MAP__
#define __CREATE_MAP__

#include "graphic.h"
#include "menu.h"
#include "../../editor/h/snake.h"
#include "../../graphic/h/images.h"
#include "../../map/h/map.h"

class Create_map:public Menu
{


private:
	/* division of screen, should be recomputed when fullscreened */
	enum Map_divide
	{
		MAP = 0,
		CLEAN,
		SAVE,
		GENERATE,
		EXIT,
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
	void drawPanel(int i, Window * w);

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

	/* width of the text shown in resolution processing */
	int text_width;

	/* returns index of area in position x, y */ //TODO position namiesto x, y
	int get_rect(int x, int y, SDL_Rect * r,int max);

	/* storing typed filename so far */
	std::string file_name;

	/* center of the screen */ //TODO naprosto nepotrebne, upravit
	SDL_Rect file_r;

	/* map being drawn */
	Map * map;

	/* width for every char in allowed char */ //TODO vlastna klasa?
	int resol_width[NUMCHARS];

	/* map resolution as typed */ //TODO netrebalo by
	std::string written_x, written_y;

	/* in drawing state process events */
	void process_map();

	/* in resolution state, process event */
	void process_resolution();

	/* drawing the resolution window, asking for typing resolution */
	void draw_resol();

	/* window to save map */
	void saving();

	Object * lastPut;
public:
	/* Constructor */
	Create_map(Window * w_);
	
	/* init creates instances of elements immediately needed, in passive state (not running), it is needed only name for drawing */
	void init();

	/* reaction to events and drawing */
	void process(void);

	/* draws the screen again, if needed */
	void draw();

	/* goiing to passive state and cleaning variables */
	void clean();
	
	/* destructor, calling function clean()*/
	virtual ~Create_map()throw();

	/*function to fill created map */
	void generuj();

	/* function to handle mouse strokes */
	void buttonDown(int rentangleId, int atX, int atY);
};
#endif
