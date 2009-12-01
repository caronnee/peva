#ifndef __OTHER__
#define __OTHER__

#include <list>
#include <vector>
#include "../../map/h/map.h"
#include "../../add-ons/h/position.h"
#include "graphic.h"


class Settings:public Menu
{
	Window* w;
	std::string names[3]; //nastavit timeouti, resolution, background. TODO!
public:
	Settings(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual void init();
	virtual ~Settings()throw();
};

class Host:public Menu
{
	Window * w;
public:
	Host(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual void init();
	virtual ~Host()throw();
};
class Join:public Menu
{
	Window * w;
public:
	Join(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual void init();
	virtual ~Join()throw();
};

struct Letter
{
	std::string ch;
	int size,heigth;
	SDL_Surface * s;
};

class Play:public Menu
{
	Map * m;
	Window * w;
	Position p;
	Position begin; //whre to begin drae gameboard
	Position resolution;//map resolution in pixels
	std::list<Letter *>::iterator iter, iter_beg, iter_end;
	std::list<Letter *> letts;
	SDL_Rect rect;
	Letter letters[256];
	void redraw();
	std::list<Object *> objects; //all activ objects
	void init(int, int);
	void clear();
	virtual void init();
public:
	Play(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Play()throw();
};
#endif
