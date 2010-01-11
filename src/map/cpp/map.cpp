#include <math.h>
#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"

//TODO externe si pamatat steny pre bezpecne odmonotvanie
Box::Box()
{
	bounds.x = bounds.y = bounds.height = bounds.width = 0;
	objects.clear();
}
Map::Map(std::string configFile, std::string name)
{
}
Map::Map(Position resol, std::string skinName) 
{
	wskins.clear();
	skin = new Skin(skinName, Skin::MapSkin);
	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wskins.push_back( new WallSkin(skinName, i));
	}
	skinWork = new ImageSkinWork(skin);
	resolution = resol; 
	resolution.x +=  2*skin->get_shift().x;
	resolution.y +=  2*skin->get_shift().y;
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
	/* adding solid walls to ends */
	Position p(skin->get_size().x,0);
	ObjectMovement movement;
	movement.speed = 0;
	movement.direction = Position(0,0);
	movement.angle = 0;
	movement.old_pos = movement.position_in_map = p;
	int a = 0;
	while (p.x < resolution.x - wskins[1]->get_size().x)
	{
		a++;
		p.y = 0;
		Wall * w1 = new Wall(p, wskins[1]);
		p.y = resol.y + wskins[1]->get_size().y; //povodne resol;
		Wall * w2 = new Wall(p, wskins[1]);
		add(w1);
		add(w2);
		p.x += skin->get_size().x;
	}	
	int tmp = p.x;
	std::cout << "Preslo " << a << "-krat";
	p.y = 0;
	while (p.y < resolution.y)
	{
		p.x = 0;
		Wall * w1 = new Wall(p, wskins[1]);
		p.x = tmp;
		Wall * w2 = new Wall(p, wskins[1]);
		p.y += skin->get_size().y;
		add(w1);
		add(w2);
	}
}

void Map::redraw(Window * w, Position begin_draw_at) 
{
	std::cout << "begin ...";
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	Position pos(begin_draw_at);
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = resolution.x; 
	clip.h = resolution.y;
//	getc(stdin);
	SDL_SetClipRect(w->g->screen, &clip);
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
	int a = 0;
	for (int i =0; i< resoldraw.x; i+=BOX_WIDTH) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		for(int j =0; j< resoldraw.y; j+= BOX_HEIGHT)
		{
			map[pos.x][pos.y].objects.reset();
			Object * o = map[pos.x][pos.y].objects.read();
			while(o!=NULL)
			{
				a++;
				SDL_Rect rects;
				rects.x = o->get_pos().x - begin_draw_at.x;
				rects.y = o->get_pos().y - begin_draw_at.y;
				SDL_Rect r = o->get_rect();
			//	std::cout << rects.x << " " << rects.y << rects.w << " " << rects.h << std::endl;
				SDL_BlitSurface(o->show(),&r,w->g->screen, &rects);
				o = map[pos.x][pos.y].objects.read();
			}
			pos.y++;
		}
		r.y = 0;
		pos.y = begin_draw_at.y;
		pos.x++;
	}
	SDL_SetClipRect(w->g->screen, NULL);
	std::cout << "end"<<std::endl;
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
	Object * nearestColObject = NULL;
	size_t nearest = 0;
	//budem pocitat zatial s tym, ze rychlosti nebudu moc velike a nebude moc telies tan
	for (int x = min(oldBox.x,newBox.x); x<=max(newBox.x,oldBox.x); x++)
	{
		for (int y =min(oldBox.y,newBox.y); y <= max(newBox.y,oldBox.y); y++)
		{
			Box & b = map[x][y];
			Position colVector;
			/* no need to reset */
			for (size_t i = 0; i<b.objects.size(); i++)
			{
				//TODO dat to do samostatnej funkcie
				Object * objectInBox = b.objects.read();			
				if (( objectInBox == NULL ) || ( o == objectInBox ))
					continue;

				if ((o->collideWith(objectInBox, colVector)) //ak skoliduje, budeme predpokladat, ze spravne
				&&(getDistance(objectInBox, o) < nearest))	
				{
					nearestColObject = objectInBox;
				}		
			}
		}
	}	
	return nearestColObject;
}
//TODO dat to do position?
size_t Map::getDistance(Object * o1, Object * o2)
{
	Position pos = o1->get_pos().substractVector(o2->get_pos());
	return pos.x*pos.x+pos.y*pos.y; //su to dostatocne male cisla, aby sa to sem voslo
}

void Map::performe()
{
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
			map[i][j].objects.reset();

	/* resolving he move action that happened */
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			Box &b = map[i][j];
			std::cout << "-" << i << "," <<j <<":"<<b.objects.size()<<"-"<<std::endl;
			Object * o = b.objects.read();
			while (o!=NULL)
			{
				if (!o->alive())
				{
					b.objects.remove(b.objects.data);
					o->dead();
					o = b.objects.data->value;
					continue;
				}
				resolveMove(o);
				Position p = o->get_pos();
				b.objects.moveHead(map[p.x/BOX_WIDTH][p.y/BOX_HEIGHT].objects);
				o = b.objects.data->value;
				usleep(50);
			}
		}
		std::cout <<std::endl;
	//	sleep(1);
}
void Map::resolveBorders(Object *o ) //TODO zmazat, budu tam solid steny, ak tak sa o to ma postarat object
{
	if (o->movement.position_in_map.x <0)
	{
		std::cout << 1;
		getc(stdin);
	//	o->movement.direction.x *= -1;
		o->movement.position_in_map.x = -1; //odrazene
		//TODO doplnit na checkovanie kolizii kvli lamaniu ciary
	}
	else if (o->movement.position_in_map.x > resolution.x-o->width())
	{
		std::cout << 1;
		getc(stdin);
	//	o->movement.direction.x *= -1;
//		o->movement.position_in_map.x = 2*(resolution.x-o->width()) - o->movement.position_in_map.x;
		o->movement.position_in_map.x = resolution.x - o->width(); //odrazene
	}
	if (o->movement.position_in_map.y < 0)
	{
		std::cout << 1;
		getc(stdin);
	//	o->movement.direction.y *= -1;
//		o->movement.position_in_map.y *= -1;
		o->movement.position_in_map.y = 0; //odrazene
	}
	else if(o->movement.position_in_map.y > resolution.y-o->height())
	{
		std::cout << 1;
		getc(stdin);
	//	o->movement.direction.y *= -1;
	//	o->movement.position_in_map.y = 2*(resolution.y - o->height()) - o->movement.position_in_map.y;
		o->movement.position_in_map.y = resolution.y - o->height(); //odrazene
	}
}
void Map::resolveMove(Object * o)
{
	if (o->blocksMove()) 
	{
		return;
	}
	/* move, actually */
	o->move();
	resolveBorders(o);
	Object *collidedWith = checkCollision(o);
	if (collidedWith!=NULL)
	{
		//TODO vypocitaj vektor, zblazni sa
		std::cout << "Kollidujem!";
		getc(stdin);
	}
}

void Map::add(Object * o)
{
	if (o == NULL)
	{
		std::cout << "Error! null object!"; 
		getc(stdin); 
	}
	Position pos= o->get_pos();
	pos.x /= BOX_WIDTH;
	pos.y /= BOX_HEIGHT;
	map[pos.x][pos.y].objects.add(o->item);
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
