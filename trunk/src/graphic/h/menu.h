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

		/* returns name of the menu */
		SDL_Surface * get_name()const;

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
