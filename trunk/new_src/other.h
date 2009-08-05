#ifndef __OTHER__
#define __OTHER__

#include <vector>
#include "draw.h"
#include "position.h"
#include <list>


class Settings:public Menu
{
	Window* w;
	std::string names[3]; //nastavit timeouti, resolution, background. TODO!
public:
	Settings(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Settings()throw();
};

class Host:public Menu
{
	Window * w;
public:
	Host(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Host()throw();
};
class Join:public Menu
{
	Window * w;
public:
	Join(Window * w_);
	virtual void process(void);
	virtual void draw();
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
	enum PlayType
	{
		Editor,
		Game
	};

	Window * w;
	Position p;
	std::list<Letter *>::iterator iter;
	std::list<Letter *> letts;
	SDL_Rect rect;
	Letter letters[256];
public:
	Play(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Play()throw();
};
#endif
