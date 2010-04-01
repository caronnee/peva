#include "../../add-ons/h/help_functions.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem.hpp"
#include "../../add-ons/h/macros.h"
#include "../h/loadMapMenu.h"

#define BEGIN_X 20
#define BEGIN_Y 20

namespace bf = boost::filesystem;

LoadMapMenu::LoadMapMenu(Window * window, Map * map)
{
	index = 0;
	map->clean();
	w = window;
}
void LoadMapMenu::process()
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
					case SDLK_DOWN:
						SDL_Rect r;
						r.x = BEGIN_X;
						r.y = BEGIN_Y + index * vSkip;
						SDL_BlitSurface(maps[index].show, NULL, w->g->screen, &r);
						SDL_UpdateRect(w->g->screen, r.x, r.y, w->g->screen->w - 2*BEGIN_X, w->g->screen->h- 2* BEGIN_Y);
						index ++;
						if (index == maps.size())
							index--;
						if (index > end)
						{
							begin = end - size;	
							end=index;
							draw();
							return;
						}
						SDL_BlitSurface(maps[index].chosen, NULL, w->g->screen, &r);
						SDL_UpdateRect(w->g->screen, r.x, r.y, w->g->screen->w - 2*BEGIN_X, w->g->screen->h - 2* BEGIN_Y);
						break;
					case SDLK_UP:
						SDL_BlitSurface(maps[index].show, NULL, w->g->screen, &r);
						SDL_UpdateRect(w->g->screen, r.x, r.y, w->g->screen->w - 2*BEGIN_X, w->g->screen->h - 2* BEGIN_Y);
						index--;
						if (index < 0)
							index = 0;
						if (index < begin)
						{
							begin = index;
							end = begin + size;
							draw();
							return;
						}
						SDL_BlitSurface(maps[index].chosen, NULL, w->g->screen, &r);
						SDL_UpdateRect(w->g->screen, r.x, r.y, w->g->screen->w - 2*BEGIN_X, w->g->screen->h - 2* BEGIN_Y);
						break;
					case SDLK_RETURN:
						mapToFill->load(w, maps[index].name);
						w->pop();
						return;
					default:
						TEST("Unhandled button")
						break;
				}
				break;
			}
	}	
}
void LoadMapMenu::draw()
{
}
void LoadMapMenu::init()
{
	//zisti vsetky s priponou .map
	vSkip =  TTF_FontLineSkip(w->g->g_font);
	bf::directory_iterator end_iter;
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
		maps.push_back(record);
	}
	size = min<int>(maps.size(), (w->g->screen->h - BEGIN_Y) / vSkip );
}
void LoadMapMenu:: clean()
{
	//nothing
}
LoadMapMenu::~LoadMapMenu()
{
}
