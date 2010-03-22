#include <sstream>
#include "../h/graphic.h"
#include "../h/main_menu.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

Graphic::Graphic()
{
	resolution_width = DEFAULT_WIN_WIDTH;
	resolution_heigth = DEFAULT_WIN_HEIGTH;
	font_size = DEFAULT_FONT_SIZE;
	font = DEFAULT_FONT;

	SDL_Color s = {255,255,255,0};
	normal =s;
	SDL_Color t = {255,0,0,0};	
	light =t; 

	g_font = NULL;
	screen = NULL;
}
bool Graphic::Init()
{
	//if inited, return true; TODO
	if(SDL_Init(SDL_SUBSYSTEMS) == -1)
	{
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	atexit(SDL_Quit);
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
	screen = SDL_SetVideoMode(resolution_width, resolution_heigth, WIN_BPP, WIN_FLAGS);

	if(screen == NULL)
	{
		std::cerr << "Unable to set video, resolution: " << resolution_width << resolution_heigth << ", " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	g_font = TTF_OpenFont(font.c_str(), font_size); 
	if(!g_font)
	{
		std::cout << font << std::endl;
		std::cerr << "Unable to open font: " << TTF_GetError() << std::endl;
		return false;
	}	
	SDL_EnableUNICODE(true);
	//SDL_Rect ** r = SDL_ListModes(g->screen->format,WIN_FLAGS|SDL_FULLSCREEN);
	/*int i =0;
	  if (r == NULL ) { std::cout << "awekfgajesgfbewa" <<std::endl; return false;}
	  if (r == (SDL_Rect**) -1 ) { std::cout << "mmmmmm" <<std::endl; }
	  std::cout << "podoprujem mody fullscreenu: " << std::endl;
	  printf("Available Modes\n");
	  for (i=0; r[i]; ++i)
	  std::cout << r[i]->w << " " <<  r[i]->h << std::endl;*/
	return true;
}
void Graphic::set_resolution(std::string res)
{
	unsigned int pos = res.find("x");
	resolution_width = convert<int>(res.substr(0,pos));
	resolution_heigth = convert<int>( res.substr(pos+1)); //ocheckovat, ci sa to da, ci nemam corrupted file!
}

void Graphic::Destroy()
{
	//  cleaning the class
	if(g_font != NULL)
	{
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
	TTF_Quit();
	SDL_Quit();
}

void Graphic::set_font(std::string s)
{
	font = s;
}

void Graphic::set_font_size(std::string s)
{
	font_size = convert<int>(s);
}

//------------------------------------------------WINDOW--------------------------------------

Window:: Window(Graphic * g_)
{
	back = DEFAULT_BACKGROUND;
	background = IMG_Load(DEFAULT_BACKGROUND);
	g = g_;
	main_menu =NULL;
	background = NULL;
}

bool Window::Init(int argc, char * argv[] )
{
	// Inicializace SDL
	bool b = g->Init();
	if(main_menu)
		return b;
	background = IMG_Load(back.c_str());
	if (background == NULL) 
	{
		TEST("Background image not found!")
	}
	main_menu = new Main(this, argc, argv);
	main_menu->init();
	state.push(main_menu); 
	return b;
}

void Window::tapestry(SDL_Rect r)
{
	int startx = r.x - r.x%background->w;
	int starty = r.y - r.y%background->h;
	if (background == NULL) 
	{
		TEST("Background image not loaded !");
		return;
	}
	for (int i = starty; i < r.y+ r.h; i+=background->h) //tapetujeme pozadie, TODO zmenit na iba raz
	{
		for (int j = startx; j <r.x+ r.w; j+=background->w)
		{
			SDL_Rect rect;
			rect.y=i;
			rect.x=j;
			SDL_BlitSurface(background,NULL,g->screen, &rect);
		}
	}
}

int Window::toggle_screen()
{
	/*if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
		WIN_FLAGS &= !SDL_FULLSCREEN;
	} 
	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	*///zatial nepotrebujeme
	if( SDL_WM_ToggleFullScreen(g->screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"Nepodarilo zmenit rozlisenie!"<<std::endl;
		SDL_FreeSurface(g->screen);
		return Init(0,NULL); //FIXME inituje sa iba grafika
	}
	return true;
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblaznimain_menu = NULL;


void Window::set_background(std::string res)
{
	std::cout << "found" << std::endl;
	back = res;
}

void Window::Destroy()
{
	if (main_menu)
		delete main_menu;
	main_menu = NULL;
	if (background)
		SDL_FreeSurface(background);
	background = NULL;
	g = NULL;
	while (!state.empty())
	{
		state.pop();
	}
	//vsetko ostatne sa nam zdeletovalo pri delete main_menu
}
void Window::add(Menu * menu)
{
	state.push(menu);
}
void Window::pop()
{
	if ( !state.empty() )
	{
		state.top()->clean();
		state.pop();
	}
}
Menu * Window::top()const
{
	return state.top();
}
void Window::process()
{
	state.top()->process();
}
bool Window::empty()
{
	return state.empty();
}
