#include <sstream>
#include "draw.h"

void Window::Init_default()
{
	font = DEFAULT_FONT;
	font_size = DEFAULT_FONT_SIZE;
	resolution_width = DEFAULT_WIN_WIDTH;
	resolution_heigth = DEFAULT_WIN_HEIGTH;
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
	} // TODO! co ak zmenim resolution? Ntreba mi potom tam rozvnako zmenit ja toto?

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		std::cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	g_font = TTF_OpenFont(font.c_str(), font_size);
	if(!g_font)
	{
		std::cout << font << std::endl;
		std::cerr << "__Unable to open font: " << TTF_GetError() << std::endl;
		return false;
	}	
	g_screen = SDL_SetVideoMode(resolution_width, resolution_heigth, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		std::cerr << "Unable to set video, resolution: " << resolution_width << resolution_heigth << ", " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	SDL_Rect ** r = SDL_ListModes(g_screen->format,WIN_FLAGS|SDL_FULLSCREEN);
	int i =0;
	if (r == NULL ) { std::cout << "awekfgajesgfbewa" <<std::endl; return false;}
	if (r == (SDL_Rect**) -1 ) { std::cout << "mmmmmm" <<std::endl; }
	std::cout << "podoprujem mody fullscreenu: " << std::endl;
	printf("Available Modes\n");
	for (i=0; r[i]; ++i)
		std::cout << r[i]->w << " " <<  r[i]->h << std::endl;
//	std::cout << "::" << r[0]->x <<std::endl;
/*	while (r[i]!=NULL)
	{
	//	std::cout << r[i]->x << std::endl;
		i++;
	}*/
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
	unsigned number =0;
	std::istringstream convertor(s);
	convertor >> number;
	return number;
}
void Window::set_resolution(std::string res)
{
//	resolution_width = 
}
void Window::set_timeout(std::string time){}
void Window::set_font(std::string res){}
void Window::set_font_size(std::string res){}
void Window::set_background(std::string res){}

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
}
