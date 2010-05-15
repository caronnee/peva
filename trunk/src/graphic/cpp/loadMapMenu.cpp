#include "../h/loadMapMenu.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/position.h"

#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem.hpp"

namespace bf = boost::filesystem;

Load::Load( Window * w_, std::string ext_, std::string adr_)
{
	w = w_;
	ext = ext_;	
	adr = adr_;
}

void Load::resume()
{
	draw();
}
void Load::resize()
{
	vSkip =  TTF_FontLineSkip(w->g->g_font);
	size = min<int>(maps.size(), (w->g->screen->h - BEGIN_Y) / vSkip );
	begin =0;
	end = size;
}

void Load::process()
{
	while (SDL_PollEvent(&w->g->event))
	{
		switch (w->g->event.type)
		{
			case SDL_VIDEORESIZE:
				w->resize();
				break;
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
					case SDLK_DOWN:
					{
						if (size == 0)
							break;
						unchoose(index);
						index++;
						if (index == maps.size())
						{
							index = 0;
							begin = 0;
							end = size;
						}
						else if (index >= end)
						{
							begin++;
							end++;
							draw();
							return;
						}
						choose(index);
						break;
					}
					case SDLK_UP:
					{
						if (size == 0)
							break;
						unchoose(index);
						index--;
						if (index > maps.size())
						{
							index = maps.size()-1;
							begin = index -size +1;
							end = size;
							draw();
							break;
						}
						if (index < begin)
						{
							begin = index;
							end = begin + size;
							draw();
							return;
						}
						choose(index);
						break;
					}
					case SDLK_RETURN:
					{
						enter();
						return;
					}
					default:
						TEST("Unhandled button")
						break;
					}
				break;
			}
		}	
	}
}

void Load::choose(int index)
{
	SDL_Rect r2;
	r2.x = BEGIN_X;
	r2.y = BEGIN_Y + (index - begin) * vSkip;
	SDL_BlitSurface(maps[index].chosen, NULL, w->g->screen, &r2);
	SDL_UpdateRect(w->g->screen, BEGIN_X , r2.y, 
		w->g->screen->w - BEGIN_X , w->g->screen->h - r2.y );
}
void Load::unchoose(int index)
{
	SDL_Surface * s = maps[index].show;
	for(size_t i =0; i< entered.size(); i++)
		if (entered[i] == maps[index].name)
		{
			s = maps[index].chosen;
			break;
		}
	SDL_Rect r;
	r.x = BEGIN_X;
	r.y = BEGIN_Y + ( index - begin ) * vSkip;
	SDL_BlitSurface(s , NULL, w->g->screen, &r);
	SDL_UpdateRect(w->g->screen, r.x, r.y, 
			w->g->screen->w - BEGIN_X, w->g->screen->h - r.y);
}

void Load::draw()
{
	SDL_Rect rct;
	rct.x = BEGIN_X;
	rct.y = BEGIN_Y;
	rct.h = w->g->screen->h;
	rct.w = w->g->screen->w;

	w->tapestry(rct);

	for (size_t i = 0; i< size; i++)
	{
		unchoose(begin + i);
		if (i+begin == index)
			choose(begin + i);
	}
	SDL_Flip(w->g->screen);
}
void Load::init()
{
	SDL_Surface * n = get_name();

	SDL_Rect rct;
	rct.x = 0;
	rct.y = 0;
	rct.w = w->g->screen->w;
	rct.h = w->g->screen->h;

	w->tapestry(rct);
	rct.x = (w->g->screen->w - n->w)/2;
	rct.y = (BEGIN_Y - n->h)/2;
	SDL_BlitSurface(n, NULL, w->g->screen, &rct );
	SDL_Flip(w->g->screen);

	index = 0;
	//zisti vsetky s priponou .map
	bf::directory_iterator end_iter;
	if (!bf::exists( adr ))
		bf::create_directory( adr );
	for ( bf::directory_iterator dir_itr( adr );
          dir_itr != end_iter;
          ++dir_itr )
	{
		if ( !bf::is_regular( dir_itr->status() ) )
			continue;
		if ( !(bf::extension( dir_itr->path()) == ext ))
			continue;
		MapRecord record;
		record.name = dir_itr->leaf();
		record.show = TTF_RenderText_Solid(w->g->g_font, record.name.c_str(), w->g->normal);
		record.chosen = TTF_RenderText_Solid(w->g->g_font, record.name.c_str(), w->g->light);
		record.name = dir_itr->path().string();
		maps.push_back( record );
	}
	resize();
	if (size == 0 )
	{
		SDL_Rect clip;
		SDL_GetClipRect(w->g->screen, &clip);
		w->tapestry(clip);
		std::string text = "No *" + ext + " found in " +adr;
		SDL_Surface* textImage = TTF_RenderText_Solid(w->g->g_font, text.c_str(), w->g->normal);
		SDL_Rect r;
		r.x = (w->g->screen->w - textImage->w)/2;
		r.y = (w->g->screen->h - textImage->h)/2;
		SDL_BlitSurface(textImage, NULL, w->g->screen, &r);
		SDL_Flip(w->g->screen);
		SDL_FreeSurface(textImage);
		while(true)
		{
			if((SDL_WaitEvent(&w->g->event)==0)
				||(w->g->event.type ==SDL_KEYDOWN))
				break;
		}
		w->pop();
	}
}
void Load::enter()
{
	entered.push_back(maps[index].name);
	w->pop();
}
void Load:: clean()
{
	entered.clear();
	for ( size_t i =0; i< maps.size(); i++)
	{
		SDL_FreeSurface(maps[i].chosen);
		SDL_FreeSurface(maps[i].show);
	}
	maps.clear();
}
Load::~Load() {}


LoadMapMenu::LoadMapMenu(Window * window, Map * map):Load(window, ".map","./maps")
{
	w = window;
	name(w->g,"Load Map");
	index = 0;
	mapToFill = map;
}
	
void LoadMapMenu::enter()
{
	mapToFill->clean();
	mapToFill->load(w->g, maps[index].name);
	w->pop();
}	
LoadMapMenu::~LoadMapMenu(){}
