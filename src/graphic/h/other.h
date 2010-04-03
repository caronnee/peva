#ifndef __OTHER__
#define __OTHER__

#include <list>
#include <vector>
#include "../../map/h/map.h"
#include "../../add-ons/h/position.h"
#include "../../language/h/robot.h"
#include "graphic.h"


class Settings:public Menu
{
	Window* w;
	Menu * names[3]; //nastavit timeouti, resolution, background. TODO!
public:
	Settings(Window * w_);
	void process(void);
	void resume();
	void draw();
	void init();
	void clean();
	virtual ~Settings();
};

class Host:public Menu
{
	Window * w;
public:
	Host(Window * w_);
	void process(void);
	void resume();
	void draw();
	void init();
	void clean();
	virtual ~Host();
};
class Join:public Menu
{
	Window * w;
public:
	Join(Window * w_);
	void process(void);
	void resume();
	void draw();
	void init();
	void clean();
	virtual ~Join();
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
