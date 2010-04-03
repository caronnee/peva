#include <sstream>
#include "../h/window.h"
#include "../h/main_menu.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

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
	add(main_menu);
	return b;
}

void Window::tapestry(SDL_Rect r)
{
	SDL_SetClipRect(g->screen, &r);
	int startx = r.x -r.x%background->w;
	int starty = r.y -r.y%background->h;
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
	SDL_SetClipRect(g->screen, NULL);
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
	menu->init();
	menu->draw();
}
void Window::pop()
{
	if ( !state.empty() )
	{
		state.top()->clean();
		state.pop();
	}
	if ( !state.empty() )
		state.top()->resume();
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
