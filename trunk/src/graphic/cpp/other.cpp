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

Play::Play(Window *w_)
{
	/* init, not repeatable */
	srand(time(NULL));
	w = w_;
	name(w->g, "Play Game");
	loadInput = new SetMaps(w, &w->settings->inputs, ".input","inputs");
	show = NULL;
	m = NULL;
	/* cleaning up any mess */
	clean();
}
Play::~Play(){} //uz predtym sa zavola clear, takze to netreba

void Play::draw() //zatial ratame s tym, ze sme urcite vo vykreslovacej oblasti
{
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = m->boundaries.width;
	clip.h = m->boundaries.height;
	SDL_SetClipRect(w->g->screen,& clip);
	m->redraw( w->g );
	SDL_Flip(w->g->screen);
}

void Play::init(int x, int y)
{	
	focus = 0;
	if (m)
		delete m;
	Position t(x,y);
	m = new Map( t, "grass" );
	m->setBoundary(min<int> (w->g->screen->w, x), min<int>(w->g->screen->h,y));
}

void Play::clean()
{
	if (show)
		delete show;
	show = NULL;
	rect.x = 0;
	rect.y = 0;

	if (m!=NULL)
		delete m;

	m = NULL;
	done = false;
	robots.clean();
}

void Play::init()
{
	mapIter = 0;
	w->add(loadInput);
}

void Play::resume()
{
	focus = 0;
	if (show)
	{
		w->pop();
		return;
	}
	if (w->settings->inputs.empty())
	{
		w->pop();	
		return;
	}
	robots.clean();
	int err = 0;
	size_t lastIn = 0;
	for (size_t i = 0; i< w->settings->inputs.size(); i++)
	{
		if((yyin = fopen(w->settings->inputs[i].c_str(), "r"))==0)
		{
			TEST("Unable to open input " << w->settings->inputs[i] ) //TODO tu by to nikdy nemalo dojst, netreba vypisovat
			continue;
		}
		robots.input = w->settings->inputs[i];
		err += yyparse(&robots);
		fclose(yyin);	
	}
	std::string errList = "";
	lastIn = 0;
	for ( ; lastIn< robots.robots.size(); lastIn++)
		if (robots.robots[lastIn]->errors)
			errList += robots.robots[lastIn]->errorList;
	my_destroy();
	if (err)
		errList += robots.parseErrorsList;
	if ((errList != "") || err)
	{
		std::string s = "Errors found:" + errList;//TODO pytat sa na continue a stop, resp new MENU_SCROLL
		 
		while(!robots.robots.empty())
		{
			delete robots.robots.back();
			robots.robots.pop_back();
		}
		show = new ShowMenu(w,s);	
		w->add(show);
		return;
	}

	if(!m)
		m = new Map("grass");
	if (w->settings->maps.empty())
		init( 500, 400 );//TODO makro
	else
	{
		m->load(w->g, w->settings->maps[mapIter]);//fixme kontrola
		mapIter ++;
		mapIter%= w->settings->maps.size();
	}
	robots.finalize(m->visibility);
	for(size_t i =0; i< robots.robots.size(); i++)
		robots.robots[i]->save_to_xml();

	/* starts handling */
	std::list<Rectangle> starts = m->getStarts();
	for ( size_t i =0; i< robots.robots.size(); i++)
	{
		Body * body =robots.robots[i]->getBody();

		std::list<Rectangle>::iterator q = starts.begin();
		size_t t;
		Rectangle b;

		bool set = false;
		if (!starts.empty())
		{
			t =rand()%starts.size();
			for(size_t a=0; a<t; a++)//FIXME advance
				q++;
			b=*q;
		}

		for (size_t j =0; j < starts.size(); j++)
		{
			Position p;
			Rectangle e = body->collisionSize();
			p.x = q->x -(e.width - q->width)/2 - e.x;
			p.y = q->y -(e.height - q->height)/2 - e.y;
			robots.robots[i]->getBody()->place(m,p);
			if (!m->checkCollision(body))
			{
				starts.erase(q);
				set = true;
				m->add(body);
				break;
			}
		}
		if(!set)
		{
			TEST("No appropriate start place found")
			set = false;
			for (int iter = 0;iter < m->resolution.x + m->resolution.y; iter++) //FIXME other 'random' value
			{
				Position t(rand()%m->resolution.x, rand()%m->resolution.y);
				body->place(m,t);
				if (!m->checkCollision(body))
				{
					set = true;
					m->add(body);
					break;
				}
			}
			if (!set)
			{
				body->hitted(body, Position(0,0), 100000); //harakiri ;) possible easter egg
				TEST("I'm not on start, I cannot live anymore!")
			}
		}
	}
	//resolving targets
	robots.resolve();
	resize();
	draw();
}
void Play::resize()
{
	m->setBoundary(w->g->screen->w, w->g->screen->h);
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
		std::string endText = " Vitazi su:";
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
		SDL_Rect rect;
		rect.x = (m->resolution.x) >> 1;
		rect.y = (m->resolution.y) >> 1;
		SDL_BlitSurface(end, NULL, w->g->screen, &rect);
		SDL_Flip(w->g->screen); //TODO update
		w->g->waitKeyDown();
		
		SDL_FreeSurface(end);
		w->pop();
		return;
	}
	done = m->performe();
	m->updateScreen(w->g);
	while (SDL_PollEvent(&w->g->event))
	switch (w->g->event.type)
	{
		case SDL_VIDEORESIZE:
			w->resize();
			break;
		case SDL_KEYDOWN:
		{
			switch(w->g->event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					w->pop();
					return;
				}
				case SDLK_p: //pause
				{	
					while(true)
					{
						SDL_WaitEvent(&w->g->event);
						if (w->g->event.type == SDL_KEYDOWN)
							break;
					}
					m->time = SDL_GetTicks();
					break;
				}
				case SDLK_a: //another alive robot, no break, we need to center
				{
					for(size_t i =0; i<robots.robots.size(); i++)
					{
						focus++;
						focus %= robots.robots.size();
						if (robots.robots[focus]->getBody()->alive())
							break;
					}
				}
				case SDLK_c: //center aktual
				{
					if (focus >= robots.robots.size() )
						break; //should NOT be here, consider exception?
					Rectangle t = robots.robots[focus]->getBody()->collisionSize();
					Position p = robots.robots[focus]->getBody()->get_pos();
					p.x = p.x + (t.width - w->g->screen->w)/2;
					p.y = p.y + (t.height - w->g->screen->h)/2;
					Position lastAcceptable(m->resolution.x - w->g->screen->w,
						m->resolution.y - w->g->screen->h);
					if (lastAcceptable.x < 0)
						lastAcceptable.x = 0;
					if (lastAcceptable.y < 0)
						lastAcceptable.y = 0;
					if (lastAcceptable.x < p.x)
						p.x = lastAcceptable.x;
					if (lastAcceptable.y < p.y)
						p.y = lastAcceptable.y;
					if (p.x < 0)
						p.x = 0;
					if (p.y < 0)
						p.y = 0;
					m->setShift(p.x,p.y);
					break;
				}
				case SDLK_n: //next map
				{
					if (w->settings->maps.empty())
						break;
						//removing body objects
					for (size_t i = 0; i < robots.robots.size(); i++)
						m->remove(robots.robots[i]->getBody());
					resume();
					break;
				}
				default:
					break;
			}
			break;
		}
	}
}

Settings::Settings(Window *w_):Main(w_,0,NULL)
{
	w = w_;
	name(w->g,"Settings");
}
SetPenalize::~SetPenalize()
{
	//cleaned
}
SetPenalize::SetPenalize(Window *win, std::vector<int> * penalize)
{
	w = win;
	name(w->g, "Set instruction costs ");
	penals = penalize;
}

void SetPenalize::init()
{
	index = 0;
	for (int i = 0; i<IGroups; i++)
	{
		instructions[i].name = TTF_RenderText_Solid(w->g->g_font, instructionNames[i].c_str(),w->g->normal);
		instructions[i].nameChosen = TTF_RenderText_Solid(w->g->g_font, instructionNames[i].c_str(),w->g->light);
		std::string s = deconvert<int>((*penals)[i]);
		instructions[i].penalize = (*penals)[i];
		instructions[i].penal = TTF_RenderText_Solid(w->g->g_font, s.c_str(),w->g->normal);
	}
	resize();
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
void SetPenalize::resume()
{
	draw();
}
void SetPenalize::clean() { }

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
void SetPenalize::resize()
{
	begin = 0;
	vSkip = w->g->font_size << 1;
	size = min<int>(w->g->screen->h/vSkip -2, IGroups);
	end = begin + size;
}
void SetPenalize::process()
{
	while (SDL_PollEvent(&w->g->event))
	{
		switch (w->g->event.type)
		{
			case SDL_VIDEORESIZE:
			{
				w->resize();
				break;
			}
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
						if(index < 0)
							index  =0;
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
	menus[0] = new SetPenalize(w, &w->settings->penalizes);
	menus[1] = new SetScheduller(w);
	menus[2] = new SetMaps(w, &w->settings->maps, ".map", "maps");
	menus[0]->set();
}

Settings::~Settings()
{
	// ako predok
}
ShowMenu::~ShowMenu()
{
	//already cleaned
}
ShowMenu::ShowMenu(Window * w_, std::string strToshow_)
{
	w= w_;
	name(w->g,"Help");
	strToshow = strToshow_;
}
void ShowMenu::init()
{
	iter = 1;
	int borders = 20;
	size_t position =0;
	//najdeme header
	position = strToshow.find(':',0);//predpokladam, ze je dost male
	std::string show;	
	if (position == std::string::npos)
	{
		position =0;
		show = "Help";
	}
	else 
		show = strToshow.substr(0,position);
	size_t maxToHold = w->g->screen->h/w->g->font_size -4;
	
	int sizeOfChar = w->g->font_size/2;
	size_t chars = (w->g->screen->w - 2*borders)/sizeOfChar;
	images.push_back(w->g->render(show));
	while(position < strToshow.size())
	{
		size_t pos = strToshow.find_first_of("\n\r", position);
		if (pos == std::string::npos)
			pos = strToshow.size();
		if (pos - position > chars)
			pos = position + chars;
		std::string srt = strToshow.substr(position, pos - position);
		if(pos-position == chars)
		{
			size_t space = srt.find_last_of(" ");
			if(space < srt.size()-1)
			{
				pos = position +space;
				srt = srt.substr(0,space);
			}
			pos--;
		}
		position = pos+1;
		images.push_back(w->g->render(srt));
	}
	size = min<size_t>(images.size(),maxToHold);
}
void ShowMenu::resume()
{ 
	draw();
}
void ShowMenu::draw() 
{ 
	int borders = 20;
	SDL_Rect r;
	SDL_GetClipRect(w->g->screen, &r);
	w->tapestry(r);
	r.x = (w->g->screen->w - images[0]->w) >> 1;
	r.y = w->g->font_size;
	SDL_BlitSurface(images[0],NULL, w->g->screen, &r);

	r.x = borders;
	r.y = w->g->font_size << 2;
	for (size_t i = iter; i < size; i++)
	{
		r.w = images[i]->w;
		r.h = images[i]->h;
		SDL_BlitSurface(images[i],NULL, w->g->screen, &r);
		r.y += w->g->font_size;
	}
	SDL_Flip(w->g->screen);
}
void ShowMenu::clean()
{
	while(!images.empty())
	{
		SDL_FreeSurface(images.back());
		images.pop_back();
	}
}
void ShowMenu::resize()
{
	clean();
	init();
}

void ShowMenu::process()
{
	while (SDL_WaitEvent(&w->g->event)!=0)
	{
		if (w->g->event.type!= SDL_KEYDOWN)
			continue;
		switch(w->g->event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
			case SDLK_RETURN:
				w->pop();
				return;
			case SDLK_DOWN:
				if(iter == 1)
					break;
				iter--;
				draw();
				break;
			case SDLK_UP:
				if (iter >= images.size() - size +1)
					break;
				iter++;
				draw();
				break;
			default:
				TEST("Unhandled button at drawing help")
				break;
		}
		break;
	}
}
SetScheduller::~SetScheduller()
{
	//already cleaned
}
SetScheduller::SetScheduller(Window * w_)
{
	w = w_;
	name(w->g, "SetScheduller");
}
void SetScheduller::init() 
{
	txt = TTF_RenderText_Solid(w->g->g_font, "Aktualne je nastaveny scheduller:", w->g->normal);
	schedullers[0] = TTF_RenderText_Solid(w->g->g_font, "Pocet kol/instrukciu:", w->g->normal);
	schedullers[1] = TTF_RenderText_Solid(w->g->g_font, "Pocet instrukcii/kolo za cas:", w->g->normal);
	valueString = "1";
	iter = 0;
	if (w->settings->scheduller)
	{
		iter = 1;
		valueString = deconvert<int>(w->settings->scheduller);
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
void SetScheduller::resize()
{ }

void SetScheduller::process()
{
	while (SDL_PollEvent(&w->g->event))
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
						case SDLK_q:
						case SDLK_ESCAPE:
						case SDLK_RETURN:
							{
								if (valueString == "")
									valueString = "1";
								w->settings->scheduller = convert<int>(valueString);
								w->settings->scheduller *= iter;
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

SetMaps::SetMaps(Window * w_, std::vector<std::string> * result_, std::string ext, std::string addr):Load(w_,ext, addr)
{
	name(w_->g, "Choose " + addr);
	result = result_;
	entered.clear();
	for(size_t i=0; i< result->size(); i++)
		entered.push_back((*result)[i]);
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
