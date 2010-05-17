#include <fstream>
#include "../h/map.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/wall.h"
#include "boost/filesystem.hpp"

#define DEFAULT_VISIBILITY 150

namespace bf = boost::filesystem;

Box::Box()
{
	bounds.x = bounds.y = bounds.height = bounds.width = 0;
	objects[0].clear();
	objects[1].clear();
}
void Map::updateScreen( Graphic *g )
{
	SDL_Rect clip;
	SDL_GetClipRect(g->screen, &clip);
	Rectangle bounds(clip.x + boundaries.x,
		clip.y + boundaries.y,
		clip.w,
		clip.h);
	Position box;
	Position maxBox((bounds.x + bounds.width)/BOX_WIDTH+1,((bounds.y + bounds.height)/BOX_HEIGHT+1));
	if (maxBox.x > boxesInRow)
		maxBox.x = boxesInRow+1;
	if (maxBox.y > boxesInColumn)
		maxBox.y = boxesInColumn+1; //kvoli floatom

	for(box.x = bounds.x/BOX_WIDTH-1; box.x < maxBox.x; box.x++ )
	{
		if (box.x <0)
			continue;
		for(box.y = bounds.y/BOX_HEIGHT-1; box.y < maxBox.y; box.y++ )
		{
			if (box.y < 0)
				continue;
			std::list<Object *>::iterator iter = map[box.x][box.y].objects[processing].begin();
			while( iter != map[box.x][box.y].objects[processing].end() )
			{
				bool b = (*iter)->isMoving();
				bool c = (*iter)->changed();
				if (!( b || c ))
				{
					iter++;
					continue;
				}
				update(*iter,g);
				watch = *iter;
				iter++;
			}
		}
	}
}
bool Map::saveToFile(std::string filename)
{
	std::string saveInfo[NumberOfObjectToSave];
	std::ofstream output;
	if (!bf::exists("maps"))
		bf::create_directory("maps");
	std::string fln = "maps/" + filename;
	output.open(fln.c_str(), std::ios::out);
	if (!output.good())
	{
		TEST("cannot create file ")
		return false;
	}
		//resolution + visibility
	output << resolution << " " << visibility << "\n";
	for(int i = 0; i< boxesInRow; i++)
		for (int j =0; j < boxesInColumn; j++)
		{
			std::list<Object *>::iterator iter = map[i][j].objects[processing].begin();
			while (iter != map[i][j].objects[processing].end() )
			{
				saveInfo[(*iter)->objectSaveId]+=deconvert<Position>((*iter)->get_pos()) + "\n";
				iter++;
			}
		}
	for (std::list<Place>::iterator iter = places.begin();
		iter!= places.end();
		iter++)
	{
		saveInfo[iter->saveId] += deconvert<Position>(iter->r.getPos()) ; //no need for ide, it is sorted
	}
	for (int i =0; i<NumberOfObjectToSave; i++)
	{
		output << "#:-" <<i<< " " << saveInfo[i]<<std::endl;
	}
	output.close();
	return true;
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

	Position aa,b;
	if (a)
		o1->intersection(o2,aa,b);
	return a;
}
void Map::setShift(int x, int y)
{
	if (boundaries.x < 0)
		boundaries.width +=boundaries.x;
	if (boundaries.y < 0)
		boundaries.height +=boundaries.y;
	boundaries.x = x;
	boundaries.y = y;
	if (boundaries.x < 0)
		boundaries.width -=boundaries.x;
	if (boundaries.y < 0)
		boundaries.height -=boundaries.y;
}
Position Map::setBoundary(int x, int y)
{
	boundaries.width = min<int>(resolution.x,x);
	boundaries.height = min<int>(resolution.y,y);
	if (boundaries.x + boundaries.width > resolution.x)
		boundaries.x = resolution.x - boundaries.width;
	if (boundaries.y + boundaries.height > resolution.y)
		boundaries.y = resolution.y - boundaries.height;
	Position b(boundaries.width, boundaries.height);
	return b;
}
bool Map::load(Graphic * g, std::string filename)
{
	clean();

	std::ifstream input;
	input.open(filename.c_str(), std::ios::in);
	if (!input.good())
	{
		TEST(filename);
		return false;
	}
	//resolution change
	for (int i =0 ; i< boxesInRow; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	//skin netreba mazat, bo to mame ztial uplne stejne
	input.ignore(256,':');
	input >> resolution.x;
	input.ignore(256,':');
	input >> resolution.y;
	input >> visibility; //bez dvojbodky;
	create();
	Position objectPosition;
	input.ignore(256,':');
	char a;
	input >> a;
	input >> objectPosition.x; //prve zaporne
	int iter = 0;
	
	input.ignore(256,':');
	while (input >> objectPosition.x)
	{
		if (objectPosition.x < 0)
		{
			iter++;
			input.ignore(256,':');
			continue;
		}
		input.ignore(256,':');
		input >> objectPosition.y;
		Object * o = NULL;
		switch (iter)
		{
			case SaveWall:
				o = new Wall(wskins[WallSolidId], &abyss);
				break;
			case SavePushableWall:
				o = new PushableWall(wskins[WallPushId],&abyss);
				break;
			case SaveTrapWall:
				o = new TrapWall(wskins[WallTrapId],&abyss);
				break;
			case SaveStart:
				addStart(g,objectPosition.x,objectPosition.y);
				break;
			case SaveTarget:
				addTarget(g, objectPosition.x, objectPosition.y);
				break;
			default:
				TEST("Not implemented"<<iter << std::endl)
		}
		if (o!=NULL)
		{
			o->setPosition(objectPosition);
			add(o);
		}
		input.ignore(256,':');
	}
	//suppose the right structure
		
	input.close();
	return true;
}

void Map::create()
{
	boundaries.x = 0;
	boundaries.y = 0;
	boundaries.width = 0;
	boundaries.height = 0;

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
}

Map::Map(std::string skinName)
{
	commonInit(skinName);
}

void Map::commonInit(std::string skinName)
{
	watch = NULL;
	processing = 0;
	ticks = 30;
	time = 1;
	visibility = DEFAULT_VISIBILITY;
	map = NULL;
	boxesInRow = 0;
	boxesInColumn = 0;
	resolution.x = resolution.y = 0;

	wskins.clear();

	for (size_t i = 0; i< NumberObjectsImages; i++)
	{
		wskins.push_back( new WallSkin(skinName, i));
	}
}

Map::Map(Position resol, std::string skinName) 
{

	commonInit(skinName);

	resolution = resol;
	resolution.x +=  2*wskins[1]->get_shift().x;
	resolution.y +=  2*wskins[1]->get_shift().y;
	create();

	/* adding solid walls to ends */
	addBoundaryWalls();
}

void Map::addBoundaryWalls()
{
	Position p(wskins[1]->get_size().x,0);
	//X-ova os
	for (p.x = 0; p.x < resolution.x; p.x += wskins[1]->get_size().x)
	{
		p.y = 0;
		Wall * w1 = new Wall(wskins[1], &abyss);
		w1->setPosition(p,0);

		p.y = resolution.y - wskins[1]->get_shift().x;
		Wall * w2 = new Wall(wskins[1], &abyss);
		w2->setPosition(p,0);
		add(w1);
		add(w2);
	}	
	p.y = 0;
	for (p.y = 0; p.y < resolution.y; p.y += wskins[1]->get_size().y)
	{
		p.x = 0;
		Wall * w1 = new Wall(wskins[1], &abyss);
		w1->setPosition(p,0);
		p.x = resolution.x - wskins[1]->get_shift().x;
		Wall * w2 = new Wall(wskins[1], &abyss);
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

void Map::addStart(Graphic * g,size_t x, size_t y)
{
	if ((x > (size_t)resolution.x) || (y >(size_t) resolution.y))
		return;
	Rectangle r(x,y,wskins[WallStartId]->get_shift().x,
		wskins[WallStartId]->get_shift().y);
	std::list<Place>::reverse_iterator iter = places.rbegin();
	int i = -1;
	for (iter--; iter!=places.rend(); iter--) //prve nezadane
	{
		if (iter->id >=0)
			continue;
		if (iter->id!=i)
			break;
		i--;
	}
	Place pl;
	pl.saveId = SaveStart;
	pl.id = i;//zaporne cislo
	pl.r = r;
	pl.img = NULL;
	pl.numberImage = WallStartId;
	addPlace(g,pl);
}
std::list<Rectangle> Map::getStarts()
{
	std::list<Place>::iterator iter;
	std::list<Rectangle> toReturn;
	for(iter = places.begin(); iter!=places.end(); iter++)
	{
		if (iter->id < 0)
			toReturn.push_back(iter->r);
	}
	return toReturn;
}
void Map::addTarget(Graphic * g,size_t x, size_t y)
{
	if ((x > (size_t)resolution.x)||(y > (size_t)resolution.y))
		return;
	Rectangle r(x,y,wskins[TargetPlace]->get_shift().x,
		wskins[TargetPlace]->get_shift().y);

	std::list<Place>::iterator iter;
	int i = 0;
	for (iter = places.begin();iter!=places.end(); iter++) //prve nezadane
	{
		if (iter->id <0)
			continue;
		if (iter->id!=i)
			break;
		i++;
	}

	Place pl;
	pl.saveId = SaveTarget;
	pl.r = r;
	pl.numberImage = TargetPlace;
	pl.img = TTF_RenderText_Solid(g->g_font,deconvert<size_t>(i).c_str(), g->light);
	pl.id = i;
	addPlace(g,pl);
}
void Map::addPlace(Graphic * g, Place p)
{
	std::list<Place>::iterator iter;
	
	for (iter = places.begin();iter!=places.end(); iter++)
	{
		if (p.r.overlaps(iter->r))
		{
			TEST("position already set")
			return;
		}
	}
	for (iter = places.begin();iter!=places.end(); iter++)
		if(iter->id > p.id)
			break;

	places.insert(iter,p);
}
Position Map::size()const
{
	return resolution;
}
SDL_Rect Map::getBoundingRect(Object *o, Graphic*g)
{
	Position diff = o->get_old_pos().substractVector(o->get_pos());
	if (diff.x < 0)
		diff.x *=-1;
	if (diff.y < 0)
		diff.y *=-1;
	SDL_Rect r = o->get_rect();
	r.x = min<int> (o->get_old_pos().x, o->get_pos().x);
	r.y = min<int> (o->get_old_pos().y, o->get_pos().y);
	r.w += diff.x;
	r.h += diff.y;
	if (r.x +r.w > boundaries.x + boundaries.width)
		r.w = boundaries.x + boundaries.width - r.x;
	if (r.y +r.h > boundaries.y + boundaries.height)
		r.h = boundaries.y + boundaries.height - r.y;
	return r;
}
void Map::update(Object * o, Graphic * g)
{
	SDL_Rect r = getBoundingRect(o,g);
	r.x-=boundaries.x;
	if (r.x < 0)
		r.x = 0;
	r.y-=boundaries.y;
	if (r.y < 0)
		r.y = 0;
	update(r,true, g);
}

void Map::drawAll(Graphic * g)
{
	background(g);

	SDL_Rect clip;
	SDL_GetClipRect(g->screen, &clip);
	Rectangle bounds(clip.x + boundaries.x,
		clip.y + boundaries.y,
		clip.w,
		clip.h);
	for (std::list<Place>::iterator iter = places.begin(); 
		iter!= places.end(); 
		iter++)
	{
		if (bounds.overlaps(iter->r))
		{
			SDL_Rect r,r2;
			r.x = iter->r.x - boundaries.x;
			r.y = iter->r.y - boundaries.y;
			r2 = r;
			SDL_BlitSurface(wskins[iter->numberImage]->get_surface(0), NULL, g->screen, &r);
			if (iter->img) //odstranit? FIXME
				SDL_BlitSurface(iter->img, NULL, g->screen, &r2);
		}
	}
	draw(g);
}
void Map::redraw(Graphic * g)
{
	background(g);
	draw(g);
}
void Map::background(Graphic * g)
{	
	SDL_Rect clip;
	SDL_GetClipRect(g->screen, &clip);
	int startX = - (clip.x % (wskins[0]->get_size().x));
	int startY = - (clip.y % (wskins[0]->get_size().y));
	for (int x = startX; x < clip.w; x += wskins[0]->get_size().x) // pre tapety
	{
		for(int y = startY; y< clip.h; y+= wskins[0]->get_size().y) //FIXME kvoli rects, neskor opravti, minoritna vec, indent(x,y)
		{
			SDL_Rect r;
			r.x = x + clip.x;
			r.y = y + clip.y;

			SDL_BlitSurface(wskins[0]->get_surface(0),NULL, g->screen, &r);
		}
	}
}
void Map::draw(Graphic * g ) 
{
	ticks = (SDL_GetTicks() - time)%100 + 30;
	ticks = 30;
	time = SDL_GetTicks();
	Position pos;
	pos.x = boundaries.x > 0 ? boundaries.x/BOX_WIDTH:0;
	pos.y = boundaries.y > 0 ? boundaries.y/BOX_HEIGHT:0;
	Rectangle b = map[pos.x][pos.y].bounds;
	Position max(boundaries.x+boundaries.width, boundaries.y+boundaries.height);
	while ( b.x< max.x ) //prejde tolkokrat, kolko boxov sa zvisle zmesti
	{
		if (pos.x > boxesInRow)
			break;
		b = map[pos.x][pos.y].bounds; //FIXME tu by to vobec nemuselo byt
		while ( b.y < max.y )
		{
			if (pos.y > boxesInColumn)
				break;
			b = map[pos.x][pos.y].bounds;
			std::list<Object *>::iterator iter = map[pos.x][pos.y].objects[processing].begin();
			while( iter != map[pos.x][pos.y].objects[processing].end() )
			{
				SDL_Rect rects;
				rects.x = (*iter)->get_pos().x - boundaries.x;
				rects.y = (*iter)->get_pos().y - boundaries.y;
				SDL_Rect r = (*iter)->get_rect();
				SDL_BlitSurface((*iter)->show(),&r,g->screen, &rects);
				iter++;
			}
			iter = map[pos.x][pos.y].objects[1-processing].begin();
			while( iter != map[pos.x][pos.y].objects[1-processing].end() )
			{
				SDL_Rect rects;
				rects.x = (*iter)->get_pos().x - boundaries.x;
				rects.y = (*iter)->get_pos().y - boundaries.y;
				SDL_Rect r = (*iter)->get_rect();
				SDL_BlitSurface((*iter)->show(),&r,g->screen, &rects);
				iter++;
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
			std::list<Object *>::iterator iter = map[x][y].objects[processing].begin();
			while ( iter != map[x][y].objects[processing].end() )
			{
				checkNearest(o, *iter, nearest, nearestColObject);
				iter++;
			}
			iter = map[x][y].objects[1-processing].begin();
			while ( iter != map[x][y].objects[1-processing].end() )
			{
				checkNearest(o, *iter, nearest, nearestColObject);
				iter++;
			}
		}
	}	
	return nearestColObject;
}
void Map::checkNearest(Object * o, Object * objectInBox, size_t& nearest, Object *& nearestColObject )
{
	if (( objectInBox == NULL ) || ( o == objectInBox )|| (!objectInBox->alive()))
		return;
	if (!((o->substance + objectInBox->substance) 
				&& (collideWith(o, objectInBox))))
		return;
	size_t dist = o->get_old_pos().getDistance(objectInBox->get_pos());
	if (dist < nearest)	
	{
		nearestColObject = objectInBox;
		nearest = dist;
	}
}
bool Map::performe(Graphic * g)
{
	/* resolving he move action that happened */
	int processed = 1-processing;
	for ( size_t i = 0; i< boxesInRow; i++ )
		for (size_t j = 0; j< boxesInColumn; j++ )
		{
			while (!map[i][j].objects[processing].empty())
			{
				std::list<Object *>::iterator iter = map[i][j].objects[processing].begin();
				Object * o = *iter;
				Position p = o->get_pos();
				if (!o->alive())
				{
					map[i][j].objects[processing].erase(iter);
					o->dead();
					update(o,g);
					continue;
				}
				resolveMove(o);
				map[i][j].objects[processed].splice(map[p.x/BOX_WIDTH][p.y/BOX_HEIGHT].objects[processed].begin(),
						map[p.x/BOX_WIDTH][p.y/BOX_HEIGHT].objects[processing], iter);
			}
		}
	processing = processed;
	return false;
}
void Map::remove(Object * o)
{
	Position pos = o->get_pos();
	pos.x/=BOX_WIDTH;
	pos.y/=BOX_HEIGHT;
	map[pos.x][pos.y].objects[processing].remove(o);
	map[pos.x][pos.y].objects[1-processing].remove(o);//nevieme, kde to je FIXME
}

void Map::resolveBorders(Object *o ) 
{
	//TODO vobec by nmalo nastavat
	if (o->movement.position_in_map.x <0)
	{
		TEST("Pozicia objektu je mensia ako 0");
		//	o->movement.direction.x *= -1;
		o->movement.position_in_map.x = -1; //odrazene
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
	o->move(ticks);
	resolveBorders(o);
	Object * collidedWith= checkCollision(o);
	ObjectMovement muf;
	muf.position_in_map = Position( 1999,2000);
	while (collidedWith!=NULL)
	{
		o->hit(collidedWith);
		collidedWith= checkCollision(o);
		TEST("Pozicia po kolidovani:" << o->get_pos())
		muf = o->movement;
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
	map[pos.x][pos.y].objects[processing].push_back(o);
}
Object * Map::removeShow(Position position, bool all, Graphic * g)
{
	SDL_Rect r;
	r.x=-1;

	Object * o = removeAt(position, r);
	//osekat precnievajuce casti
	SDL_Rect clip;
	SDL_GetClipRect(g->screen, &clip);
	if (r.x < clip.x)
		r.x = clip.x;		
	if (r.y < clip.y )
		r.y = clip.y;
	if (r.x + r.w > clip.x + clip.w)
		r.w = clip.x + clip.w - r.x;
	if (r.y +r.h > clip.y + clip.h)
		r.h = clip.y + clip.h - r.h;
	update(r,true,g);
	return o;
}
void Map::update(SDL_Rect newBound, bool all, Graphic * g)
{
	SDL_Rect clip = newBound;

	SDL_SetClipRect(g->screen, &clip);
	drawAll(g);
	SDL_UpdateRect(g->screen,clip.x,clip.y,clip.w,clip.h);
	SDL_SetClipRect(g->screen, NULL);
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

			std::list<Object *>::iterator iter = map[boxP.x][boxP.y].objects[processing].begin();
			while( iter != map[boxP.x][boxP.y].objects[processing].end() )
			{
				Object * o = * iter;
				Rectangle r;
				r.width = o->get_rect().w; //to co blitujem
				r.height = o->get_rect().h;
				r.x = o->get_pos().x;
				r.y = o->get_pos().y;
				if (r.overlaps(removePos))
				{
					map[boxP.x][boxP.y].objects[processing].erase(iter);
					toBlit = o->get_rect();
					toBlit.x = r.x - boundaries.x;
					toBlit.y = r.y - boundaries.y;
					return o;
				}
				iter ++;
				o=*iter;
			}
		}
	}
	TEST("Object not found!"<<std::endl)
	//ci to nie je place alebo startPosition, popripade obe
	//FIXME
	for (std::list<Place>::iterator i = places.begin(); i!=places.end(); i++)
	{
		if (i->r.overlaps(removePos))
		{
			toBlit.x = i->r.x - boundaries.x;
			toBlit.y = i->r.y - boundaries.y;
			toBlit.w = i->r.width;
			toBlit.h = i->r.height;
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
			std::list<Object *>::iterator itr = map[i][j].objects[0].begin();
			while (itr != map[i][j].objects[0].end())
			{
				delete *itr;
				itr++;
			}
			itr = map[i][j].objects[1].begin();
			while (itr != map[i][j].objects[1].end())
			{
				delete *itr;
				itr++;
			}
			map[i][j].objects[0].clear();
			map[i][j].objects[1].clear();
		}
	places.clear();
	while(!abyss.empty())
	{
		delete *abyss.begin();
		abyss.erase(abyss.begin());
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
