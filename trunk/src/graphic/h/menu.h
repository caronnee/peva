#ifndef __MENU__
#define __MENU__

#include <string>

class Menu
{
	protected:
		std::string name;
	public:
		/* returns name of the menu */
		std::string get_name()const;

		/* resolves events */
		virtual void process(void) = 0;

		/* drwas actual state */
		virtual void draw()=0; 

		/* fill data */
		virtual void init()=0; 

		/* clean data */
		virtual void clean() = 0;
};
#endif
