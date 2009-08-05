#include "map.h"

Map::Map(Position resol)
{
	resolution = resol;
	map = new Object**[resol.x];
	for( int i =0; i< resolution.x; i++)
	{
		map[i] = new Object*[resolution.y];
		for (int k = 0; k< resolution.y; k++)
		{
			map[i][k] = NULL;
		}
	}
	rects = new SDL_Rect * [resol.x];
	SDL_Rect r(0,0);
	for(int i = 0; i< resol.x)
	{
		rects[i] = new SDL_Rect[resol.y];
		for(int j =0; j< resol.y; j++)
		{
			rects[i][j] = r;
			r.y+=IMG_HEIGHT;
		}
		r.y = 0;
		r.x+=IMG_WIDTH;
	}
}
void Map::redraw(Window * w) //POZOR, mozny segfault, potrebujem, aby boli vzdy minim z kazdehokonca
{
	//vytapetuj to naskor prazdnymi tilom
	SDL_Rect r(0,0);
	Position pos(begin_draw_at);
	for (int i =0; i< resolution.x; i++)
	{
		for(int j =0; j< resolution.y; j++)
		{
			SDL_BlitSurface(m.tile[FreeTile],NULL, w->g->g_screen, &r);
			r.y+=IMG_HEIGHT;
		}
		r.y = 0;
		r.x+=IMG_WIDTH;
	}
	for (int i =0; i< resolution.x; i++)
	{
		for(int j =0; j< resolution.y; j++)
		{
			Object * o = map[pos.x][pos.y];
			if(o!=NULL)
			{
				SDL_BlitSurface(o,NULL,w->g->g_screen, &o->pos);
			}
			pos.y++;
			r.y+=IMG_HEIGHT;
		}
		r.y = 0;
		pos.y = begin_draw_at.y;
		pos.x++;
		r.x+=IMG_WIDTH;
		r.x = 0;
	}
	SDL_Flip(w->g->g_screen);
}

void Map::update(Window * w, Position p)
{
	Position pos(p.x-1,p.y-1);	
	SDL_Rect r()
	for (int i =0; i<=2; i++)
	{
		for (int j =0; j<=2; j++)
		{
			SDL_BlitSurface(m.tile[FreeTile],NULL,w-.g->g_screen, &r);
		}
	}
	for (int i =-1; i<=1; i++)
	{
		for (int j =-1; j<=1; j++)
		{
			SDL_BlitSurface(map[x.x][y.y],NULL,w-.g->g_screen, &r);
		}
	}
}
~Map::Map() throws()
{
	for(int i = 0; i< resolution.x; i++)
	{
		for(int j =0; j< resolution.y; j++)
			delete map[i][j];
		delete [] map[i];
	}
	delete map;
}
