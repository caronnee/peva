#include <cstdlib>
#include <time.h>
#include "other.h"
#include "position.h"
#include "missille.h"

Join::Join(Window *w_)
{
	w = w_;
	name = "Join";
}
void Join::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,w->g->screen,&r);
	SDL_Flip(w->g->screen);
}

void Join::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko u JOINU" << std::endl;
						break;
				}
				break;
			}
	}	
}
Join::~Join()throw(){};

Host::Host(Window *w_)
{
	name = "Host";
	w = w_;
}
void Host::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,w->g->screen,&r);
	SDL_Flip(w->g->screen);
}

void Host::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko HOST" << std::endl;
						break;
				}
				break;
			}
	}	
}
Host::~Host()throw(){};

Play::Play(Window *w_)
{
	srand(time(NULL));
	name = "Play";
	w = w_;
	rect.x = 0;
	rect.y = 0;
	iter = iter_beg = letts.begin();
	resolution.x = 500;
	resolution.y = 300;
	begin.x = 0;
	begin.y = 0; //TODO  vystredit
	for (int i = 0; i< 256; i++)
	{
		letters[i].heigth = TTF_FontLineSkip(w->g->g_font);
		letters[i].ch = i;
		TTF_SizeText(w->g->g_font,letters[i].ch.c_str(), &letters[i].size,NULL); 
		letters[i].s = TTF_RenderText_Solid(w->g->g_font,letters[i].ch.c_str(), w->g->normal);

	}
	init (300,400);//TODO zmenit na mapy, ktore uzivatel zada
	//mapa o velkosti 10x10
/*	for(int i = 0; i<8; i++)
	{
		switch (rand()%3)
		{
			case 0:
				objects.push_back(new SolidWall(&t));
				break;
			case 1:
				objects.push_back(new TrapWall(&t));
				break;
			case 2:
				objects.push_back(new PushableWall(&t));
				break;
	//		case 3:
	//			objects.push_back(new Missille(Position(rand()%5, rand()%8)));
				break;
		}
	}
	//pozicia v pixeloch
	for ( int i = 0; i< objects.size(); i++)
	{
		objects[i]->position_in_map.x = rand()%600;
		objects[i]->position_in_map.y = rand()%480;
	}
	//detect collisions
	for (int i =0; i< objects.size(); i++)
		for (int j = i + i; j< objects.size(); j++)
		{
			if (object[i].x)
		}
		*/
	Position speed(100,100);
	Object *o =new Missille(Position(rand()%resolution.x, rand()%resolution.y), speed);
	objects.push_back(o);
	m->add(o);
}
Play::~Play()throw()
{
	for(size_t i =0; i< objects.size(); i++)
	{
		delete (objects[i]);
	}
}
void Play::redraw()
{
	w->tapestry();
	draw();
}

void Play::draw() //zatial ratame s tym, ze sme urcite vo vykreslovacej oblasti
{
	m->redraw(w, begin);
	SDL_Flip(w->g->screen);
}

void Play::init(int x, int y)
{
	resolution = Position(x,y);
	m = new Map(resolution);
	objects.clear();
	std::cout << "mapa vytvorena";
}
void Play::process()
{
	for (size_t i =0; i< objects.size(); i++)
	{
		objects[i]->action(m);
	}
	redraw();
	while (SDL_PollEvent(&w->g->event))
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_a:
						{
							Object * o = new Missille(Position(rand()%15, rand()%15), Position(100, 360));
							objects.push_back(o);
							m->add(o);
							break;
						}
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						break;
				}
				break;
			}
	}
}

Settings::Settings(Window *w_)
{
	w = w_;
	name = "Settings";
}
void Settings::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,w->g->screen,&r);
	SDL_Flip(w->g->screen);
}

void Settings::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Settings::~Settings()throw(){};