#include <cstdlib>
#include <time.h>
#include "../h/other.h"
#include "../../add-ons/h/position.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/missille.h"
#include "../../language/h/bison.h"
#include "../../language/h/robot.h"

#define LAST -1
// pre debug ucelu = 0, inak = 1
extern FILE * yyin; //TODO zmenit na spravne nacitanie z editora
extern void my_destroy();
extern int yyparse(Robots *);

Join::Join(Window *w_)
{
	w = w_;
	name = "Join";
}
void Join::clean()
{
	//TODO
}
void Join::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	w->tapestry();
	SDL_Flip(w->g->screen);
}

void Join::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->pop();
							return;
						}
					default:
						std::cout << "nezname tlacitko u JOINU" << std::endl;
						break;
				}
				break;
			}
	}	
}
void Join::init(){}

Join::~Join(){};

Host::Host(Window *w_)
{
	name = "Host";
	w = w_;
}
void Host::clean()
{
	//TODO
}
void Host::draw()
{
	SDL_Rect r;
	r.x = 10;
	r.y = 10;
	w->tapestry();
	SDL_Flip(w->g->screen);
}

void Host::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->pop();
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
void Host::init(){}

Host::~Host(){};

Play::Play(Window *w_)
{
	/* init, not repeatable */
	srand(time(NULL));
	name = "Play Game";
	w = w_;
	m = NULL;
	for (int i = 0; i< 256; i++)
	{
		letters[i].heigth = TTF_FontLineSkip(w->g->g_font);
		letters[i].ch = i;
		TTF_SizeText(w->g->g_font,letters[i].ch.c_str(), &letters[i].size,NULL); 
		letters[i].s = TTF_RenderText_Solid(w->g->g_font,letters[i].ch.c_str(), w->g->normal);
	}

	/* cleaning up any mess */
	clean();
}
Play::~Play(){} //uz predtym sa zavola clear, takze to netreba

void Play::draw() //zatial ratame s tym, ze sme urcite vo vykreslovacej oblasti
{
	m->redraw(w );
	SDL_Flip(w->g->screen);
}

void Play::init(int x, int y)
{
	m = new Map(Position (x,y), "grass");
	m->setBoundary(min (w->g->screen->w, x), min (w->g->screen->h,y));
}

void Play::clean()
{
	done = false;
	rect.x = 0;
	rect.y = 0;
	iter = iter_beg = letts.begin();

	if (m!=NULL)
		delete m;

	m = NULL;
	done = false;
	robots.clean();
}

void Play::init()
{
	init( 500, 400 );//TODO zmenit na mapy, ktore uzivatel zada, zo struktury alebo suboru
}
void Play::process()
{
	size_t aliveRobots = robots.robots.size();//TODO vlastna funckia
	bool t = false;
	for (size_t i = 0; i< robots.robots.size();i++)
	{	
		if (!robots.robots[i]->action(t))
			aliveRobots--;
		done |= t;
	}
	if (/*aliveRobots == LAST ||*/ done) //ak je posledny robot
	{
		w->pop();//TODO dorobit vitazne tazenie, ako new win(x)
		TEST("Skoncili sme")
		return;
	}
	done = m->performe();
	draw(); //TODO performe bude mat OK, ci sa to ma prekreslit, kvoli sleepom
	while (SDL_PollEvent(&w->g->event))
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(w->g->event.key.keysym.sym)
			{
			/*	case SDLK_a:
				{
					Object * o = new Missille(Position(15,20), Position(-50,-60),new Skin("dragon",Skin::MissilleSkin));
					m->add(o);
					break;
				}*/
				case SDLK_r:
				{	
					if((yyin=fopen("vstup", "r"))==0)
					{
						puts("Unable to open input\n");
						break;
					}
					int err = yyparse(&robots);
					robots.checkSkins();
					bool bad = false;
					for ( size_t i =0; i< robots.robots.size(); i++)
					{

						if (robots.robots[i]->errors)
						{
							bad = true;
							break;
						}
					}
					if(bad|err)
					{
						fclose(yyin);	
						my_destroy();
						TEST("spatny vstup!")
						while(!robots.robots.empty())
						{
							delete robots.robots.back();
							robots.robots.pop_back();
						}
						break;
					}
					for ( size_t i =0; i< robots.robots.size(); i++)
					{
						robots.robots[i]->getBody()->place(m,Position (250,i*180+100));
						robots.robots[i]->save_to_xml();
						m->add(robots.robots[i]->getBody());
					}
					fclose(yyin);	
					my_destroy();
					break;
				}
				case SDLK_ESCAPE:
				{
					w->pop();
					return;
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
	w->tapestry();
	SDL_Flip(w->g->screen);
}
void Settings::clean()
{
	//TODO
}
void Settings::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0)
	{
		w->pop();
		return;
	}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->pop();
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

void Settings::init() {}

Settings::~Settings(){}
