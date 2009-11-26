#include "../h/main_menu.h"
#include "../h/create_map.h"
#include "../h/other.h"

Main::Main(Window * w_)
{
	iterator = 0;
	w = w_; //akonahle sa vytvori, tak sa vykresli to, co sa ma
	menus[0] = new Play(w_); //TODO zmenit na add a tak podobne, aby to bolo dynamicke
	menus[1] = new Host(w_); //TODO mozno nechat bez iterator a menit to rovno switch( state)?
	menus[2] = new Join(w_);
	menus[3] = new Settings(w_);
	menus[4] = new Create_map(w_);
	}
void Main::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					case SDLK_RETURN:
						{
							w->state.push(menus[iterator]);
							menus[iterator]->init();
							break;
						}
					case SDLK_UP:
						{
							iterator--;
							if (iterator<0) iterator = NUMBEROFMENUS -1;
							break;
						}
					case SDLK_DOWN:
						{
							iterator++;
							iterator%=NUMBEROFMENUS;
						}
					default:
						break;
				}
				break;
			}
	}
	draw();
}
void Main::draw()
{
	SDL_Rect rect;

	w->tapestry();
	
	int offset_up = 10;
	rect.y = (w->g->screen->h + (w->g->font_size+offset_up)*4)/2;
	rect.x = (w->g->screen->w)/2 - 15;// TODO zmenit na lepsie
	SDL_Surface* text;
	TTF_SetFontStyle(w->g->g_font, TTF_STYLE_NORMAL);
	int width;
	
	rect.y = (w->g->screen->h >> 1) - TTF_FontLineSkip(w->g->g_font)*2;
	for (int i =0; i< NUMBEROFMENUS; i++)
	{
		TTF_SizeText(w->g->g_font, menus[i]->name.c_str(),&width, NULL);
		if (i==iterator)
		{
			text = TTF_RenderText_Solid(w->g->g_font,menus[i]->name.c_str(), w->g->light );
		}
		else
		{
			text = TTF_RenderText_Solid(w->g->g_font,menus[i]->name.c_str(), w->g->normal );
		}	
		if (text ==NULL) std::cout << " Error rendering text " << TTF_GetError() <<std::endl; //podla mna tu tato podmienka nemusi byt
		rect.x = (w->g->screen->w >> 1) - (width >> 1);
		if (text ==NULL) std::cout << "IEuhfzeuh:"<<TTF_GetError() <<std::endl;
		SDL_BlitSurface(text, NULL, w->g->screen, &rect);
		SDL_FreeSurface(text);
		rect.y+=30;
	}
	SDL_Flip(w->g->screen);
}
void Main::init(){} //TODO nieco sa tu bude initovat
Main::~Main()throw ()
{
	for (int i =0; i < NUMBEROFMENUS; i++)
	{
		delete menus[i];
	}
}
