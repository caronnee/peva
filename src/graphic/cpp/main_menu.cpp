#include "../h/main_menu.h"
#include "../h/create_map.h"
#include "../h/other.h"
#include "../../add-ons/h/macros.h"

Main::Main(Window * w_, int argc, char * argv[])
{
	for (int i = 1; i< argc; i++)
	{
		std::string s(argv[i]);
		files.push_back(s);
	}
	w = w_; 
	for (int i =0; i< NUMBEROFMENUS; i++)
		menus[i] = NULL;
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
							iterator--;
							if (iterator<0) 
								iterator = NUMBEROFMENUS -1;
							menus[iterator]->set();
							break;
						}
					case SDLK_DOWN:
						{
							menus[iterator]->unset();
							iterator++;
							iterator%=NUMBEROFMENUS;
							menus[iterator]->set();
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
	for (int i =0; i < NUMBEROFMENUS; i++)
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
	update();
}
void Main::update()
{
	SDL_Rect rect;
	rect.x = (w->g->screen->w)/2 - 15;// TODO zmenit na lepsie
	for (int i =0; i< NUMBEROFMENUS; i++)
	{
		rect.x = (w->g->screen->w >> 1) - (menus[i]->get_name()->w >> 1);
		rect.h = w->g->font_size;
		SDL_BlitSurface(menus[i]->get_name(), NULL, w->g->screen, &rect);
		rect.y += w->g->font_size << 1;
		SDL_UpdateRect(w->g->screen, rect.x, rect.y, rect.w, rect.h);
	}
}
void Main::init()
{
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
