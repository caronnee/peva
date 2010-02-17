#include <math.h>
#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

//TODO externe si pamatat steny pre bezpecne odmonotvanie
Box::Box()
{
	bounds.x = bounds.y = bounds.height = bounds.width = 0;
	objects.clear();
}
Map::Map(std::string configFile, std::string name)
{
}

bool Map::collideWith( Object * o1, Object* o2 ) // pouzitelne iba pre vzajomne walls, zatial
{
	Rectangle r1 = o1->collisionSize();
	r1.x += o1->movement.position_in_map.x;
	r1.y += o1->movement.position_in_map.y;

	Rectangle r2 = o2->collisionSize();
	r2.x += o2->get_pos().x; 
	r2.y += o2->get_pos().y;

	bool a =r1.overlaps(r2);
	if (a)
	{
		std::cout <<" overlaplo!"<< std::endl;
		TEST(r1.x << ":" << r2.x << std::endl << r1.width << ":" <<r2.width)
	}
	return  (a);
}
void Map::setBoundary(size_t x, size_t y)
{
	boundaries.width = x + wskins[1]->get_size().x;
	boundaries.height = y+ wskins[1]->get_size().y;;
}
Map::Map(Position resol, std::string skinName) 
{
	boundaries.x = 0;
	boundaries.y = 0;
	boundaries.width = 0;
	boundaries.height = 0;
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
	//X-ova os
	for (p.x = skin->get_size().x; p.x < resolution.x; p.x += wskins[1]->get_size().x)
	{
		a++;
		p.y = 0;
		Wall * w1 = new Wall(wskins[1]);
		w1->setPosition(p,0);

		p.y = resol.y + wskins[1]->get_size().y; //povodne resol;
		Wall * w2 = new Wall(wskins[1]);
		w2->setPosition(p,0);
		add(w1);
		add(w2);
	}	
	a = 0;
	p.y = 0;
	for (p.y = 0; p.y < resolution.y; p.y += wskins[1]->get_size().y)
	{
		a++;
		p.x = 0;
		Wall * w1 = new Wall(wskins[1]);
		w1->setPosition(p,0);
		p.x = resolution.x-wskins[1]->get_size().x;
		Wall * w2 = new Wall(wskins[1]);
		w2->setPosition(p,0);
		add(w1);
		add(w2);
	}
}

void Map::shift(int shiftLeft, int shiftUp)
{
	boundaries.x +=shiftLeft;
	boundaries.y += shiftUp;
}
void Map::addTarget(size_t x, size_t y)
{
	Position p(x,y);
	size_t id = places.size();
	Place pl;
	pl.id = id; 
	pl.p = p;
}
void Map::redraw(Window * w ) 
{
	SDL_Rect r; //TODO nie takto natvrdlo
	r.x = 0;
	r.y = 0;
	Position pos;
	pos.x = boundaries.x/BOX_WIDTH;
	pos.y = boundaries.y/BOX_HEIGHT;
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = resolution.x; 
	clip.h = resolution.y;
	SDL_SetClipRect(w->g->screen, &clip);
	for (int i =0; i< boundaries.width; i+=skin->get_size().x) // pre tapety
	{
		for(int j =0; j< boundaries.height; j+=skin->get_size().y)
		{
			SDL_Rect sr = skinWork->get_rect();
			SDL_BlitSurface(skin->get_surface(WallFree),&sr, w->g->screen, &r);
			r.y+=skin->get_size().y;
		}
		r.y = 0;
		r.x+=skin->get_size().x;
	}
	int a = 0;
	for (int i =0; i< boundaries.width; i+=BOX_WIDTH) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		for(int j =0; j< boundaries.height; j+= BOX_HEIGHT)
		{
			map[pos.x][pos.y].objects.reset();
			Object * o = map[pos.x][pos.y].objects.read();
			while(o!=NULL)
			{
				a++;
				SDL_Rect rects;
				rects.x = o->get_pos().x - boundaries.x;
				rects.y = o->get_pos().y - boundaries.y;
				SDL_Rect r = o->get_rect();
				SDL_BlitSurface(o->show(),&r,w->g->screen, &rects);
				o = map[pos.x][pos.y].objects.read();
			}
			pos.y++;
		}
		r.y = 0;
		pos.y = boundaries.y/BOX_HEIGHT;
		pos.x++;
	}
	SDL_SetClipRect(w->g->screen, NULL);
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
Object * Map::checkCollision(Object * o)
{	
	Position oldBox(o->movement.old_pos.x/BOX_WIDTH,o->movement.old_pos.y/BOX_HEIGHT);
	Position newBox(o->movement.position_in_map.x/BOX_WIDTH,o->movement.position_in_map.y/BOX_HEIGHT);
	//TODO spravt nearest
	Object * nearestColObject = NULL;
	size_t nearest = MY_INFINITY;

	//budem pocitat zatial s tym, ze rychlosti nebudu moc velike a nebude moc telies tan
	for (int x = min(oldBox.x,newBox.x)-1; x<=max(newBox.x,oldBox.x)+1; x++) //staci -1, bo ideme od minima
	{
		if ((x == -1)||(x>boxesInRow))
			continue;
		for (int y =min(oldBox.y,newBox.y)-1; y <= max(newBox.y,oldBox.y)+1; y++)
		{
			if ((y == -1)||(y > boxesInColumn))
				continue;
			Box & b = map[x][y];
			/* no need to reset */
			for (size_t i = 0; i<b.objects.size(); i++)
			{
				//TODO dat to do samostatnej funkcie
				Object * objectInBox = b.objects.read();			
				if (( objectInBox == NULL ) || ( o == objectInBox ))
					continue;
				if (!((o->substance + objectInBox->substance) 
					&& (collideWith(o, objectInBox))))
					continue;
				size_t dist = o->get_old_pos().getDistance(objectInBox->get_pos());
				if (dist < nearest)	
				{
					nearestColObject = objectInBox;
					nearest = dist;
				}		
			}
		}
	}	
	return nearestColObject;
}

bool Map::performe()
{
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
			map[i][j].objects.reset();

	/* resolving he move action that happened */
	for (size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			Box &b = map[i][j];
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
	return false;
}
void Map::resolveBorders(Object *o ) //TODO zmazat, budu tam solid steny, ak tak sa o to ma postarat object
{
	//TODO vobec by nmalo nastavat
	if (o->movement.position_in_map.x <0)
	{
		TEST("Pozicia objektu je mensia ako 0");
	//	o->movement.direction.x *= -1;
		o->movement.position_in_map.x = -1; //odrazene
		//TODO doplnit na checkovanie kolizii kvli lamaniu ciary
	}
	else if (o->movement.position_in_map.x > resolution.x-(int)o->width())
	{
		TEST("Pozicia objektu je viac ako maximum");
	//	o->movement.direction.x *= -1;
//		o->movement.position_in_map.x = 2*(resolution.x-o->width()) - o->movement.position_in_map.x;
		o->movement.position_in_map.x = resolution.x - o->width(); //odrazene
	}
	if (o->movement.position_in_map.y < 0)
	{
		TEST("Pozicia je y mensia ako 0");
	//	o->movement.direction.y *= -1;
//		o->movement.position_in_map.y *= -1;
		o->movement.position_in_map.y = 0; //odrazene
	}
	else if(o->movement.position_in_map.y > resolution.y-(int)o->height())
	{
		TEST("pozicia y vacsia ako max");
	//	o->movement.direction.y *= -1;
	//	o->movement.position_in_map.y = 2*(resolution.y - o->height()) - o->movement.position_in_map.y;
		o->movement.position_in_map.y = resolution.y - o->height(); //odrazene
	}
}
/* Only for moving object */
void Map::resolveMove(Object * o)
{
	if (o->blocksMove()) 
	{
		return;
	}
	/* move, actually */
	o->move();
	resolveBorders(o);
	Object * collidedWith= checkCollision(o);
	if (collidedWith!=NULL)
	{
		o->hit(collidedWith);
	}
}

void Map::add(Object * o)
{
	if (o == NULL)
	{
		TEST("Error! null object!"); 
		return;
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
