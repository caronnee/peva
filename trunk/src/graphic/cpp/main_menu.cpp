#include "../h/main_menu.h"
#include "../h/create_map.h"
#include "../h/other.h"
#include "../../add-ons/h/macros.h"

Main::Main(Window * w_, int argc, char * argv[])
{
	size = 0;	
	for (int i = 1; i< argc; i++)
	{
		std::string s(argv[i]);
		files.push_back(s);
	}
	w = w_; 
	menus = NULL;
}
void Main::resume()
{
	draw();
}
void Main::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->pop();
							return;
						}
					case SDLK_RETURN:
						{
							w->add(menus[iterator]);
							break;
						}
					case SDLK_UP:
						{
							menus[iterator]->unset();
							update(menus, size, iterator, w->g);
							iterator--;
							if (iterator<0) 
								iterator = size -1;
							menus[iterator]->set();
							update(menus, size, iterator, w->g);
							break;
						}
					case SDLK_DOWN:
						{
							menus[iterator]->unset();
							update(menus, size, iterator, w->g);
							iterator++;
							iterator%=size;
							menus[iterator]->set();
							update(menus, size, iterator, w->g);
							break;
						}
					default:
						//throw exception
						break;
				}
				break;
			}
	}
}
void Main::clean()
{
	for (int i =0; i < size; i++)
	{
		if (menus[i])
			delete menus[i];
		menus[i] = NULL;
	}
	files.clear();
}

void Main::draw()
{
	SDL_Rect pom;
	SDL_GetClipRect(w->g->screen, &pom);
	w->tapestry(pom);
	
	TTF_SetFontStyle(w->g->g_font, TTF_STYLE_NORMAL);
	SDL_Flip(w->g->screen);
	drawMenu(menus, size, w->g );
}

void Main::init()
{
	menus = new Menu*[NUMBEROFMENUS];
	size = NUMBEROFMENUS;
	iterator = 0;
	menus[0] = new Play(w,files); 
	menus[1] = new Host(w); 
	menus[2] = new Join(w);
	menus[3] = new Settings(w);
	menus[4] = new Create_map(w);
	menus[0]->set();
} 

Main::~Main()
{
	clean();
}
