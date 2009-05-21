#include "other.h"

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
}
void Play::draw()
{
	SDL_Rect r;
	r.x = 100;
	r.y = 10;
	SDL_BlitSurface(w->background,NULL,w->g->g_screen,&r);
	SDL_Flip(w->g->g_screen);
}

void Play::process()
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
