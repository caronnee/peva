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
	SetPenalize(Window * w, std::vector<int>* penalize);
	void init();
	void resume();
	void choose(int index);
	void unchoose(int index);
	void process();
	void draw();
	void clean();
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
	void resume();
	void init();
	void draw();
	void process();
	void clean();
	
};
class SetMaps : public Load
{
	std::vector<std::string> * result;
public:
	SetMaps(Window * w, std::vector<std::string> * result_ );
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

struct Letter
{
	std::string ch;
	int size,heigth;
	SDL_Surface * s;
};

class Play:public Menu
{
	std::vector<std::string> files;
	Map * m;
	Window * w;
	bool done;
	Robots robots;
	std::list<Letter *>::iterator iter, iter_beg, iter_end;
	std::list<Letter *> letts;
	SDL_Rect rect;
	Letter letters[256];
	void init(int, int);
public:
	Play(Window * w_, std::vector<std::string> files);
	void process(void);
	void init();
	void resume();
	void draw();
	void clean();
	virtual ~Play();
};
#endif
