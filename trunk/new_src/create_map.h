#ifndef __CREATE_MAP__
#define __CREATE_MAP__

#include "draw.h"
#include "menu.h"

class Create_map:public Menu
{
	enum Map_divide
	{
		MAP = 0,
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

	enum Win_type
	{
		RESOLUTION = 0,
		DRAW,
		SAVING
	};
	Window * w;
	Win_type state;
	bool x; //x = oddelovac u resolution
	bool mouse_down; //bola vybrana/ uklada sa tile

	int begin_x, begin_y;
	int window_begin_x, window_begin_y; //centrovanie do stredu

	SDL_Surface * text;
	SDL_Surface * selected;
	int text_width;
	int select;
	int get_rect(int x, int y, SDL_Rect * r,int max);

	Tile * tiles[NumberOfWalls_ -1];
	SDL_Rect tile_rect[NumberOfWalls_];
	SDL_Rect rects[NumberOfMapDivision];

	SDL_Surface * info_o;
	std::string info;
	int info_width;
	std::string file_name;
	SDL_Rect file_r;

/*	SDL_Rect ** map_rects;
	int map_rects_number;
	int offset_x, offset_y;*/
	unsigned int ** map; //maximalne 32 druhov stien, na mape prave 1object, take to nevadi
	SDL_Surface * resol[NUMCHARS]; //0-9+x
	int resol_width[NUMCHARS];
	int resolX,resolY, number_written; //max 5x5 cifier?
	std::string written_x, written_y;
	void process_map();
	void process_resolution();
	void draw_resol();
	void saving();
	bool save();
	void reset();
public:
	Create_map(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Create_map()throw();
};
#endif
