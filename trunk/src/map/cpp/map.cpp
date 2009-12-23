#include <math.h>
#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"

//width of box in pixels
#define BOX_WIDTH 100
//height of box in pixels
#define BOX_HEIGHT 100

Box::Box()
{
	bounds.x = bounds.y = bounds.height = bounds.width = 0;
	objects.clear();
}

Map::Map(Position resol, std::string skinName) 
{
	skin = new Skin(skinName, Skin::MapSkin);
	skinWork = new ImageSkinWork(skin);
	resolution = resol; 
	boxesInRow = (float)resolution.x/ BOX_WIDTH; 
	boxesInColumn = (float)resolution.y/ BOX_HEIGHT; 
	Rectangle begin(0,0,BOX_WIDTH,BOX_HEIGHT);
	map = new Box *[(int)boxesInRow +1 ];
	for(int i = 0; i < boxesInRow; i++) 
	{
		/* +1 because of real numbers */
		map[i] = new Box [(int)boxesInColumn + 1]; 
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
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	Position pos(begin_draw_at);
	for (int i =0; i< w->g->screen->w; i+=skin->get_size().x) // pre tapety
	{
		for(int j =0; j< w->g->screen->h; j+=skin->get_size().y)
		{
			SDL_Rect sr = skinWork->get_rect();
			SDL_BlitSurface(skin->get_surface(WallFree),&sr, w->g->screen, &r);
			r.y+=skin->get_size().y;
		}
		r.y = 0;
		r.x+=skin->get_size().x;
	}
	Position resoldraw(min(w->g->screen->w,resolution.x),min(w->g->screen->h, resolution.y)); //TODO predsa to nebudem pocitat kazdy krat!
	for (int i =0; i< resoldraw.x; i+=BOX_WIDTH) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		for(int j =0; j< resoldraw.y; j+= BOX_HEIGHT)
		{
			map[pos.x][pos.y].objects.reset();
			Object * o = map[pos.x][pos.y].objects.read();
			while(o!=NULL)
			{
				std::cout << "HA!";
				getc(stdin);
				SDL_Rect rects;
				rects.x = o->get_pos().x - begin_draw_at.x;
				rects.y = o->get_pos().y - begin_draw_at.y;
				SDL_Rect r = o->get_rect();
				SDL_BlitSurface(o->show(),&r,w->g->screen, &rects);
				o = map[pos.x][pos.y].objects.read();
			}
			pos.y++;
		}
		r.y = 0;
		pos.y = begin_draw_at.y;
		pos.x++;
	}
}

void Map::collision(Object* o1, Object *o2) //utocnik, obranca
{
/*	if (o1->attack > o2->defense)
	{d
		o2->damage-=o1->attack;
	}
	else
	{
		o1->defense;
	}
	*/
}
Object * Map::checkCollision(Object * o)
{	
	//	pre kazdy roh sa pozri, akom je boxe. Ak rozny, checkuj kolizi pre kazdy objekt v boxe s useckou (A,B)
	//	vieme urcite, ze dalsi boc bude vedlajsi z velkosti boxi a z maximu pohyby za sekund
	Position oldBox(o->movement.old_pos.x/BOX_WIDTH,o->movement.old_pos.y/BOX_HEIGHT);
	Position newBox(o->movement.position_in_map.x/BOX_WIDTH,o->movement.position_in_map.y/BOX_HEIGHT);
	//TODO spravt nearest
	for (int x = oldBox.x; x<=newBox.x; x++)
	{
		for (int y =oldBox.y; y <= newBox.y; y++)
		{
			Box & b = map[x][y];
			Position colVector;
			/* no need to reset */
			for (size_t i = 0; i<b.objects.size(); i++)
			{
				Object * objectInBox = b.objects.read();			
				if (( objectInBox == NULL ) || ( o == objectInBox ))
					continue;
				if (o->collideWith(objectInBox, colVector)) //ak skoliduje, budeme predpokladat, ze spravne
					{
						objectInBox->collision(colVector);
						//			iter = b->objects.begin();
					}		
				//		else
			}
		}
	}	
	return NULL;
}

void Map::performe()
{
	/* resolving he move action that happened */
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			Box &b = map[i][j];
			Object * o = b.objects.read();
			while (o!=NULL)
			{
				resolveMove(o);
				Position p = o->get_pos();
				b.objects.moveHead(map[p.x/BOX_WIDTH][p.y/BOX_HEIGHT].objects);
				o = b.objects.data->value;
			}
		}
	//for all boxes, do action
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			Box &b = map[i][j];
			b.objects.reset();
			Object * o = b.objects.read();
			while (o!=NULL)
			{
				o->action(); //scheduller je v tom
				o = b.objects.read();
			}
			b.objects.reset();
			for(size_t i =0; i< b.objects.size(); i++)
				{
					std::cout<<b.objects.read()<< "_";
				}
				std::cout<<std::endl;
		}
}
void Map::resolveBorders(Object *o ) //TODO zmazat, budu tam solid steny, ak tak sa o to ma postarat object
{
	if (o->movement.position_in_map.x <0)
	{
	//	o->movement.direction.x *= -1;
		o->movement.position_in_map.x = -1; //odrazene
		//TODO doplnit na checkovanie kolizii kvli lamaniu ciary
	}
	else if (o->movement.position_in_map.x > resolution.x-o->width())
	{
	//	o->movement.direction.x *= -1;
//		o->movement.position_in_map.x = 2*(resolution.x-o->width()) - o->movement.position_in_map.x;
		o->movement.position_in_map.x = resolution.x - o->width(); //odrazene
	}
	if (o->movement.position_in_map.y < 0)
	{
	//	o->movement.direction.y *= -1;
//		o->movement.position_in_map.y *= -1;
		o->movement.position_in_map.y = 0; //odrazene
	}
	else if(o->movement.position_in_map.y > resolution.y-o->height())
	{
	//	o->movement.direction.y *= -1;
	//	o->movement.position_in_map.y = 2*(resolution.y - o->height()) - o->movement.position_in_map.y;
		o->movement.position_in_map.y = resolution.y - o->height(); //odrazene
	}
}
void Map::resolveMove(Object * o)
{
	if (!(o->isMoving())) //pokial je mrtvy, tak je taky nemoving
		return;
	/* move, actually */
	o->move();
	resolveBorders(o);
	Object *collidedWith = checkCollision(o);
	if (collidedWith!=NULL)
	{
		//TODO vypocitaj vektor, zblazni sa
	}
}

void Map::add(Object * o)
{
	 if (o == NULL)
	 {
		 std::cout << "ERROR! null object!"; 
		 getc(stdin); 
	 }
	Position pos= o->get_pos();
	pos.x /= BOX_WIDTH;
	pos.y /= BOX_HEIGHT;
	map[pos.x][pos.y].objects.add(o);
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