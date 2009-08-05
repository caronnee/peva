#include "other.h"
#include "position.h"

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
	SDL_BlitSurface(w->background,NULL,w->g->g_screen,&r);
	SDL_Flip(w->g->g_screen);
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
						std::cout << "nezname tlacitko XXX" << std::endl;
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
	SDL_BlitSurface(w->background,NULL,w->g->g_screen,&r);
	SDL_Flip(w->g->g_screen);
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
						std::cout << "nezname tlacitko XXX" << std::endl;
						break;
				}
				break;
			}
	}	
}
Host::~Host()throw(){};


Play::Play(Window *w_)
{
	name = "Play";
	w = w_;
	begin = 0;
	rect.x = 0;
	rect.y = 0;
	for (int i = 0; i< 256; i++)
	{
		letters[i].heigth = TTF_FontLineSkip(w->g->g_font);
		letters[i].ch = i;
		TTF_SizeText(w->g->g_font,letters[i].ch.c_str(), &letters[i].size,NULL); 
		letters[i].s = TTF_RenderText_Solid(w->g->g_font,letters[i].ch.c_str(), w->g->normal);
	}
}
void Play::draw()
{
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	SDL_BlitSurface(w->background,NULL,w->g->g_screen,&r);
/*	for( int i =0; i< 256; i++)
	{
		r.x += letters[i-1].size;
		if (r.x >= w->g->resolution_width)
		{
			r.x = 0;
			r.y += letters[0].heigth;
		}
		SDL_BlitSurface(letters[i].s,NULL,w->g->g_screen, &r);
	}*/
	for(std::list<Letter *>::iterator i = letts.begin(); 
			(i!=letts.end()) && (r.y < w->g->resolution_width);
		       	i++)
	{
		if((*i) == NULL)
		{
			r.x = 0;
			r.y+=letters[0].heigth;
			continue;
		}
		SDL_BlitSurface((*i)->s, NULL, w->g->g_screen, &r);
		r.x+=(*i)->size;
	}
	SDL_Flip(w->g->g_screen);
}

void Play::process()
{
	draw();
	if (SDL_WaitEvent(&w->g->event) == 0){w->state.pop();return;}
	switch (w->g->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->g->event.key.keysym.sym)
				{
					case SDLK_RETURN:
						{
							letts.push_back(NULL);
							break;
						}
					case SDLK_UP:
						{
							
							break;
						}
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
								
					default:
						std::cout <<w->g->event.key.keysym.unicode << "!" <<std::endl;
						letts.push_back(&letters[w->g->event.key.keysym.unicode]);
						
						break;
				}
				break;
			}
	}
}
Play::~Play()throw(){};

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
	SDL_BlitSurface(w->background,NULL,w->g->g_screen,&r);
	SDL_Flip(w->g->g_screen);
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
