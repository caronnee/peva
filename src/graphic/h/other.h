#ifndef __OTHER__
#define __OTHER__

#include <list>
#include <vector>
#include "../../map/h/map.h"
#include "../../add-ons/h/position.h"
#include "../../language/h/robot.h"
#include "../../language/h/instructions.h"
#include "graphic.h"
#include "main_menu.h"
#include "loadMapMenu.h"

struct Penalize
{
	int penalize;
	SDL_Surface * penal;
	SDL_Surface * name;
	SDL_Surface * nameChosen;
};

class SetPenalize : public Menu
{
	Window *w;
	Penalize instructions[IGroups];
	int begin, size, index, end, vSkip;
	std::vector<int>* penals;
public:
	void resize();
	SetPenalize(Window * w, std::vector<int>* penalize);
	void init();
	void resume();
	void choose(int index);
	void unchoose(int index);
	void process();
	void draw();
	void clean();
	virtual ~SetPenalize();
};
class ShowMenu : public Menu
{
	Window * w;
	std::string strToshow;
	size_t iter;
	size_t size;
	std::vector<SDL_Surface *> images;
public:

	ShowMenu(Window * w, std::string str);
	void init();
	void process();
	void resume();
	void draw();
	void clean();
	void resize();
	virtual ~ShowMenu();
};

class SetScheduller : public Menu
{
	int iter;
	Window * w;
	int * result;
	SDL_Surface * txt;
	SDL_Surface * value;
	SDL_Surface * schedullers[2];
	std::string valueString;
public:
	SetScheduller(Window * w, int *sched);
	void resize();
	void resume();
	void init();
	void draw();
	void process();
	void clean();
	virtual ~SetScheduller();
	
};
class SetMaps : public Load
{
	std::vector<std::string> * result;
public:
	SetMaps(Window * w, std::vector<std::string> * result_, std::string ext, std::string addr );
	void enter();
	void clean();
	virtual ~SetMaps();
};
class Settings:public Main
{
	Setting * s;
public:
	Settings(Window * w_, Setting *s);
	void init();
	virtual ~Settings();
};


class Play:public Menu
{
	Menu * show;
	size_t focus;
	std::vector<std::string> files;
	Map * m;
	Window * w;
	bool done;
	Robots robots;
	int mapIter;
	SDL_Rect rect;
	void init(int, int);
	Setting * settings;
	Menu * loadInput;
public:
	Play(Window * w_, Setting * s);
	void process(void);
	void init();
	void resize();
	void resume();
	void draw();
	void clean();
	virtual ~Play();
};
#endif
