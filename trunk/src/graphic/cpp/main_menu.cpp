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
	init();
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
							menus[iterator]->init();
							break;
						}
					case SDLK_UP:
						{
							iterator--;
							if (iterator<0) 
								iterator = NUMBEROFMENUS -1;
							break;
						}
					case SDLK_DOWN:
						{
							iterator++;
							iterator%=NUMBEROFMENUS;
							break;
						}
					default:
						//throw exception
						break;
				}
				break;
			}
	}
	draw();
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
		TTF_SizeText(w->g->g_font, menus[i]->get_name().c_str(),&width, NULL);
		if (i==iterator)
		{
			text = TTF_RenderText_Solid(w->g->g_font,menus[i]->get_name().c_str(), w->g->light );
		}
		else
		{
			text = TTF_RenderText_Solid(w->g->g_font,menus[i]->get_name().c_str(), w->g->normal );
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
void Main::init()
{
	iterator = 0;
	menus[0] = new Play(w,files); 
	menus[1] = new Host(w); 
	menus[2] = new Join(w);
	menus[3] = new Settings(w);
	menus[4] = new Create_map(w);
} 

Main::~Main()
{
	clean();
}
