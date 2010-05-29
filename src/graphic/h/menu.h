#ifndef __MENU__
#define __MENU__

#include <string>
#include "graphic.h"

#define BEGIN_X 40
#define BEGIN_Y 40

/* default structure for hadling menus*/
class Menu
{
	protected:
		SDL_Surface * nameHighLight;
		SDL_Surface * nameNormal;
		SDL_Surface * show;
	public:
		/* constuctor */
		Menu();

		/* draws menu in the middle of the screen and updates it */
		void drawMenu(Menu ** menus, int size, Graphic * g);

		/* updates drawing menu */
		void update(Menu ** menus, int size, int iterator, Graphic * g);

		/* returns at which menu is mouse pointed at */
		int getMenu( Menu ** menus, int size, Graphic* g);

		/* returns name of the menu */
		SDL_Surface * get_name()const;

		/* resumes window */
		virtual void resume() = 0;

		/* function hadling resizing window */
		virtual void resize() = 0;

		/* resolves events */
		virtual void process() = 0;

		/* sets name of the menu */
		void name(Graphic * g, std::string s);

		/* draws actual state */
		virtual void draw()=0; 

		/* fill data */
		virtual void init()=0; 

		/* clean data */
		virtual void clean() = 0;

		/* changes name to highlight */
		void set();

		/* changes name to normal */
		void unset();

		/* destructor */
		~Menu();
};
#endif
