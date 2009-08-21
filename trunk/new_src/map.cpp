#include "map.h"
#include <math.h>

//width of box in pixels
#define BOX_WIDTH 500
//height of box in pixels
#define BOX_HEIGHT 500

Box::Box(Rectangle rect)
{
	bounds = rect;
}

Map::Map(Position resol) //map resolution in pixels
{
	resolution = resol; 
	float boxesInRow = resolution.x/ BOX_WIDTH; 
	float boxesInColumn = resolution.y/ BOX_HEIGHT; 
	Rectangle begin(0,0,BOX_WIDTH,BOX_HEIGHT);
	map = new Box **[(int)boxesInRow +1 ];
	for(int i = 0; i < boxesInRow; i++) //tolko framov vytvorime v x osi
	{
		map[i] = new Box * [(int)boxesInColumn + 1]; //+1 because of real numbers
		for(int j = 0; j < boxesInColumn; j++)
		{
			map[i][j] = new Box(begin);
			begin.y+= BOX_HEIGHT;	
		}
		begin.x+=BOX_HEIGHT;
		begin.y = 0;
	}
	// boxes created
}

void Map::redraw(Window * w) 
{
	//vytapetuj to naskor prazdnymi tilom
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	Position pos(begin_draw_at);
	for (int i =0; i< resolution.x; i++)
	{
		for(int j =0; j< resolution.y; j++)
		{
			SDL_BlitSurface(m.tiles[FreeTile],NULL, w->g->screen, &r);
			r.y+=IMG_HEIGHT;
		}
		r.y = 0;
		r.x+=IMG_WIDTH;
	}

	//zacinaju sa vykreslovat objekty na viditelnej ploche
	for (int i =0; i< w->g->screen->w; i+=BOX_HEIGHT) //prejde tolkokrat, kolko boxon sa zvisle zmesti
	{
		for(int j =0; j< w->g->screen->w; j+= BOX_WIDTH)
		{
			std::list<Object *>::iterator iter = map[pos.x][pos.y]->objects.begin();
			while(iter != map[pos.x][pos.y]->objects.end())
			{
				Object * o = *iter;
				iter++;
				if(o!=NULL)
				{
					SDL_Rect rects;
					rects.x = o->position_in_map.x - begin_draw_at.x;
				       rects.y = o->position_in_map.y - begin_draw_at.y;
					SDL_BlitSurface(o->show(),NULL,w->g->screen, &rects);
				}
				pos.y++;
				r.y+=IMG_HEIGHT;
			}
		}
		r.y = 0;
		pos.y = begin_draw_at.y;
		pos.x++;
		r.x+=IMG_WIDTH;
		r.x = 0;
	}
	SDL_Flip(w->g->screen);
}

void Map::collision(Object* o1, Object *o2) //utocnik, obranca
{
/*	if (o1->attack > o2->defense)
	{
		o2->damage-=o1->attack;
	}
	else
	{
		o1->defense;
	}
	*/
}
void Map::move(Object * o)
{
	//TODO
}
void Map::update(Window * w, Position p)
{
/*	Position pos(p.x-1,p.y-1);	
	SDL_Rect r;
	for (int i =0; i<=2; i++)
	{
		for (int j =0; j<=2; j++)
		{
			SDL_BlitSurface(m.tiles[FreeTile],NULL,w->g->screen, &r);
		}
	}
	for (int i =-1; i<=1; i++)
	{
		for (int j =-1; j<=1; j++)
		{
			SDL_BlitSurface(map[x.x][y.y],NULL,w->g->screen, &r);
		}
	}*/
}

Map::~Map() 
{
	for(int i = 0; i< resolution.x; i++)
	{
		for(int j =0; j< resolution.y; j++)
			delete map[i][j];
		delete [] map[i];
	}
	delete map;
}
