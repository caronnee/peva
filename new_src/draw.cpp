#include <sstream>
#include "draw.h"

static SDL_Surface * g_screen; //TODO! spravit get_functiony, zmena na read_only

Main::Main(Window * w_)
{
	iterator = 0;
	w = w_; //akonahle sa vytvori, tak sa vykresli to, co sa ma
	menus[0] = new Play(w_);
	menus[1] = new Host(w_);
	menus[2] = new Join(w_);// TODO este mapa
	menus[3] = new Settings(w_);
}
void Main::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					case SDLK_RETURN:
						{
							w->state.push(menus[iterator]);
							break;
						}
					case SDLK_UP:
						{
							iterator--;
							if (iterator<0) iterator = 3;
							break;
						}
					case SDLK_DOWN:
						{
							iterator++;
							iterator%=4;
						}
					default:
						break;
				}
				break;
			}
	}	
}
void Main::draw()
{
	SDL_Rect rect;

	if (w->background == NULL) {std::cout << "kvjfjbnskb"<<std::endl;return;}
	int i;
	for (i = 0; i < g_screen->h; i+=w->background->h) //tapetujeme pozadie, TODO zmenit na iba raz
	{
		rect.y=i;
		int j;
		for (j =0; j < g_screen->w; j+=w->background->w)
		{
			rect.x=j;
			SDL_BlitSurface(w->background,NULL,g_screen, &rect);
		}
	}
	int offset_up = 10;
	rect.y = (g_screen->h + (w->font_size+offset_up)*4)/2;
	rect.x = (g_screen->w)/2 - 15;// TODO zmenit na lepsie
	SDL_Surface* text;
	TTF_SetFontStyle(w->g_font, TTF_STYLE_NORMAL);
	SDL_Color normal = {255,255,255,0};
	SDL_Color light = {255,0,0,0};
	int width;
	
	rect.y = (g_screen->h >> 1) - TTF_FontLineSkip(w->g_font)*2;
	for (int i =0; i< 4; i++)
	{
		TTF_SizeText(w->g_font, menus[i]->name.c_str(),	&width, NULL);
		if (i==iterator)
		{
			text = TTF_RenderText_Solid(w->g_font,menus[i]->name.c_str(), light );
		}
		else
		{
			text = TTF_RenderText_Solid(w->g_font,menus[i]->name.c_str(), normal );
		}	
		if (text ==NULL) std::cout << " Error rendering text " << TTF_GetError() <<std::endl; //podla mna tu tato podmienka nemusi byt
		rect.x = (g_screen->w >> 1) - (width >> 1);
		if (text ==NULL) std::cout << "IEuhfzeuh:"<<TTF_GetError() <<std::endl;
		SDL_BlitSurface(text, NULL, g_screen, &rect);
		SDL_FreeSurface(text);
		rect.y+=30;
	}
	SDL_Flip(g_screen);
}
Main::~Main()throw (){ }

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
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Join::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko u settings" << std::endl;
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
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Host::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko u settings" << std::endl;
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
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Play::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko u settings" << std::endl;
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
	SDL_BlitSurface(w->background,NULL,g_screen,&r);
	SDL_Flip(g_screen);
}

void Settings::process()
{
	if (SDL_WaitEvent(&w->event) == 0){w->state.pop();return;}
	switch (w->event.type)
	{
		case SDL_KEYDOWN:
			{
				switch(w->event.key.keysym.sym)
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						{
							w->state.pop();
							break;
						}
					default:
						std::cout << "nezname tlacitko u settings" << std::endl;
						break;
				}
				break;
			}
	}	
}
Settings::~Settings()throw(){};

Window:: Window()
{
	
	main_menu = new Main(this);
}
void Window::Init_default()
{
	font = DEFAULT_FONT;
	font_size = DEFAULT_FONT_SIZE;
	resolution_width = DEFAULT_WIN_WIDTH;
	resolution_heigth = DEFAULT_WIN_HEIGTH;
	timeout = DEFAULT_TIMEOUT;
	background = IMG_Load(DEFAULT_BACKGROUND);
}
bool Window::Init()
{
	// Inicializace SDL
	if(SDL_Init(SDL_SUBSYSTEMS) == -1)
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Surface* icon=IMG_Load(ICON);
	if (icon!=NULL)
	{
		SDL_WM_SetIcon(icon,NULL);
		SDL_FreeSurface(icon);
	} 

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		std::cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	g_font = TTF_OpenFont(font.c_str(), 12);
	if(!g_font)
	{
		std::cout << font << std::endl;
		std::cerr << "Unable to open font: " << TTF_GetError() << std::endl;
		return false;
	}	
	g_screen = SDL_SetVideoMode(resolution_width, resolution_heigth, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		std::cerr << "Unable to set video, resolution: " << resolution_width << resolution_heigth << ", " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	//SDL_Rect ** r = SDL_ListModes(g_screen->format,WIN_FLAGS|SDL_FULLSCREEN);
	/*int i =0;
	if (r == NULL ) { std::cout << "awekfgajesgfbewa" <<std::endl; return false;}
	if (r == (SDL_Rect**) -1 ) { std::cout << "mmmmmm" <<std::endl; }
	std::cout << "podoprujem mody fullscreenu: " << std::endl;
	printf("Available Modes\n");
	for (i=0; r[i]; ++i)
		std::cout << r[i]->w << " " <<  r[i]->h << std::endl;*/
	state.push(main_menu);
	return true;
}

int Window::Toggle_screen()
{
	if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
//		WIN_FLAGS &= !SDL_FULLSCREEN;
	} 
//	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	if( SDL_WM_ToggleFullScreen(g_screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"Nepodarilo zmenit rozlisenie!"<<std::endl;
		SDL_FreeSurface(g_screen);
		return Init();
		}
	return true;
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblazni

unsigned int Window::convert(std::string s)
{
	std::cout << s<< std::endl;
	unsigned number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
}
void Window::set_resolution(std::string res)
{
	unsigned int pos = res.find("x");
	resolution_width = convert(res.substr(0,pos));
	resolution_heigth = convert ( res.substr(pos+1)); //ocheckovat, ci sa to da, ci nemam corrupted file!
}
void Window::set_timeout(std::string time)
{
	timeout = convert(time);
}
void Window::set_font(std::string s)
{
	font = s;
}
void Window::set_font_size(std::string s)
{
	font_size = convert(s);
}
void Window::set_background(std::string res)
{
	background = IMG_Load(res.c_str());
	if (background == NULL) std::cout << "Backgound image not found!" <<std::endl;
}

void Window::Destroy()
{
	// Ak bol nejaky kod, uprace po nom 
	if(g_font != NULL)
	{
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	TTF_Quit();
	SDL_Quit();
//	delete main_menu;
}
