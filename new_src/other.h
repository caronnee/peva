#ifndef __OTHER__
#define __OTHER__

#include "draw.h"

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
class Play:public Menu
{
	Window * w;
public:
	Play(Window * w_);
	virtual void process(void);
	virtual void draw();
	virtual ~Play()throw();
};
#endif
