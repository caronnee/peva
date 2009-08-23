#ifndef __MENU__
#define __MENU__

#include <string>

class Menu
{
	public:
		int iterator;//kolko sme toho naalokovali
		std::string name;
		std::string get_name();
		virtual void process(void) = 0;
		virtual void draw()=0; 
};
#endif
