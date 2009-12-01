#include <math.h>
#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"

//width of box in pixels
#define BOX_WIDTH 500
//height of box in pixels
#define BOX_HEIGHT 500

Box::Box()
{
	objects.clear();
}

Map::Map(Position resol, std::string skinName) //map resolution in pixels + maap lookout
{
	skin = new Skin(skinName, Skin::MapSkin);
	std::cout << "Konstruktor mapy" << resol << std::endl;
	resolution = resol; 
	float boxesInRow = (float)resolution.x/ BOX_WIDTH; 
	float boxesInColumn = (float)resolution.y/ BOX_HEIGHT; 
	Rectangle begin(0,0,BOX_WIDTH,BOX_HEIGHT);
	map = new Box *[(int)boxesInRow +1 ];
//	std::cout << boxesInRow << "grgrgrg" << boxesInColumn << std::endl;
	for(int i = 0; i < boxesInRow; i++) //tolko framov vytvorime v x osi
	{
		map[i] = new Box [(int)boxesInColumn + 1]; //+1 because of real numbers
		for(int j = 0; j < boxesInColumn; j++)
		{
			map[i][j].bounds = begin;
			begin.y+= BOX_HEIGHT;	
		}
		begin.x+=BOX_HEIGHT;
		begin.y = 0;
	}
	//TODO solid steny na koncoch
}

void Map::redraw(Window * w, Position begin_draw_at) 
{
//vytapetuj to naskor prazdnymi tilom
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	Position pos(begin_draw_at);
	for (int i =0; i< w->g->screen->w; i+=skin->get_size().x)
	{
		for(int j =0; j< w->g->screen->h; j+=skin->get_size().y)
		{
		//	SDL_BlitSurface(m.tiles[FreeTile],NULL, w->g->screen, &r);
			r.y+=skin->get_size().y;
		}
		r.y = 0;
		r.x+=skin->get_size().x;
	}
	Position resoldraw(min(w->g->screen->w,resolution.x),min(w->g->screen->h, resolution.y)); //TODO predsa to nebudem pocitat kazdy krat!
//	std::cout << "zacina vykreslovanie objektov" << std::endl;
//getc(stdin);
//zacinaju sa vykreslovat objekty na viditelnej ploche
	for (int i =0; i< resoldraw.x; i+=BOX_WIDTH) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		for(int j =0; j< resoldraw.y; j+= BOX_HEIGHT)
		{
//	std::cout << "huhu"<< pos << std::endl;
//getc(stdin);
		/*	if (map[pos.x][pos.y]->objects.empty())
			{
				std::cout << "wdygvure" <<std::endl;
			}
			else std::cout << "not empty"<< map[pos.x][pos.y]->objects.size() << std::endl;
//	getc(stdin);
		*/
			std::list<Object *>::iterator iter = map[pos.x][pos.y].objects.begin();
//	std::cout << pos << w->g->screen->w << w->g->screen->h<<std::endl;
//	getc(stdin);
			while(iter != map[pos.x][pos.y].objects.end())
			{
//			std::cout << "HE??" << std::endl;
				Object * o = (*iter);
//			std::cout << "goin";
//				getc(stdin);
				iter++;
				if(o!=NULL)
				{
					SDL_Rect rects;
					rects.x = o->get_pos().x - begin_draw_at.x;
					rects.y = o->get_pos().y - begin_draw_at.y;
					SDL_BlitSurface(o->show(),NULL,w->g->screen, &rects);
				}
//		pos.y++;
//		r.y+=skin->get_size().y;
			}
		}
		r.y = 0;
		pos.y = begin_draw_at.y;
		pos.x++;
//	r.x+=skin->get_size().x;
//	r.x = 0;
	}
	SDL_Flip(w->g->screen);
//	std::cout << "end";
//getc(stdin);
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
void Map::move(ObjectMovement& move , Object * o) //TODO vracat position
{
	if ((o->movement.direction.x == 0)&&(o->movement.direction.y ==0))
		return;
	if (o->movement.position_in_map.x < 0)
	{
	//	std::cout << o->movement.position_in_map << std::endl;
	//	getc(stdin);
		o->movement.direction.x *= -1;
		o->movement.position_in_map.x *= -1;
		o->movement.position_in_map.x = o->movement.position_in_map.x;
	//	std::cout << o->movement.position_in_map << std::endl;
	//	getc(stdin);
		//TODO doplnit na checkovanie kolizii kvli lamaniu ciary
	}
	else if (o->movement.position_in_map.x > resolution.x-o->show()->w)
	{
		o->movement.direction.x *= -1;
		o->movement.position_in_map.x = 2*(resolution.x-o->show()->w) - o->movement.position_in_map.x;
	}
	if (o->movement.position_in_map.y < 0)
	{
		o->movement.direction.y *= -1;
		o->movement.position_in_map.y *= -1;
	}
	else if(o->movement.position_in_map.y > resolution.y-o->show()->h)
	{
		o->movement.direction.y *= -1;
		o->movement.position_in_map.y = 2*(resolution.y - o->show()->h) - o->movement.position_in_map.y;
	}
//	pre kazdy roh sa pozri, akom je boxe. Ak rozny, checkuj kolizi pre kazdy objekt v boxe s useckou (A,B)
//	vieme urcite, ze dalsi boc bude vedlajsi z velkosti boxi a z maximu pohyby za sekundu
	Position oldBox(move.old_pos.x/BOX_WIDTH,move.old_pos.y/BOX_HEIGHT);
	Position newBox(move.position_in_map.x/BOX_WIDTH,move.position_in_map.y/BOX_HEIGHT);
	if(oldBox != newBox) //checkni pre kolizie aj ostatne
	{
		std::cout << "TODO" << std::endl;
	}
	//pre vsetky v tej povodnej, ci sa nam to skolidovalo
	Box b = map[oldBox.x][oldBox.y];
	Object * nearest = NULL; //TODO kontrola, ci to fakt je nutne
	float dist = BOX_WIDTH*BOX_HEIGHT; //nekonecno
	Position colVector;
	std::list<Object *>::iterator iter = b.objects.begin();
	while (iter!=b.objects.end())
	{
		if ( o != (* iter))

			if (o->collideWith(*iter, colVector)) //ak skoliduje, budeme predpokladat, ze spravne
			{
				(*iter)->collision(colVector);
				//			iter = b->objects.begin();
			}		
		//		else
		iter++;
	}
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

void Map::add(Object * o)
{
	Position pos= o->get_pos();
	pos.x /=BOX_WIDTH;
	pos.y /=BOX_HEIGHT;
	map[pos.x][pos.y].objects.push_back(o);
	std::cout << "added to" << pos << std::endl;
}

Map::~Map() 
{
	
	float boxesInRow = (float)resolution.x/ BOX_WIDTH; 
	for(int i = 0; i< boxesInRow; i++)
	{
		delete [] map[i];
	}
	delete map;
}
