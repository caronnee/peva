#ifndef __MENU__
#define __MENU__

#include <string>
#include "graphic.h"

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

		/* returns name of the menu */
		SDL_Surface * get_name()const;

		/* resumes window */
		virtual void resume() = 0;

		/* resolves events */
		virtual void process(void) = 0;

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
