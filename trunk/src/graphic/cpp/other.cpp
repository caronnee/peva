#include <cstdlib>
#include <time.h>
#include "../h/other.h"
#include "../../add-ons/h/position.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/missille.h"
#include "../../language/h/bison.h"
#include "../../language/h/robot.h"

#define LAST 1000

// pre debug ucelu = 0, inak = 1
extern FILE * yyin; //TODO zmenit na spravne nacitanie z editora
extern void my_destroy();
extern int yyparse(Robots *);


std::string instructionNames[] ={ "undefined ", "Call", "Create variable ", "loadlocal variable ", "loadglobal variable ", "load element", "conversion to int ", "conversion to real", "duplicate instruction", "store integer ", "store real ", "store object ", "store element", "pop ", "goto instruction ", "jump if true condition", "break ", "continue ", "return ", "restore", "remove temporary", "plusplus integer ", "plusplus real ", "minusminus integer ", "minusminus real ", "plus integer ", "plus real ", "minus integer ", "minus real ", "multiply integer ", "multiply real ", "divide integer ", "divide real ", "modulo ", "binary and ", "logical and ", "binary or ", "or ", "binary not ", "not ", "greater than integer ", " greater than real ", "greater or equal integer ", "greater or equal real ", "equal integer ", "equal real ", "equal object ", "not equal structure", "not equal integer ", "not equal real ", "not equal object ", "less than integer ", "less than real ", "less equal integer ", "less equal real ", "begin block ", "end block ", "see ", "eye ", "fetchstate after action", "step ", "step default number ", "wait ", "shoot at location ", "shoot at angle ", "turn ", "turn right ", "turn left", "is hit question", "is player question", "is wall question", "is missille question ", "locate question", "is moving question"};

Play::Play(Window *w_, std::vector<std::string> fls)
{
	/* init, not repeatable */
	files = fls;
	srand(time(NULL));
	w = w_;
	name(w->g, "Play Game");
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

void Play::resume(){}
void Play::draw() //zatial ratame s tym, ze sme urcite vo vykreslovacej oblasti
{
	m->redraw(w );
	SDL_Flip(w->g->screen);
}

void Play::init(int x, int y)
{
	m = new Map(Position (x,y), "grass");
	m->setBoundary(min<int> (w->g->screen->w, x), min<int>(w->g->screen->h,y));
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
	int err = 0;
	for (size_t i =0; i< files.size(); i++)
	{
		if((yyin=fopen(files[i].c_str(), "r"))==0)
		{
			std::cout<< "Unable to open input " << files[i] << std::endl;
			continue;
		}
		err += yyparse(&robots);
		fclose(yyin);	
	}
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
		w->pop();
		return;
	}
	for ( size_t i =0; i< robots.robots.size(); i++)
	{
		robots.robots[i]->getBody()->place(m,Position (250,i*180+100));
		robots.robots[i]->save_to_xml();
		m->add(robots.robots[i]->getBody());
	}
	my_destroy();

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
	if ((aliveRobots == LAST) || done) //ak je posledny robot
	{
		std::string endText = " Vitazi su: \r";
		std::string doneBots = "";
		std::string lastBots = "";
		for (size_t i = 0; i< robots.robots.size(); i++)
		{
			if(!robots.robots[i]->getBody()->alive())
				continue;
			if (!robots.robots[i]->getBody()->tasks)
				doneBots +=robots.robots[i]->getName();
			lastBots +=robots.robots[i]->getName();
		}
		SDL_Surface * end;
		if (doneBots != "")
			end = TTF_RenderText_Solid(w->g->g_font,(endText+doneBots).c_str(), w->g->normal);
		else
			end = TTF_RenderText_Solid(w->g->g_font,(endText+lastBots).c_str(), w->g->normal);
		TEST("___"<<m)
		SDL_Rect rect;
		rect.x = (m->resolution.x) >> 1;
		rect.y = (m->resolution.y) >> 1;
		TEST("Skoncili sme poprve")
		SDL_BlitSurface(end, NULL, w->g->screen, &rect);
		SDL_Flip(w->g->screen);
		SDL_WaitEvent(&w->g->event);
		SDL_FreeSurface(end);
		TEST("Skoncili sme")
		w->pop();
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

Settings::Settings(Window *w_, Setting *s):Main(w_,0,NULL)
{
	w = w_;
	settings = s;
	name(w->g,"Settings");
}
SetPenalize::SetPenalize(Window *win, std::vector<int> * penalize)
{
	w = win;
	name(w->g, "Set instruction costs ");
	penals = penalize;
}
void SetPenalize::draw()
{
	SDL_Rect clip;
	SDL_GetClipRect(w->g->screen,&clip);
	w->tapestry(clip);
	for (int i =0; i< size; i++ )
	{
		SDL_Rect rect;
		rect.x = BEGIN_X;
		rect.y = BEGIN_Y + i*vSkip;
		SDL_BlitSurface(instructions[begin+i].name, NULL, w->g->screen, &rect);
		rect.y = BEGIN_Y + i*vSkip;
		rect.x+= w->g->screen->w- 2* BEGIN_X - instructions[begin+i].penal->w;
		SDL_BlitSurface(instructions[begin+i].penal, NULL, w->g->screen, &rect);
	}
	SDL_Rect rect;
	rect.x = BEGIN_X;
	rect.y = BEGIN_Y + (index - begin)*vSkip;
	SDL_BlitSurface(instructions[index].nameChosen, NULL, w->g->screen, &rect);
	SDL_Flip(w->g->screen);
}
void SetPenalize::init()
{
	begin = 0;
	vSkip = w->g->font_size << 1;
	size = min<int>(w->g->screen->h/vSkip -1, IGroups);
	end = begin + size;
	for (int i = 0; i<IGroups; i++)
	{
		instructions[i].name = TTF_RenderText_Solid(w->g->g_font, instructionNames[i].c_str(),w->g->normal);
		instructions[i].nameChosen = TTF_RenderText_Solid(w->g->g_font, instructionNames[i].c_str(),w->g->light);
		std::string s = deconvert<int>((*penals)[i]);
		instructions[i].penal = TTF_RenderText_Solid(w->g->g_font, s.c_str(),w->g->normal);
	}
}
void SetPenalize::resume()
{
	draw();
}
void SetPenalize::clean()
{
}
void SetPenalize::choose(int iterator)
{
	SDL_Rect r2;
	r2.x = BEGIN_X;
	r2.y = BEGIN_Y + (index - begin) * vSkip;
	SDL_BlitSurface(instructions[index].nameChosen, NULL, w->g->screen, &r2);
	SDL_UpdateRect(w->g->screen, BEGIN_X , r2.y, 
			w->g->screen->w - BEGIN_X , w->g->screen->h - r2.y );

}
void SetPenalize::unchoose(int iterator)
{
	SDL_Rect r2;
	r2.x = BEGIN_X;
	r2.y = BEGIN_Y + (index - begin) * vSkip;
	SDL_BlitSurface(instructions[index].name, NULL, w->g->screen, &r2);
	SDL_UpdateRect(w->g->screen, BEGIN_X , r2.y, 
		w->g->screen->w - BEGIN_X , w->g->screen->h - r2.y );
}
void SetPenalize::process()
{
	while (SDL_PollEvent(&w->g->event))
	{
		switch (w->g->event.type)
		{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
					case SDLK_RETURN:
					{
						for (int i =0; i< IGroups; i++)
							(*penals)[i] = instructions[i].penalize;
						w->pop();
						return;
					}
					case SDLK_LEFT:
					{
						instructions[index].penalize--;
						SDL_FreeSurface(instructions[index].penal);
						std::string txt = deconvert<int>(instructions[index].penalize);
						instructions[index].penal =  TTF_RenderText_Solid(w->g->g_font, txt.c_str(), w->g->light);
						draw(); //TODO iba tu cast
						break;
					}
					case SDLK_RIGHT:
					{
						instructions[index].penalize++;
						SDL_FreeSurface(instructions[index].penal);
						std::string txt = deconvert<int>(instructions[index].penalize);
						instructions[index].penal =  TTF_RenderText_Solid(w->g->g_font, txt.c_str(), w->g->light);
						draw();
						break;
					}
					case SDLK_DOWN:
					{
						if (size == 0)
							break;
						unchoose(index);
						index++;
						if (index == IGroups)
							index--;
						else if (index >= end)
						{
							begin++;
							end++;
							draw();
							return;
						}
						choose(index);
						break;
					}
					case SDLK_UP:
					{
						if (size == 0)
							break;
						unchoose(index);
						index--;
						if (index > IGroups)
							index = 0;
						if (index < begin)
						{
							begin = index;
							end = begin + size;
							draw();
							return;
						}
						choose(index);
						break;
					}
					
					default:
					TEST("Unhandled button")
						break;
				}
				break;
			}
		}	
	}
}
void Settings::init()
{
	size = 3;
	iterator = 0;
	menus = new Menu * [size];
	menus[0] = new SetPenalize(w, &settings->penalizes);
	menus[1] = new SetScheduller(w, &settings->scheduller);
	menus[2] = new SetMaps(w, &settings->maps);
	menus[0]->set();
}

Settings::~Settings()
{
	// ako predok
}
SetScheduller::SetScheduller(Window * w_, int * sched)
{
	w = w_;
	name(w->g, "SetScheduller");
	result = sched;
}
void SetScheduller::init() 
{
	txt = TTF_RenderText_Solid(w->g->g_font, "Aktualne je nastaveny scheduller:", w->g->normal);
	schedullers[0] = TTF_RenderText_Solid(w->g->g_font, "Pocet kol/instrukciu:", w->g->normal);
	schedullers[1] = TTF_RenderText_Solid(w->g->g_font, "Pocet instrukcii/kolo za cas:", w->g->normal);
	valueString = "1";
	iter = 0;
	if (*result)
	{
		iter = 1;
		valueString = deconvert<int>(*result);
	}
	value =TTF_RenderText_Solid(w->g->g_font, valueString.c_str(), w->g->normal);	
}
void SetScheduller::draw()
{
	SDL_Rect rct;
	SDL_GetClipRect(w->g->screen, &rct);
	w->tapestry(rct);
	SDL_Rect rect;
	rect.x = (w->g->screen->w - txt->w)/2;
	rect.y = BEGIN_Y;

	SDL_BlitSurface(txt, NULL, w->g->screen, &rect);

	rect.x = (w->g->screen->w - schedullers[iter]->w)/2;
	rect.y = BEGIN_Y + 3* w->g->font_size;
	
	SDL_BlitSurface(schedullers[iter], NULL, w->g->screen, &rect);
	if (iter != 0)
	{
		rect.x = (w->g->screen->w - schedullers[iter]->w)/2;
		rect.y = BEGIN_Y + 6* w->g->font_size;
		SDL_BlitSurface(value, NULL, w->g->screen, &rect);
	}
	SDL_Flip(w->g->screen);
}
void SetScheduller::process()
{
	while (SDL_PollEvent(&w->g->event))
	{
		switch (w->g->event.type)
		{
			case SDL_KEYDOWN:
				{
					switch(w->g->event.key.keysym.sym)
					{
						case SDLK_q:
						case SDLK_ESCAPE:
						case SDLK_RETURN:
							{
								if (valueString == "")
									valueString = "1";
								(*result) = convert<int>(valueString);
								(*result) *= iter;
								w->pop();
								return;
							}
						case SDLK_LEFT:
						case SDLK_RIGHT:
							{
								iter ++;
								iter %=2;
								draw();
								break;
							}
						case SDLK_0: case SDLK_1:
						case SDLK_2: case SDLK_3:
						case SDLK_4: case SDLK_5:
						case SDLK_6: case SDLK_7:
						case SDLK_8: case SDLK_9:
						{
							SDL_FreeSurface(value);
							if (valueString.size() > 4 )
								break;
							valueString +=w->g->event.key.keysym.sym;
							value = TTF_RenderText_Solid(w->g->g_font, valueString.c_str(), w->g->normal);	
							draw();
							break;
						}
						case SDLK_BACKSPACE:
						{
							SDL_FreeSurface(value);
							valueString.erase(valueString.size()-1,1);
							value = TTF_RenderText_Solid(w->g->g_font, valueString.c_str(), w->g->normal);	
							draw();
							break;
						}

						default:
							TEST("Unhandled button")
								break;
					}
					break;
				}
		}	
	}
}

void SetScheduller::clean()
{
	SDL_FreeSurface(schedullers[0]);
	SDL_FreeSurface(schedullers[1]);
	SDL_FreeSurface(value);
	SDL_FreeSurface(txt);
}
void SetScheduller::resume()
{
	//nikdy by namlo nastat , zatial
}

SetMaps::SetMaps(Window * w_, std::vector<std::string> * result_):Load(w_,".map", "./maps")
{
	name(w->g, "Choose maps");
	result = result_;
}
void SetMaps::enter()
{
	for (size_t i = 0; i< entered.size(); i++)
		if (entered[i] == maps[index].name)
			{
				entered[i] = entered.back();
				entered.pop_back();
				return;
			}
	entered.push_back(maps[index].name);
}
void SetMaps::clean()
{
	result->clear();
	for (size_t i = 0; i< entered.size(); i++)
		result->push_back(entered[i]);
	Load::clean();
}
SetMaps::~SetMaps()
{
	//zatial nic
}
