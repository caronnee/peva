//TODO namiesto makier pouzit nieco schopnejsie
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <fstream>
#include <iostream>
#include "../h/create_map.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/wall.h"
#include "../../graphic/h/loadMapMenu.h"

#define SPACE_KOEF 2

Create_map::Create_map(Window *w_)
{ 
	w = w_;
	name(w->g, "Create map");
	nextMenu = NULL;
	lastPut = NULL;
	map= NULL;
	skins.clear();
	text = NULL;
	select = 1;
	info_o = NULL;
	for (size_t i =0; i< NUMCHARS; i++)
		resol[i] = NULL;
	clean();
}
void Create_map::resize()
{
	std::string info = "Zadajte meno suboru";
	int info_width;
	TTF_SizeText(w->g->g_font,info.c_str(),&info_width,NULL); 
	info_o = TTF_RenderText_Solid(w->g->g_font,info.c_str(), w->g->normal);//TODO prehodit do kontruktora

	file_r.y = w->g->screen-> h/2 - 2*TTF_FontLineSkip(w->g->g_font);
	file_r.x = w->g->screen->w /2 - info_width/2;
	file_r.w = info_width+20;
	file_r.h = 3*TTF_FontLineSkip(w->g->g_font);

	/*setting widths*/
	rects[LEFT].w = rects[RIGHT].w =  15;//15 pixelov, obr neskor
	rects[CHOOSE].w = 2*skins[0]->get_size().x; 
	rects[UP].w = rects[DOWN].w = w->g->screen->w - rects[LEFT].w - rects[RIGHT].w - rects[CHOOSE].w;
	rects[MAP].w = w->g->screen->w - rects[CHOOSE].w - rects[LEFT].w - rects[RIGHT].w;
	rects[SAVE].w = rects[GENERATE].w =  rects[LOAD].w =
		rects[CLEAN].w = rects[EXIT].w = rects[VISIBILITY].w = 
		(w->g->screen->w / BUTTONS);

	/*setting heights*/
	rects[SAVE].h = rects[EXIT].h = rects[LOAD].h =
		rects[CLEAN].h = rects[GENERATE].h = rects[VISIBILITY].h = 30;
	rects[CHOOSE].h = w->g->screen->h;
	rects[UP].h = rects[DOWN].h = 15; //TODO potom sa to zosti z obrazkov naloadovanych
	rects[LEFT].h = rects[RIGHT].h = w->g->screen->h - rects[EXIT].h - rects[UP].h - rects[DOWN].h;
	rects[MAP].h = w->g->screen->h - rects[UP].h - rects[DOWN].h - rects[EXIT].h;

	/* setting x positions */
	rects[LEFT].x = rects[CLEAN].x = 0;
	rects[UP].x = rects[DOWN].x = rects[LEFT].w;
	rects[MAP].x = rects[LEFT].x + rects[LEFT].w;
	rects[RIGHT].x = rects[MAP].x + rects[MAP].w;

	rects[CHOOSE].x = rects[RIGHT].x + rects[RIGHT].w;
	rects[LOAD].x = rects[CLEAN].x + rects[CLEAN].w; //na jednej urovni
	rects[SAVE].x = rects[LOAD].x + rects[LOAD].w; //na jednej urovni
	rects[GENERATE].x = rects[SAVE].x + rects[SAVE].w; //na jednej urovni
	rects[EXIT].x = rects[GENERATE].x + rects[GENERATE].w;
	rects[VISIBILITY].x = rects[EXIT].x + rects[EXIT].w;

	/* setting y positions */
	rects[UP].y = 0;
	rects[CHOOSE].y = 0;
	rects[MAP].y = rects[LEFT].y = rects[RIGHT].y = rects[UP].h;
	rects[DOWN].y = rects[MAP].y+rects[MAP].h;
	rects[EXIT].y = rects[SAVE].y  = rects[CLEAN].y = rects[LOAD].y =
	rects[GENERATE].y = rects[VISIBILITY].y = rects[DOWN].y + rects[DOWN].h;

	//vygnerujeme mapove s tym, ze prva rada a prvy stlpec nevykresluju nic	
	int pom = rects[CHOOSE].y + skins[0]->get_size().y/2;

	for (int i =1; i< NumberObjectsImages; i++)
	{
		tile_rect[i].x = rects[CHOOSE].x + skins[0]->get_size().x/2;
		tile_rect[i].y = pom;
		tile_rect[i].w = skins[0]->get_size().x;
		tile_rect[i].h = skins[0]->get_size().y;
		pom += skins[0]->get_size().y +20; //TODO konstanta
	}
	if (map)
	{
		map->setBoundary(rects[MAP].w,rects[MAP].h); 
	}
}
void Create_map::init()
{
	for (size_t i = 0; i< NumberObjectsImages; i++)
		skins.push_back(new WallSkin("grass",i)); //TODO zo subora	
	
	std::string txt = "Write map resolution:";
	text = TTF_RenderText_Solid(w->g->g_font,txt.c_str(),w->g->normal);// na resize 2.krat
	TTF_SizeText(w->g->g_font,txt.c_str(),&text_width,NULL);
	if (text == NULL)  
	{
		TEST("Ajta krajta, nevytvoril sa text!");
	}
	std::string s[] = {"0","1","2","3","4","5","6","7","8","9","x"};
	for (int i =0; i< NUMCHARS; i++)
	{
		resol[i] = TTF_RenderText_Solid(w->g->g_font,s[i].c_str(),w->g->normal);
		TTF_SizeText(w->g->g_font,s[i].c_str(),&resol_width[i],NULL);
	}//TODO! po esc spat na resolution a resize


	std::string ids[] = {"clean", "save", "load", "generate", "exit" };
	for (int i =0; i< BUTTONS-1; i++)
	{
		buttonsImages[i] = TTF_RenderText_Solid( w->g->g_font,ids[i].c_str(), w->g->normal);
	}
	resize();
}

int Create_map::get_rect(int x, int y,SDL_Rect * r, int max)
{
	int i;
	for (i = 0; i < max; i++)
	{
		if ((x >=r[i].x) 
				&& (x< r[i].x + r[i].w)
				&& (y >= r[i].y)
				&& (y < r[i].y + r[i].h))
			return i;
	}
	return -1;
}

void Create_map::draw_resol() //TODO tu staci len raz vykreslit a potom sa pozriet na zmeny
{
	SDL_Rect r;
	r.x = (w->g->screen->w >> 1) - (text_width >> 1);
	r.y = (w->g->screen->h >> 1) - TTF_FontLineSkip(w->g->g_font)*2;
	SDL_BlitSurface (text, NULL, w->g->screen, &r);
	r.y+=TTF_FontLineSkip(w->g->g_font);
	for (unsigned int i = 0; i< written_x.size(); i++)
	{
		SDL_BlitSurface(resol[written_x[i] - '0'], NULL,w->g->screen, &r);
		r.x+=resol_width[written_x[i] - '0'];//potom to vycentrovat, samostatna funkcia
	}
	SDL_BlitSurface(resol[NUMCHARS - 1], NULL,w->g->screen, &r);
	r.x+=resol_width[NUMCHARS - 1];//potom to vycentrovat, samostatna funkcia
	for (unsigned int i = 0; i< written_y.size(); i++)
	{
		SDL_BlitSurface(resol[written_y[i] - '0'], NULL,w->g->screen, &r);
		r.x+=resol_width[written_y[i] - '0'];// TODO potom to vycentrovat, samostatna funkcia
	}
}
void Create_map::draw()
{
	SDL_Rect clip;
	SDL_GetClipRect(w->g->screen, &clip); 
	w->tapestry(clip);
	if (state == RESOLUTION)
	{
		draw_resol();
	}
	else
	{
		//nakresli pole
		SDL_Rect r = rects[MAP];
		r.w = map->boundaries.width;
		r.h = map->boundaries.height;
		SDL_SetClipRect(w->g->screen, &r);
	
		map->drawAll(w->g);

		//dokreslime panel
		SDL_SetClipRect(w->g->screen, NULL);
		for (int i =1 ; i< SelectedID; i++) //bez grass
		{
			drawPanel(i);
		}
		r = tile_rect[select];
		SDL_BlitSurface(skins[SelectedID]->get_surface(0),NULL,w->g->screen,&r);
		for (int i = 0; i < BUTTONS; i++)
		{
			r = rects[CLEAN + i];
			SDL_BlitSurface(buttonsImages[i],NULL, w->g->screen, &r);
		}
	}
	SDL_Flip(w->g->screen);
}
void Create_map::drawPanel(int i)
{
	SDL_Rect sh = tile_rect[i];
	SDL_Rect clip = sh;
	SDL_SetClipRect(w->g->screen, &clip);
	w->tapestry(sh);
	sh.x += (tile_rect[i].w - skins[i]->get_size().x) >>1;
	sh.y += (tile_rect[i].h - skins[i]->get_size().y) >>1;
	SDL_BlitSurface(skins[i]->get_surface(0),NULL,w->g->screen,&sh);
	SDL_UpdateRect(w->g->screen,tile_rect[select].x,tile_rect[select].y,tile_rect[select].w,tile_rect[select].h);
	SDL_SetClipRect(w->g->screen, NULL);
}

void Create_map::handleKey(SDLKey c)
{
	if (!x) 
		written_x+=w->g->event.key.keysym.sym; 
	else 
		written_y+=w->g->event.key.keysym.sym;
}
void Create_map::backspace()
{
	if ((!x)&&(written_x.length())) 
		written_x.erase(written_x.length()-1,1);
	if (x && (written_y.length())) 
		written_y.erase(written_y.length()-1,1);

}
void Create_map::drawInit()
{
	state = DRAW;
	Position p(convert<int>(written_x),convert<int>(written_y));
	map = new Map(p,"grass");

	buttonsImages[BUTTONS-1] = TTF_RenderText_Solid( w->g->g_font, deconvert<size_t>(map->visibility/10).c_str(), w->g->normal);

	map->shift(-rects[MAP].x, -rects[MAP].y);
	resize();
	draw();
}

void Create_map::keyDown(SDLKey c)
{
	switch (c)
	{
		case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4: 
		case SDLK_5: case SDLK_6: case SDLK_7: case SDLK_8: case SDLK_9: 
		{
			handleKey(c);
			draw();
			break;
		}
		case SDLK_BACKSPACE:
		{
			backspace();
			draw();
			break;
		}
		case SDLK_RETURN: 
		{ 
			drawInit();
			break;
		}
		case SDLK_RIGHT:
		case SDLK_x: { x = true; break;}
		case SDLK_LEFT:{x = false;break;}
		case SDLK_q:
		case SDLK_ESCAPE:
		{
			w->pop();
			return;
		}
		default:
			TEST("Unknown command (Create map)" )
			break;
	}
}
void Create_map::process_resolution()
{
	switch (w->g->event.type)
	{
		case SDL_VIDEORESIZE:
			w->resize();
			break;
		case SDL_KEYDOWN:
		{
			keyDown(w->g->event.key.keysym.sym);
			break;
		}
	}
}
void Create_map::generuj()
{
	map->clean();
	Position hlp = map->resolution;
	hlp.substractVector(Position(2*skins[WallSolidId]->get_shift().x,2*skins[WallSolidId]->get_shift().y));
	Position snakeRes = hlp/(SPACE_KOEF*60);

	Snakes snake(snakeRes); //FIXME nie konstanta ale vlastnost mapy
	Position diff(hlp.x / (SPACE_KOEF*snakeRes.x), hlp.y / (SPACE_KOEF*snakeRes.y) );
	snake.create();

	Position objPosition(skins[WallSolidId]->get_shift().x,skins[WallSolidId]->get_shift().y);
	TEST("vypisujem..\n")
	for (int i =0; i< snakeRes.x; i++)
	{
		for (int j =0; j< snakeRes.y; j++)
		{
			TEST(snake.map[i][j]);
			if (!snake.isWallAt(Position(i,j),Position(1,1)))
			{
				objPosition.y += SPACE_KOEF * diff.y;
				continue;
			}
			int oldX = objPosition.x;
			for (int a =0; a< SPACE_KOEF; a++)
			{
				for (int b = 0; b < SPACE_KOEF; b++)
				{
					Wall* wall = new Wall(skins[WallSolidId], NULL);
					wall->setPosition(objPosition,0);
					map->add(wall);
					objPosition.x += diff.x;
				}
				objPosition.x = oldX;
				objPosition.y += diff.y;
			}
		}
		TEST("..\n")
		objPosition.y = skins[WallSolidId]->get_shift().y;
		objPosition.x += SPACE_KOEF*diff.y;
	}
	map->addBoundaryWalls();
}
void Create_map::saving()
{
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
		{
			Uint16 znak = w->g->event.key.keysym.unicode;
			switch(znak)
			{
				case SDLK_BACKSPACE:
				{
					file_name = file_name.substr(0,file_name.size()-1);
					draw();
					break;
				}
				case SDLK_ESCAPE:
				{
					w->pop();
					return;
				}
				case SDLK_RETURN:
				{
					std::string msg = "Ok, press Enter to continue";
					file_name += ".map";
					if ( (file_name == ".map") || (!map->saveToFile(file_name) ) )
						msg = "Cannot save to file '"+ file_name +"'";
					
					state = DRAW;
					resize();
					draw();
					SDL_Surface *srf = TTF_RenderText_Solid(w->g->g_font,msg.c_str(),w->g->normal);
					SDL_Rect rcr = file_r;
					rcr.y += TTF_FontLineSkip(w->g->g_font)>>4;
					SDL_BlitSurface(srf, NULL, w->g->screen, &rcr);
					SDL_Flip(w->g->screen);
					SDL_FreeSurface(srf);
					file_name = "";
					do 
						SDL_WaitEvent(&w->g->event);
					while (w->g->event.type != SDL_KEYDOWN);
					draw();
					return;
				}
				default:
				{
					std::string temp;
					if (znak!=0)
						file_name+=(char) w->g->event.key.keysym.unicode; //TODO zistit ako funuje unicode
					if (temp==file_name)
					{
						break;
					}

					SDL_Surface *s = TTF_RenderText_Solid(w->g->g_font,file_name.c_str(),w->g->normal);
					if (s == NULL)
					{
						TEST("something's reeeally really wrong")
					}
					SDL_Rect r = file_r;
					r.y += TTF_FontLineSkip(w->g->g_font);
					SDL_BlitSurface(s, NULL, w->g->screen, &r);
					SDL_Flip(w->g->screen);
					SDL_FreeSurface(s);
					break;
				}
			}
			break;
		}
		case SDL_QUIT:
		{
			w->Destroy();
		}
	}
}
Position Create_map::closest(Position position, Object * o) //TODO dat toobjektu tu sa to asi nehodi
{
	//zistime, ci sa da tom mame upravit v -ovej alebo y-ovej osy

	Position result = position;
	if ( o == NULL )
		return result;
	Rectangle p = o->collisionSize(); //tu by malo byt normalne size, ale toto nevadi
	if ((p.x < position.x) && (position.x < p.x + p.width))
	{
		result.y = p.y;
	}
	if ((p.y < position.y) && (position.y < p.y + p.height))
	{
		result.x  = p.x;
	}
	return result;
}
void Create_map::buttonDown(int number, int atX, int atY)
{
	switch (number)
	{
		case MAP:
		{
			int x, y;
			x = atX + map->boundaries.x;
			y = atY + map->boundaries.y;
			Object * wall = NULL;
			switch (select)
			{
				case TargetPlace:
					map->addTarget(w->g, x, y);
					break;
				case WallBreakId:
					wall = new BreakableWall(skins[WallBreakId], NULL);
					break;
				case WallSolidId:
					wall = new Wall(skins[WallSolidId], NULL);
					break;
				case WallPushId:
					wall = new PushableWall(skins[WallPushId], NULL);
					break;
				case WallTrapId:
					wall = new TrapWall(skins[WallTrapId], NULL);
					break;
				case WallStartId:
					map->addStart(w->g, x, y);
					break;
				default:
					TEST("Object not recognized" << select);
			}
			SDL_Rect update;
			update.x =atX;
			update.y =atY;
			update.w = update.h = 50; //default, FIXME

			if (wall)
			{
				Position p(x,y); //x,y = aktual position
				wall->setPosition(p,0);
				Object * collide = map->checkCollision(wall);
				if (collide == NULL)
				{
					map->add(wall);
					lastPut = wall;
					update.w = wall->width();
					update.h = wall->height(); //TODO check, netreba shift?
					if (update.h+update.y > map->boundaries.height + 15)
						update.h -= update.h + update.y - map->boundaries.height - 15; //TODO zrusit a dat pre pred funkciu v tom, kde to vola, newBound sa proste nebde menit
					if (update.w+update.x > map->boundaries.width + 15)
						update.w -= update.w + update.x - map->boundaries.width - 15;

					map->update(update,true,w->g);
					break;
				}
				else
				{
					TEST("Koliduje")
				}
				update.w = -1;
				update.h = -1;
				lastPut = collide;
				delete wall;
				break;
			}
			map->update(update,true,w->g);
			break;
		}
		case CLEAN:
			{
				TEST("cleaning" )
				map->clean();
				map->addBoundaryWalls();
				SDL_Rect updateRect = rects[MAP];
				updateRect.w = min<int>(rects[MAP].w,map->boundaries.width);
				updateRect.h = min<int>(rects[MAP].h,map->boundaries.height);
				map->update(updateRect, true,w->g);
				break;
			}
		case SAVE:
		{
			TEST("save" )
			SDL_Rect r = file_r;
			SDL_FillRect(w->g->screen, &r,0);
			r.x+=10;
			SDL_BlitSurface(info_o,NULL,w->g->screen,&r);
			SDL_Flip(w->g->screen);
			state = SAVING;
			mouse_down = false;
			break;
		}
		case LOAD:
		{
			TEST("Loading map")
			if (nextMenu)
				delete nextMenu;
			nextMenu = new LoadMapMenu(w,map);
			map->shift(rects[MAP].x, rects[MAP].y);
			w->add( nextMenu );
			mouse_down = false;
			break;
		}
		case GENERATE:
		{
			generuj();//TODO vlastnost mapy

			SDL_Rect rect_ = rects[MAP];
			rect_.w = map->boundaries.width;
			rect_.h = map->boundaries.height;

			map->update(rect_, true,w->g);
			break;
		}
		case EXIT:
		{
			w->pop();
			break;
		}
		case CHOOSE:
		{
			mouse_down = false;
			TEST("choose" )
			int wall = get_rect(w->g->event.button.x,w->g->event.button.y, tile_rect, NumberObjectsImages);
			if (wall != -1)
			{
				drawPanel(select);
				SDL_UpdateRect(w->g->screen,tile_rect[select].x,tile_rect[select].y,tile_rect[select].w,tile_rect[select].h);
				select = wall;
				SDL_BlitSurface(skins[SelectedID]->get_surface(0),NULL,w->g->screen,&tile_rect[select]);
				SDL_UpdateRect(w->g->screen,tile_rect[select].x,tile_rect[select].y,tile_rect[select].w,tile_rect[select].h);
			}
			break;
		}
		case LEFT:
		{
			mouse_down = false;
			while (true)
			{
				if (map->boundaries.x > -rects[MAP].x)
					map->shift(-2,0);
				map->update(rects[MAP], true,w->g);
				if ((SDL_PollEvent(&w->g->event))
						&&(w->g->event.type == SDL_MOUSEBUTTONUP))
					break;
			}
			break;
		}
		case RIGHT:
		{
			mouse_down = false;
			while (true)
			{
				if (map->boundaries.x < map->size().x - rects[RIGHT].x)
					map->shift(2,0);
				map->update(rects[MAP], true,w->g);
				if ((SDL_PollEvent(&w->g->event))
						&&(w->g->event.type == SDL_MOUSEBUTTONUP)){
					break;

				}
			}
			break;
		}
		case UP:
		{ 
			mouse_down = false;
			while (true)
			{
				if (map->boundaries.y > -rects[MAP].y)
					map->shift(0,-2);
				map->update(rects[MAP], true,w->g);
				if ((SDL_PollEvent(&w->g->event))
						&&(w->g->event.type == SDL_MOUSEBUTTONUP))
					break;
			}
			break;
		}
		case DOWN:
		{
			mouse_down = false;
			while (true)
			{
				if (map->boundaries.y < map->size().y -rects[DOWN].y)
					map->shift(0, 2);
				map->update(rects[MAP], true,w->g);
				if ((SDL_PollEvent(&w->g->event))
						&&(w->g->event.type == SDL_MOUSEBUTTONUP))
					break;
			}
			break;
		}
		default: 
		{
			TEST(" Area unrecognized " )
			break;
		}
	}
}
void Create_map::resume()
{
	map->setBoundary(rects[MAP].w,rects[MAP].h); //kolko moze do sirky a vysky sa vykreslit, u resizu prekreslit
	map->shift(-rects[MAP].x, -rects[MAP].y);
	setVisibility();
	draw();
}

void Create_map::setVisibility()
{
	SDL_FreeSurface(buttonsImages[BUTTONS -1]);
	buttonsImages[BUTTONS -1] = TTF_RenderText_Solid(w->g->g_font, deconvert<size_t>(map->visibility/10).c_str(), w->g->normal);

}
//BIG TODO zmenit na citatelnejsie
void Create_map::process_map()
{
	switch (w->g->event.type)
	{
		case SDL_VIDEORESIZE:
			w->resize();
			break;
		case SDL_KEYDOWN:
		{
			switch(w->g->event.key.keysym.sym)
			{

				case SDLK_m:
					map->visibility-=20; //bez breaku, aby som sa nemusela opakovat:)
				case SDLK_p:
					{
						map->visibility +=10;
						setVisibility();
						SDL_Rect r = rects[VISIBILITY];
						r.w = w->g->screen->w - r.x;
						r.h = w->g->screen->h - r.y;
						w->tapestry(r);
						SDL_BlitSurface(buttonsImages[BUTTONS-1],NULL, w->g->screen, &r);
						SDL_UpdateRect(w->g->screen, rects[VISIBILITY].x, rects[VISIBILITY].y, rects[VISIBILITY].w, rects[VISIBILITY].h);
						break;
					}
				case SDLK_q:
				case SDLK_SPACE:
					draw();
					SDL_Flip(w->g->screen);
					break;
				case SDLK_ESCAPE:
				{
					w->pop();
					return;
				}
				default:
					TEST("Unknown command (Create map)" )
					break;

			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			mouse_down = true;
			addObj();
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouse_down = false; //POZOR na to, ze to moze byt aj iny button!
			lastPut = NULL;
			break;
		}
		case SDL_MOUSEMOTION:
		{
			if (mouse_down)
				addObj();
			break;
		}
	}
}
void Create_map::removeFromMap(Position p)
{
	SDL_Rect r;
	r = rects[MAP];
	SDL_SetClipRect(w->g->screen, &r);
	Object * o = map->removeShow(p,true,w->g);
	if ( o != NULL)
		delete o;
	SDL_SetClipRect( w->g->screen, NULL );
}

void Create_map::addObj()
{	
	Position p(0,0);
	Uint8 state = SDL_GetMouseState(&p.x, &p.y);
	if ( state & SDL_BUTTON_LEFT)
	{
		buttonDown (get_rect(p.x, p.y,rects,NumberOfMapDivision),p.x,p.y);
		return;
	}
	if ( state & 4)
	{
		removeFromMap(p);
		return;
	}
}

void Create_map::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0)
	{
		w->pop();
		return;
	}
	if (state == DRAW) 
	{
		process_map();
		
		return;
	}
	if (state == RESOLUTION)
	{
		process_resolution();
		return;
	}
	if (state == SAVING)
	{
		saving();
	}
}
void Create_map::clean()
{	
	lastPut = NULL;
	state = RESOLUTION;
	file_name = "";
	x = false;
	mouse_down = false;
	select = 1;
	written_x = "";
	written_y = "";
	map = NULL;
	if (text)
		SDL_FreeSurface(text);
	text = NULL;
	if (info_o)
		SDL_FreeSurface(info_o);
	info_o = NULL;
	for (int i =0; i< NUMCHARS; i++)
	{
		if (resol[i])
			SDL_FreeSurface(resol[i]);
		resol[i] = NULL;
	}
	while (!skins.empty())
	{
		if (skins.back())
			delete skins.back();
		skins.pop_back();
	}
	if (map)
		delete map;
	map = NULL;
}

Create_map::~Create_map()throw()
{
	clean();
} 
