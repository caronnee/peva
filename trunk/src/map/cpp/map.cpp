#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/wall.h"

//TODO externe si pamatat steny pre bezpecne odmonotvanie
Box::Box()
{
	bounds.x = bounds.y = bounds.height = bounds.width = 0;
	objects.clear();
}

Map::Map(std::string configFile, std::string name)
{
}

bool Map::collideWith( Object * o1, Object* o2 )
{
	Rectangle r1 = o1->collisionSize();
	r1.x += o1->get_pos().x;
	r1.y += o1->get_pos().y;

	Rectangle r2 = o2->collisionSize();
	r2.x += o2->get_pos().x; 
	r2.y += o2->get_pos().y;

	bool a = r1.overlaps(r2);

	return a;
}
void Map::setBoundary(int x, int y)
{
	boundaries.width = min<int>(resolution.x,x);
	boundaries.height = min<int>(resolution.y,y);
}
Map::Map(Position resol, std::string skinName) 
{
	boundaries.x = 0;
	boundaries.y = 0;
	boundaries.width = 0;
	boundaries.height = 0;
	wskins.clear();
	resolution = resol;
	skin = new Skin(skinName, Skin::MapSkin);
	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wskins.push_back( new WallSkin(skinName, i));
	}
	skinWork = new ImageSkinWork(skin);
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
	//X-ova os
	for (p.x = 0; p.x < resolution.x; p.x += wskins[1]->get_size().x)
	{
		p.y = 0;
		Wall * w1 = new Wall(wskins[1]);
		w1->setPosition(p,0);

		p.y = resolution.y - skin->get_shift().x;
		Wall * w2 = new Wall(wskins[1]);
		w2->setPosition(p,0);
		add(w1);
		add(w2);
	}	
	p.y = 0;
	for (p.y = 0; p.y < resolution.y; p.y += wskins[1]->get_size().y)
	{
		p.x = 0;
		Wall * w1 = new Wall(wskins[1]);
		w1->setPosition(p,0);
		p.x = resolution.x - skin->get_shift().x;
		Wall * w2 = new Wall(wskins[1]);
		w2->setPosition(p,0);
		add(w1);
		add(w2);
	}
}

void Map::shift(int shiftLeft, int shiftUp)
{
	boundaries.x += shiftLeft;
	boundaries.y += shiftUp;
}
void Map::addTarget(Window * w,size_t x, size_t y)
{
	Position p(x,y);
	size_t i = 0;
	std::list<Place>::iterator iter = places.begin();
	for (;iter!=places.end(); i++,iter++) //prve nezadane
		if (iter->id!=i)
			break;
	size_t id = i;
	Place pl;
	pl.id = id; 
	pl.p = p;
	pl.img = TTF_RenderText_Solid(w->g->g_font,deconvert<size_t>(id).c_str(), w->g->light);
	places.insert(iter,pl);
}
Position Map::size()const
{
	return resolution;
}
void Map::drawAll(Window * w)
{
	background(w);
	for (std::list<Position>::iterator i = starts.begin() ; i != starts.end(); i++)
	{
		if (boundaries.overlaps(*i))
		{
			SDL_Rect r;
			r.x = i->x - boundaries.x;
			r.y = i->y - boundaries.y;
			SDL_BlitSurface(wskins[WallStartId]->get_surface(0), NULL, w->g->screen, &r);
		}
	}

	for (std::list<Place>::iterator iter = places.begin(); iter!= places.end(); iter++)
	{
		if (boundaries.overlaps(iter->p))
		{
			SDL_Rect r;
			r.x = iter->p.x - boundaries.x;
			r.y = iter->p.y - boundaries.y;
			SDL_BlitSurface(wskins[TargetPlace]->get_surface(0), NULL, w->g->screen, &r);
			SDL_BlitSurface(iter->img, NULL, w->g->screen, &r);
		}
	}
	draw(w);
}
void Map::redraw(Window*w)
{
	background(w);
	draw(w);
}
void Map::background(Window * w)
{	
	SDL_Rect clip;
	SDL_GetClipRect(w->g->screen, &clip);
	for (int x = 0; x < boundaries.width; x+=skinWork->width()) // pre tapety
	{
		for(int y = 0; y< boundaries.height; y+=skinWork->height()) //FIXME kvoli rects, neskor opravti, minoritna vec, indent(x,y)
		{
			SDL_Rect r; //TODO nie takto natvrdlo
			r.x = x +clip.x;
			r.y = y +clip.y;

			SDL_Rect sr = skinWork->get_rect();
			SDL_BlitSurface(skin->get_surface(WallFree),&sr, w->g->screen, &r);
		}
	}
}
void Map::draw(Window * w ) //HA! tu mi uplne staci grafika a nie cele okno
{
	Position pos;
	pos.x = boundaries.x/BOX_WIDTH;
	pos.y = boundaries.y/BOX_HEIGHT;
	for (int i =0; i< boundaries.width; i += BOX_WIDTH) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		if (pos.x > boxesInRow)
			break;
		for(int j =0; j< boundaries.height; j += BOX_HEIGHT)
		{
			if (pos.y > boxesInColumn)
				break;
			map[pos.x][pos.y].objects.reset();
			Object * o = map[pos.x][pos.y].objects.read();
			while( o != NULL )
			{
				SDL_Rect rects;
				rects.x = o->get_pos().x - boundaries.x;
				rects.y = o->get_pos().y - boundaries.y;
				SDL_Rect r = o->get_rect();
				SDL_BlitSurface(o->show(),&r,w->g->screen, &rects);
				o = map[pos.x][pos.y].objects.read();
			}
			pos.y++;
		}
		pos.y = boundaries.y/BOX_HEIGHT;
		pos.x++;
	}
}

Object * Map::checkCollision(Object * o)
{	
	Position oldBox(o->movement.old_pos.x/BOX_WIDTH,o->movement.old_pos.y/BOX_HEIGHT);
	Position newBox(o->movement.position_in_map.x/BOX_WIDTH,o->movement.position_in_map.y/BOX_HEIGHT);
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
				if (( objectInBox == NULL ) || ( o == objectInBox )|| (!objectInBox->alive()))
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
	for ( size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			Box &b = map[i][j];
			Object * o = b.objects.read();
			while (o!=NULL)
			{
				if (!o->alive())
				{
					b.objects.remove();
					o->dead();
					o = b.objects.data->value;
					continue;
				}
				resolveMove(o);
				Position p = o->get_pos();
				b.objects.moveHead(map[p.x/BOX_WIDTH][p.y/BOX_HEIGHT].objects);
				o = b.objects.data->value;
			}
		}
	return false;
}
void Map::remove(Object * o)
{
	Position pos = o->get_pos();
	pos.x/=BOX_WIDTH;
	pos.y/=BOX_HEIGHT;
	map[pos.x][pos.y].objects.reset();
	Object *object = map[pos.x][pos.y].objects.read();
	while (object!=NULL)
	{
		if (object == o)
		{
			map[pos.x][pos.y].objects.remove();
			break;
		}
		object = map[pos.x][pos.y].objects.read();
	}
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
		TEST("Pozicia je y mensia ako 0" << o->movement.position_in_map);
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
	while (collidedWith!=NULL)
	{
		o->hit(collidedWith);
		collidedWith= checkCollision(o);
		TEST("Pozicia po kolidovani:" << o->get_pos())
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
	if ((pos.x > resolution.x) || (pos.y > resolution.y) ||(pos.x < 0) || (pos.y < 0))
		return;
	pos.x /= BOX_WIDTH;
	pos.y /= BOX_HEIGHT;
	map[pos.x][pos.y].objects.add(o->item);
}
Object * Map::removeShow(Position position, bool all, Window*w)
{
	SDL_Rect r;
	Object * o = removeAt(position, r);
	Rectangle oldBounds = boundaries;
	boundaries.x += r.x;
	boundaries.y += r.y;
	boundaries.width = r.w;
	boundaries.height = r.h;
	
	SDL_Rect clip = r;
	r.x = boundaries.x;
	r.y = boundaries.y;
	SDL_SetClipRect(w->g->screen, &clip);
	if (all)
	{
		background(w);
		draw(w);
	}
	else
		drawAll(w);
	SDL_SetClipRect(w->g->screen, NULL);
	SDL_UpdateRect(w->g->screen,boundaries.x,boundaries.y,boundaries.width,boundaries.height);
	boundaries = oldBounds;
	return o;
}
Object * Map::removeAt(Position position, SDL_Rect &toBlit)
{
	Position removePos(position);

	//posunutie oproti vyhladu
	removePos.x += boundaries.x;
	removePos.y += boundaries.y;

	Position boxP(removePos.x / BOX_WIDTH -1, removePos.y / BOX_HEIGHT -1);
	for (int i = 0; i <2; i++,boxP.x++)
	{
		boxP.y = removePos.y / BOX_HEIGHT -1;
		for (int j = 0; j <2; j++, boxP.y++)
		{
			//staci kontrolovat na box predtym, FIXME objekty vacsia ako box
			if ((boxP.y < 0)||(boxP.y > boxesInColumn)||(boxP.x < 0)|| (boxP.x>boxesInRow ))
				continue;

			map[boxP.x][boxP.y].objects.reset();
			Object * o = map[boxP.x][boxP.y].objects.read();
			while( o!=NULL )
			{
				Rectangle r = o->collisionSize();
				r.height += r.y;
				r.width += r.x;
				r.x = o->get_pos().x;
				r.y = o->get_pos().y;
				if (r.overlaps(position))
				{
					map[boxP.x][boxP.y].objects.remove();
					map[boxP.x][boxP.y].objects.reset();
					toBlit = o->get_rect();
					toBlit.x = r.x;
					toBlit.y = r.y;
					return o;
				}
				o = map[boxP.x][boxP.y].objects.read();
			}
		}
	}
	//TEST("Object not found!"<<std::endl)
	//ci to nie je place alebo startPosition, popripade obe
	//FIXME
	Rectangle r;
	r.width = 50;
	r.height = 50; //start area moze byt mala a ja si ju just budem fixovat:)
	for (std::list<Position>::iterator i = starts.begin(); i!=starts.end(); i++)
	{
		r.x = i->x;
		r.y = i->y;
		if (r.overlaps(position))
		{
			toBlit.x = r.x;
			toBlit.y = r.y;
			toBlit.w = r.width;
			toBlit.h = r.height;
			starts.erase(i);
			return NULL;
		}
	}
	for (std::list<Place>::iterator i = places.begin(); i!=places.end(); i++)
	{
		r.x = i->p.x;
		r.y = i->p.y;
		if (r.overlaps(position))
		{
			toBlit.x = r.x;
			toBlit.y = r.y;
			toBlit.w = r.width;
			toBlit.h = r.height;
			places.erase(i);
			return NULL;
		}
	}
	return NULL;
}
void Map::clean()
{
	for (size_t i =0; i< boxesInRow; i++)
		for(size_t j = 0; j< boxesInColumn; j++)
		{
			map[i][j].objects.reset();
			Object * o = map[i][j].objects.read();
			while (o!=NULL)
			{
				remove(o);
				delete o;
				o = map[i][j].objects.data->value;
			}
		}
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
