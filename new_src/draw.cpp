#include "draw.h"
#include <string>

//skoro globalne premenne, ale prin inkludovani sa ndostanu az ho hlahvneho programu, takze by to malo fachat

bool Init()
{
	// Inicializace SDL
	if(SDL_Init(SDL_SUBSYSTEMS) == -1)
	{
		cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_Surface* icon=IMG_Load("./images/icon.png");
	if (icon!=NULL)
	
		SDL_WM_SetIcon(icon,NULL);
		SDL_FreeSurface(icon);
	} // TODO! co ak zmenim resolution? Ntreba mi potom tam rozvnako zmenit ja toto?

	// Inicializace SDL_ttf
	if(TTF_Init() == -1)
	{
		cerr << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}
	g_font = TTF_OpenFont("./fonts/sfd/DejaVuSansCondensed.ttf", 16);
	if(!g_font)
	{
		cerr << "Unable to open font: " << TTF_GetError() << std::endl;
		return false;
	}	
	g_screen = SDL_SetVideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP, WIN_FLAGS);

	if(g_screen == NULL)
	{
		cerr << "Unable to set video, resolution: " << WIN_WIDTH << WIN_HEIGHT << ", " << TTF_GetError() << std::endl;
		return false;
	}
	SDL_WM_SetCaption(WIN_TITLE, NULL);
	return true;
}

int Toggle_screen()
{
	if (WIN_FLAGS && SDL_FULLSCREEN) //z fullscreenu do okna
	{
		WIN_FLAGS &= ~SDL_FULLSCREEN;
	} 
	else WIN_FLAGS |= SDL_FULLSCREEN; //opacne
	if( SDL_WM_ToggleFullScreen(g_screen) ==0) //nepodarilo sa to cez funkciu
	{
		std::cout<<"Nepodarilo zmenit rozlisenie!"<<std::endl;
		SDL_FreeSurface(g_screen);
		Init();
		}
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblazni

void Destroy()
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
