#include <sstream>
#include "draw.h"
#include "main_menu.h"
#include "help_functions.h"

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
}
bool Graphic::Init()
{
	//if inited, return true; TODO
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
	g_screen = SDL_SetVideoMode(resolution_width, resolution_heigth, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
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
	//SDL_Rect ** r = SDL_ListModes(g->g_screen->format,WIN_FLAGS|SDL_FULLSCREEN);
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
	// Ak bol nejaky kod, uprace po nom 
	// TODO lespei osefovat, pri viacerych oknach sa mi moze stat, ze deletnem niekolkokrat
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

//------------------------------------------------WINDOW-----------------------------------------------------
Window:: Window(Graphic * g_)
{
	back = DEFAULT_BACKGROUND;
	timeout = DEFAULT_TIMEOUT;
	background = IMG_Load(DEFAULT_BACKGROUND);
	g = g_;
}

bool Window::Init()
{
	// Inicializace SDL
	bool b = g->Init();
	std::cout << "__" <<back << std::endl;
	background = IMG_Load(back.c_str());
	if (background == NULL) std::cout << "Backgound image not found!" <<std::endl;
	main_menu = new Main(this); //TODO  nieco ako set_main
	state.push(main_menu); 
	return b;
}

void Window::tapestry()
{
	SDL_Rect rect;
	if (background == NULL) {std::cout << "kvjfjbnskb"<<std::endl;return;}
	int i;
	for (i = 0; i < g->g_screen->h; i+=background->h) //tapetujeme pozadie, TODO zmenit na iba raz
	{
		rect.y=i;
		int j;
		for (j =0; j < g->g_screen->w; j+=background->w)
		{
			rect.x=j;
			SDL_BlitSurface(background,NULL,g->g_screen, &rect);
		}
	}
}

int Window::Toggle_screen()
{
	if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
//		WIN_FLAGS &= !SDL_FULLSCREEN;
	} 
//	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	if( SDL_WM_ToggleFullScreen(g->g_screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"Nepodarilo zmenit rozlisenie!"<<std::endl;
		SDL_FreeSurface(g->g_screen);
		return Init();
		}
	return true;
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblazni


void Window::set_timeout(std::string time)
{
	timeout = convert<int>(time);
}

void Window::set_background(std::string res)
{
	std::cout << "found" << std::endl;
	back = res;
}

void Window::Destroy()
{
		delete main_menu;
}
