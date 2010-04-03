#include "../../add-ons/h/help_functions.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem.hpp"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/position.h"
#include "../h/loadMapMenu.h"

#define BEGIN_X 20
#define BEGIN_Y 20

namespace bf = boost::filesystem;

LoadMapMenu::LoadMapMenu(Window * window, Map * map)
{
	index = 0;
	mapToFill = map;
	w = window;
}
void LoadMapMenu::resume()
{
	draw();
}
void LoadMapMenu::process()
{
	while (SDL_PollEvent(&w->g->event))
	{
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
					case SDLK_DOWN:
					{
						if (size == 0)
							break;
						unchoose(index);
						index++;
						if (index == maps.size())
							index--;
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
							index = 0;
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
						mapToFill->clean();
						mapToFill->load(w, maps[index].name);
						w->pop();
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

void LoadMapMenu::choose(int index)
{
	SDL_Rect r2;
	r2.x = BEGIN_X;
	r2.y = BEGIN_Y + (index - begin) * vSkip;
	SDL_BlitSurface(maps[index].chosen, NULL, w->g->screen, &r2);
	SDL_UpdateRect(w->g->screen, BEGIN_X , r2.y, 
		w->g->screen->w - BEGIN_X , w->g->screen->h - r2.y );
}
void LoadMapMenu::unchoose(int index)
{
	SDL_Rect r;
	r.x = BEGIN_X;
	r.y = BEGIN_Y + ( index - begin ) * vSkip;
	SDL_BlitSurface(maps[index].show, NULL, w->g->screen, &r);
	SDL_UpdateRect(w->g->screen, r.x, r.y, 
			w->g->screen->w - BEGIN_X, w->g->screen->h - r.y);
}

void LoadMapMenu::draw()
{
	SDL_Rect rct;
	rct.x = 0;
	rct.y = 0;
	rct.h = w->g->screen->h;
	rct.w = w->g->screen->w;

	TEST("--")
	w->tapestry(rct);

	for (size_t i = 0; i< size; i++)
	{
		unchoose(begin + i);
		if (i+begin == index)
			choose(begin + i);
	}
	SDL_Flip(w->g->screen);
}
void LoadMapMenu::init()
{
	//zisti vsetky s priponou .map
	vSkip =  TTF_FontLineSkip(w->g->g_font);
	bf::directory_iterator end_iter;
	if (!bf::exists("./maps"))
		bf::create_directory("maps");
	for ( bf::directory_iterator dir_itr( "./maps" );
          dir_itr != end_iter;
          ++dir_itr )
	{
		if ( !bf::is_regular( dir_itr->status() ) )
			continue;
		if ( !(bf::extension( dir_itr->path()) == ".map"))
			continue;
		MapRecord record;
		record.name = dir_itr->leaf();
		record.show = TTF_RenderText_Solid(w->g->g_font, record.name.c_str(), w->g->normal);
		record.chosen = TTF_RenderText_Solid(w->g->g_font, record.name.c_str(), w->g->light);
		record.name = dir_itr->path().string();
		maps.push_back(record);
	}
	size = min<int>(maps.size(), (w->g->screen->h - BEGIN_Y) / vSkip );
	begin =0;end = size;
}
void LoadMapMenu:: clean()
{
	//nothing
}
LoadMapMenu::~LoadMapMenu()
{
}
