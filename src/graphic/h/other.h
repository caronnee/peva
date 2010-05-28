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


/* penalization value to concrete robot 
 * instruction + images for drawing 
 * */
struct Penalize
{
	/* value of penalization instruction */
	int penalize;

	/* value converted to surface */
	SDL_Surface * penal;

	/* image of name */
	SDL_Surface * name;

	/* image of name, highlited */
	SDL_Surface * nameChosen;
};
/* 
 * menu drawing penalization instruction 
 * */
class SetPenalize : public Menu
{
	/* handle to window */
	Window *w;

	/* value for every instruction denoted by index */
	Penalize instructions[IGroups];

	/* index of the first instruction to draw,
	 * size on instruction to */
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
	SetScheduller(Window * w);
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
class SetSections : public Menu
{
	SDL_Surface * sectionPart[SECTIONS * 3];
	SDL_Surface ** sections;
	GamePoints * gp;
	int iter;
	int iterSubSection;
	Window * w;
public:
	SetSections(Window * w, GamePoints * points);
	void init();
	void process();
	void draw();
	void clean();
	virtual ~SetSections();

	void resume();
	void resize();

};
class Settings:public Main
{
	enum Menus
	{
		Penalize,
		Scheduller,
		Maps,
		Sections,
		NumberOfMenus
	};
public:
	Settings(Window * w_);
	void init();
	virtual ~Settings();
};


class Play:public Menu
{
	/* timestamp */
	size_t timeStamp;

	/* true of error occured */
	bool error;

	/* wheather mnu should recreate map and robots */
	bool recreate;

	/* addition manu to show when something happens */
	Menu * show;

	/* which robot is focused */
	size_t focus;

	/* map of the dungeon */
	Map * m;

	/* window hadler */
	Window * w;

	/* if true, game is over */
	bool done;

	/* loaded robots */
	Robots robots;

	/* which map is currently in use */
	int mapIter;

	/* init some map when none was chosen */
	void init(int, int);

	/* menu for loading robot inputs */
	Menu * loadInput;

	/* sets map to center robot with focus */
	void setFocus();
public:
	/* constructor */
	Play(Window * w_);

	/* handling events */
	void process();

	/* initialization when meni chosen */
	void init();

	/* handling resizing */
	void resize();

	/* handling return to menu */
	void resume();

	/* drawing events */
	void draw();

	/* clening after menu if called off */
	void clean();

	/* destructor */
	virtual ~Play();
};
#endif
