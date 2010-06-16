#include <cstdlib>
#include <time.h>
#include "../h/other.h"
#include "../../add-ons/h/position.h"
#include "../../add-ons/h/macros.h"
#include "../../objects/h/missille.h"
#include "../../language/h/bison.h"
#include "../../language/h/robot.h"

#define LAST 1
#define TIMESTAMP 20

// pre debug ucelu = 0, inak = 1
extern FILE * yyin; 
extern void my_destroy();
extern int yyparse(Robots *);


std::string instructionNames[] = { "undefined", "call", "create", "load", "conversion", "duplicate", "store", "pop", "jump", "break", "continue", "return", "restore", "removetemp", "plusplus", "minusminus", "plus", "minus", "multiply", "divide", "modulo", "binaryand", "and", "binaryor", "or", "binarynot", "not", "gt", "ge", "equal", "notequal ", "lt", "le", "begin", "endblock", "see", "eye", "fetchstate", "step", "wait", "shoot", "turn", "hit", "check", "locate", "direction", "random" };

Play::Play(Window *w_)
{
	/* init, not repeatable */
	error = false;
	recreate = true;
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
	clip.x = m->boundaries.x < 0? -m->boundaries.x:0;
	clip.y = m->boundaries.y < 0? -m->boundaries.y:0;
	clip.w = m->boundaries.width - clip.x;
	clip.h = m->boundaries.height - clip.y;
	SDL_SetClipRect(w->g->screen, &clip);
	m->drawAll( w->g );
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
	error = false;
	if (show)
		delete show;
	show = NULL;

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
	done = false;
	focus = 0;

	if (error ||w->settings->inputs.empty())
	{
		w->pop();
		return;
	}
	if (!recreate)
	{
		draw();
		return;
	}
	timeStamp = TIMESTAMP;
	robots.clean();
	robots.points = w->settings->gamePoints;
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
		error = true;
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
			t = rand()%starts.size();
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
			Position resol(m->getResolution().x - body->collisionSize().x,
					m->getResolution().y - body->collisionSize().y);
			TEST("No appropriate start place found")
			set = false;
			for (int iter = 0;iter < m->getResolution().x + m->getResolution().y; iter++) //FIXME other 'random' value
			{
				Position randomPosition(rand()%resol.x, rand()%resol.y);
				body->place(m,randomPosition);
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
	setFocus();
	if (robots.parseWarningList!="")
	{	
		std::string out = "";
		recreate = false;
		out += "warning!:"+robots.parseWarningList;
		show = new ShowMenu(w,out);
		w->add(show);
		return;
	}
	draw();
}
void Play::resize()
{
	m->setShift( 0 ,0);
	Position rct = m->setBoundary(w->g->screen->w, w->g->screen->h);
	//rozdiel medzi poslednym a sucasnym shiftom
	//TODO nacentrovat do posledneho robota
	m->setShift( (w->g->screen->w - rct.x)/-2,(w->g->screen->h - rct.y)/-2);
}
void Play::setFocus()
{
	Rectangle t = robots.robots[focus]->getBody()->collisionSize();
	Position p = robots.robots[focus]->getBody()->get_pos();
	p.x = p.x + (t.width - w->g->screen->w)/2;
	p.y = p.y + (t.height - w->g->screen->h)/2;
	Position lastAcceptable(m->getResolution().x - w->g->screen->w,
			m->getResolution().y - w->g->screen->h);
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
	if (m->boundaries.x < 0	)
		p.x = m->boundaries.x;
	if (m->boundaries.y < 0)
		p.y = m->boundaries.y;
	m->setShift(p.x,p.y);
}
void Play::process()
{
	size_t aliveRobots = robots.robots.size();
	bool t = false;
	for (size_t i = 0; i< robots.robots.size();i++)
	{	
		if (!robots.robots[i]->action(t))
			aliveRobots--;
		done |= t;
	}
	if (done)
		timeStamp--;
	else 
		timeStamp = TIMESTAMP;
	if ((aliveRobots == LAST) || timeStamp == 0) //ak je posledny robot
	{
		std::string endText = " Vitazi su:";
		std::string doneBots = "";
		std::string lastBots = "";
		for (size_t i = 0; i< robots.robots.size(); i++)
		{
			if(!robots.robots[i]->getBody()->alive())
				continue;
			if (!robots.robots[i]->getBody()->getTasks())
				doneBots +=robots.robots[i]->getName();
			lastBots +=robots.robots[i]->getName();
		}
		SDL_Surface * end;
		if (doneBots != "")
			end = w->g->render((endText+doneBots));
		else
			end = w->g->render((endText+lastBots));
		SDL_Rect rect;
		rect.x = (w->g->screen->w) >> 1;
		rect.y = (w->g->screen->h) >> 1;
		SDL_BlitSurface(end, NULL, w->g->screen, &rect);
		SDL_Flip(w->g->screen); //TODO update
		bool wait = false;
		while (!wait)
		{
			SDLKey key =w->waitKeyDown();
			switch (key)
			{
				case SDLK_ESCAPE:
				{
					w->pop();
					return;
				}
				case SDLK_s:
				{
					std::string out = "States:";
					if (show)
						delete show;
					for (size_t i =0; i<robots.robots.size(); i++)
						out += robots.robots[i]->info();
					show = new ShowMenu(w,out);
					w->add(show);
					wait = true;
					recreate = true;
					for (size_t i =0; i< robots.robots.size(); i++)
						m->remove(robots.robots[i]->getBody());
					return;
				}	
				case SDLK_RETURN:
				case SDLK_SPACE:
					wait = true;
					break;
				default:
					break;
			}
		}

		recreate = true;
		for (size_t i =0; i< robots.robots.size(); i++)
			m->remove(robots.robots[i]->getBody());
		resume();
		return;
	}
	done = m->performe(w->g);
	SDL_Delay(w->settings->delay);
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
				case SDLK_SPACE: //pause
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
				case SDLK_p:
				{
					w->settings->delay++;
					break;
				}
				case SDLK_m:
				{
					if (w->settings->delay!=0)
						w->settings->delay--;
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
					draw();
				}
				case SDLK_c: //center aktual
				{
					setFocus();	
					draw();
					break;
				}
				case SDLK_s:
				{
					recreate = false;
					std::string out = "States:";
					if (show)
						delete show;
					for (size_t i =0; i<robots.robots.size(); i++)
						out += robots.robots[i]->info();
					show = new ShowMenu(w,out);
					w->add(show);
					return;
				}
				case SDLK_n: //next map
				{
					recreate = true;
					if (w->settings->maps.empty())
						break;
						//removing body objects
					for (size_t i = 0; i < robots.robots.size(); i++)
						m->remove(robots.robots[i]->getBody());
					resume();
					break;
				}
				case SDLK_d:
				{
					draw();
					break;
				}
				default:
					break;
			}
			break;
		}
	}
}
SetSections::~SetSections()
{
	clean();
}
SetSections::SetSections(Window * w_, GamePoints * gp_)
{
	w = w_;
	gp = gp_;
	name(w->g,"Set maximum value of sections");
	for ( int i =0; i< SECTIONS * 3; i++)
		sectionPart[i] = NULL;
	sections = NULL;
}
void SetSections::resume() { }

void SetSections::resize() { }

void SetSections::draw()
{
	SDL_Rect rct;
	rct.x = BEGIN_X;
	rct.y = BEGIN_Y;
	rct.h = w->g->screen->h;
	rct.w = w->g->screen->w;

	SDL_SetClipRect(w->g->screen, &rct);
	w->tapestry(rct);

	SDL_Rect r;
	r.y = w->g->screen->h/3; //proste niekde
	for (int a = 0; a< SECTIONS; a++)
	{
		int i = a*3;
		int partSize = w->g->screen->w / SECTIONS;
		SDL_Rect rect;
		rect.y = r.y ; //proste niekde
		rect.x = a*partSize + ( partSize - sectionPart[i]->w )/2;//do stredu
		SDL_Rect tb = rect;
		if (a == iter)
		{
			SDL_BlitSurface(sectionPart[i+1],NULL,w->g->screen,&rect);
			tb.x = a*partSize + (partSize - sectionPart[i+2]->w )/2;
			tb.y += w->g->font_size*2;
			SDL_BlitSurface(sectionPart[i+2],NULL,w->g->screen,&tb);
			continue;
		}
		SDL_BlitSurface(sectionPart[i],NULL,w->g->screen,&rect);
		tb.y += w->g->font_size*2;
		tb.x = a*partSize + (partSize - sectionPart[i+2]->w )/2;//do stredu
		SDL_BlitSurface(sectionPart[i+2],NULL,w->g->screen,&tb);
	}

	r.y += w->g->font_size*4+BEGIN_Y;
	r.x = BEGIN_X;
	for (int i =0; i< 2*FirstSection::NumberOfSections; i+=2)
	{
		SDL_Rect sctrct = r;
		sctrct.x = BEGIN_X;
		sctrct.y += i*w->g->font_size;
		SDL_BlitSurface(sections[i],NULL,w->g->screen, &sctrct);
		sctrct.x += sections[i]->w + BEGIN_X;
		SDL_BlitSurface(sections[i+1],NULL,w->g->screen, &sctrct);
	}
	int j = 2*FirstSection::NumberOfSections;
	for (int i =0; i< 2*SecondSection::NumberOfSections; i+=2)
	{
		SDL_Rect sctrct = r;
		sctrct.x = BEGIN_X + w->g->screen->w/2;
		sctrct.y += i*w->g->font_size;
		SDL_BlitSurface(sections[i+j],NULL,w->g->screen, &sctrct);
		sctrct.x += sections[i+j]->w + BEGIN_X;
		SDL_BlitSurface(sections[i+j+1],NULL,w->g->screen, &sctrct);
	}
	//iter subsection
	if (iterSubSection>=0)
	{
		SDL_Rect chrct = r;
		chrct.x = BEGIN_X;
		chrct.y += 2*iterSubSection*w->g->font_size;
		int sect = FirstSection::NumberOfSections + SecondSection::NumberOfSections;
		sect *=2;
		if (iter == 1)
		{
			chrct.x+= w->g->screen->w/2;
			sect += FirstSection::NumberOfSections;
		}
		sect+=iterSubSection;
		SDL_BlitSurface(sections[sect], NULL, w->g->screen, &chrct);
	}
	SDL_Flip(w->g->screen);
	SDL_SetClipRect(w->g->screen, NULL);
}

void SetSections::init()
{
	iterSubSection = -1;
	iter = 0;
	for (int i = 0; i< SECTIONS*3; i+=3)
	{
		sectionPart[i] = w->g->render("Section:"+deconvert<int>(i/3));
		sectionPart[i+1] = w->g->renderLight("Section:"+deconvert<int>(i/3));
		std::string s = deconvert<int>(gp->total_[i/3]);
		if (gp->total_[i/3] < 50)
			s = "Do not check";
		sectionPart[i+2] = w->g->render( s );
	}
	for ( int i =0; i< SECTIONS * 3; i++)
		if (sectionPart[i] == NULL)
			throw "Cannot create image!";	
		
	//prva sekcia
	std::string names[] = {"hitpoints", "memory","angle", "misilles", "missilles attack","missilles hitpoints","speed","defense","attack"};

	sections = new SDL_Surface *[3*(FirstSection::NumberOfSections+ SecondSection::NumberOfSections)];
	//blit FIXME center
	int i=0;
	for ( i =0; i< 2*FirstSection::NumberOfSections; i+=2)
	{
		sections[i] = w->g->render(names[i/2]);
		sections[i+1] = w->g->render(deconvert<int>(gp->firstSection.sections[i/2]));
	}
	i = 2*FirstSection::NumberOfSections;
	for (int j =0; j<2*SecondSection::NumberOfSections; j+=2)
	{
		sections[i+j] = w->g->render(names[(i+j)/2]);
		sections[i+1+j] = w->g->render(deconvert<int>(gp->secondSection.sections[j/2]));
	}
	//names highlited
	int a = FirstSection::NumberOfSections+ SecondSection::NumberOfSections;
	a*=2;
	for (i = 0; i<FirstSection::NumberOfSections+ SecondSection::NumberOfSections; i++)
		sections[a+i] = w->g->renderLight(names[i]);
	
	SDL_Surface * n = get_name();

	SDL_Rect rct;
	rct.x = 0;
	rct.y = 0;
	rct.w = w->g->screen->w;
	rct.h = BEGIN_Y;

	w->tapestry(rct);
	rct.x = (w->g->screen->w - n->w)/2;
	rct.y = (BEGIN_Y - n->h)/2;
	SDL_BlitSurface(n, NULL, w->g->screen, &rct );
	SDL_Flip(w->g->screen);
}

void SetSections::process()
{
	SDLKey key;
	Uint8 type;
	bool d = false;
	bool down = false;
	while (true)
	{
		if (SDL_PollEvent(&w->g->event))
		{
			type = w->g->event.type;
			key =w->g->event.key.keysym.sym;
			d=true;
		}
		if (!down && !d)
			continue;
		switch (type)
		{
			case SDL_VIDEORESIZE:
			{
				w->resize();
				break;
			}
			case SDL_KEYDOWN:
			{
				down = true;
				switch(key)
				{
					case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4: case SDLK_5:
					case SDLK_6: case SDLK_7: case SDLK_8: case SDLK_9: 
					{
						if (iterSubSection >=0) //spracuj subsectiony
						{
							if (iter == 0)
							{
								SDL_FreeSurface(sections[iterSubSection*2+1]);
								gp->firstSection.sections[iterSubSection]*=10;
								gp->firstSection.sections[iterSubSection]+= key - SDLK_0;
								sections[iterSubSection*2+1] = w->g->render(deconvert<int>(gp->firstSection.sections[iterSubSection]));
							}
							else
							{
								int shift = FirstSection::NumberOfSections+iterSubSection;
								SDL_FreeSurface(sections[shift*2+1]);
								gp->secondSection.sections[iterSubSection]*=10;
								gp->secondSection.sections[iterSubSection]+=key - SDLK_0;
								sections[shift*2+1] = w->g->render(deconvert<int>(gp->secondSection.sections[iterSubSection]));
							}
							draw();
							break;
						}
						if (gp->total_[iter] < 0)
						{
							gp->total_[iter] = key - SDLK_0;
							SDL_FreeSurface(sectionPart[iter*3 + 2] );
							sectionPart[iter*3 + 2] = w->g->render( deconvert<int>(gp->total_[iter]).c_str() );
							draw();
							break;
						}
						gp->total_[iter] *=10;
						gp->total_[iter] += key - SDLK_0;
						SDL_FreeSurface(sectionPart[iter*3 + 2] );
						sectionPart[iter*3 + 2] = w->g->render( deconvert<int>(gp->total_[iter]).c_str() );
						draw();
						break;
					}
					case SDLK_BACKSPACE:
					{
						if (iterSubSection >=0)
						{
							if (iter == 0)
							{
								SDL_FreeSurface(sections[iterSubSection*2+1]);
								gp->firstSection.sections[iterSubSection]/=10;
								sections[iterSubSection*2+1] = w->g->render(deconvert<int>(gp->firstSection.sections[iterSubSection]));
							}
							else
							{
								int shift = FirstSection::NumberOfSections+iterSubSection;
								SDL_FreeSurface(sections[shift*2+1]);
								gp->secondSection.sections[iterSubSection]/=10;
								sections[shift*2+1] = w->g->render(deconvert<int>(gp->secondSection.sections[iterSubSection]));
							}
							draw();
							break;
						}
						gp->total_[iter] /=10;
						SDL_FreeSurface(sectionPart[iter*3 + 2] );
						sectionPart[iter*3 + 2] = w->g->render( deconvert<int>(gp->total_[iter]).c_str() );
						draw();
						break;
					}
					case SDLK_PAGEDOWN:
					{
						int max = (iter==0)? (int)FirstSection::NumberOfSections:(int)SecondSection::NumberOfSections;
						iterSubSection++;
						if (iterSubSection == max)
							iterSubSection--;
						draw();
						break;
					}
					case SDLK_PAGEUP:
					{
						if (iterSubSection>=0)
							iterSubSection--;
						draw();
						break;
					}
					case SDLK_q:
					case SDLK_ESCAPE:
					case SDLK_RETURN:
					{
						w->pop();
						return;
					}
					case SDLK_LEFT:
					{
						iter++;
						iter%=SECTIONS;
						iterSubSection = -1;
						draw(); //FIXME check
						break;
					}
					case SDLK_RIGHT:
					{
						iterSubSection = -1;
						if (iter <=0)
							iter = SECTIONS-1;
						else
							iter--;
						draw();
						break;
					}
					case SDLK_DOWN:
					{
						std::string s;
						if ( gp->total_[iter] <= MININUM_SECTION)
						{
							gp->total_[iter] = -1;
							s = "Do not check";
						}
						else
						{
							gp->total_[iter]--;
							s = deconvert<int>(gp->total_[iter]);
						}
						SDL_FreeSurface(sectionPart[iter*3+2]);
						sectionPart[iter*3 + 2] = w->g->render( s );
						draw();
						break;
					}
					case SDLK_UP:
					{
						if (gp->total_[iter] < MININUM_SECTION)
							gp->total_[iter] = MININUM_SECTION;
						else
							gp->total_[iter]++;
						SDL_FreeSurface(sectionPart[iter*3+2]);
						sectionPart[iter*3+2] = w->g->render( deconvert<int>(gp->total_[iter] ));
						draw();
						break;
					}
					default:
						TEST("Unhandled button")
						break;
				}
				SDL_Delay(100);
				break;
			}
			case SDL_KEYUP:
			{
				//down = false;
				break;
			}
		}	
	}
}

void SetSections::clean()
{
	for ( int i =0; i< SECTIONS * 3; i++)
	{
		SDL_FreeSurface(sectionPart[i]);
		sectionPart[i] = NULL;
	}
	int hlp = FirstSection::NumberOfSections + SecondSection::NumberOfSections;
	for (int i =0; i< 3*hlp; i++ )
		SDL_FreeSurface(sections[i]);
	delete []sections;
	sections = NULL;
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
		instructions[i].name = w->g->render( instructionNames[i]);
		instructions[i].nameChosen = w->g->renderLight( instructionNames[i]);
		std::string s = deconvert<int>((*penals)[i]);
		instructions[i].penalize = (*penals)[i];
		instructions[i].penal = w->g->render( s);
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
						if (instructions[index].penalize == 1)
							break;
						instructions[index].penalize--;
						SDL_FreeSurface(instructions[index].penal);
						std::string txt = deconvert<int>(instructions[index].penalize);
						instructions[index].penal =  w->g->renderLight( txt);
						draw(); //TODO iba tu cast
						break;
					}
					case SDLK_RIGHT:
					{
						instructions[index].penalize++;
						if(instructions[index].penalize == 0)
							instructions[index].penalize++;
						SDL_FreeSurface(instructions[index].penal);
						std::string txt = deconvert<int>(instructions[index].penalize);
						instructions[index].penal =  w->g->renderLight( txt);
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
	size = NumberOfMenus;
	iterator = 0;
	menus = new Menu * [NumberOfMenus];
	menus[Penalize] = new SetPenalize(w, &w->settings->penalizes);
	menus[Scheduller] = new SetScheduller(w);
	menus[Maps] = new SetMaps(w, &w->settings->maps, ".map", "maps");
	menus[Sections] = new SetSections(w, &w->settings->gamePoints);
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
	position = strToshow.find(':',0);
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
		size_t pos = strToshow.find_first_of("\t\n\r", position);
		if (pos == std::string::npos)
			pos = strToshow.size();
		if (pos - position > chars)
			pos = position + chars;
		std::string srt = strToshow.substr(position, pos - position);
		
		if(pos - position == chars)
		{
			size_t space = srt.find_last_of(" ");
			if(space < srt.size()-1)
			{
				pos = position +space;
				srt = srt.substr(0,space);
			}
			pos--;
		}

		if (srt == "")
		{
			position = pos+1;
			continue;
		}
		images.push_back(w->g->render(srt));
		if ((pos < strToshow.size()) && (strToshow[pos] == '\t'))
		{
			images.push_back(NULL);
		}
		position = pos+1;
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
		if (images[i]==NULL)
		{
			if (i == size -1)
				break;
			r.x =  w->g->screen->w - borders - images[i+1]->w;
			continue;
		}
		r.w = images[i]->w;
		r.h = images[i]->h;
		SDL_BlitSurface(images[i],NULL, w->g->screen, &r);
		r.y += w->g->font_size;
		r.x = borders;
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
	txt = w->g->render( "Aktualne je nastaveny scheduller:");
	schedullers[0] = w->g->render( "Pocet kol/instrukciu:");
	schedullers[1] = w->g->render( "Pocet instrukcii/kolo za cas:");
	valueString = "1";
	iter = 0;
	if (w->settings->scheduller)
	{
		iter = 1;
		valueString = deconvert<int>(w->settings->scheduller);
	}
	value =w->g->render( valueString);
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
void SetScheduller::resize() { }

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
								value = w->g->render( valueString);
								draw();
								break;
							}
						case SDLK_BACKSPACE:
							{
								SDL_FreeSurface(value);
								valueString.erase(valueString.size()-1,1);
								value = w->g->render( valueString);
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
