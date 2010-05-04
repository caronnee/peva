#include <fstream>
#include <sstream>
#include "../h/window.h"
#include "../h/main_menu.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

#define RESTORE "last.data"

Setting::Setting()
{
	penalizes.insert(penalizes.begin(), IGroups, 1);
	scheduller = 0;
	delay = 0;
	std::ifstream input;
	input.open(RESTORE);
	if (!input.good())
		return;
		
	//last inputs, as was when program normally exited
	while (true)
	{
		if (input.eof())
			return;
		int i;
		input >> i;
		if (i<0)
			break; //skoncili sme
		input.ignore(256,':');
		int val;
		input >> val;
		penalizes[i]=val;
		input.ignore(256,' ');
	}
	//scheduller, as was set ..
	input.ignore(256,' ');
	input >> scheduller;
	input.ignore(256,' ');
	input >> delay;
	for (int i =0; i< SECTIONS; i++)
	{
		input.ignore(256,' ');
		input >> gamePoints.total_[i];
	}
	std::string s;
	input >> s; //whitespace posriesi cou, cin
	while (!input.eof())
	{
		if (s=="")
			break;
		maps.push_back(s);
		input >> s; //whitespace posriesi cou, cin
	};
	input.close();
}

Setting::~Setting()
{
	std::ofstream output(RESTORE);
	for(size_t i=0; i< penalizes.size(); i++)
		if(penalizes[i]!=1)
		{
			output << i << ":" <<penalizes[i] << " ";
		}
	output << -1<<" ";
	output << scheduller << " ";
	output << delay << " ";

	for (size_t i=0; i< SECTIONS; i++)
		output << gamePoints.total_[i]<<" ";

	for (size_t i=0; i< maps.size(); i++)
		output << maps[i]<<"\n";
}

Window:: Window(Graphic * g_)
{
	background = IMG_Load(DEFAULT_BACKGROUND);
	g = g_;
	main_menu =NULL;
	background = NULL;
	settings = NULL;
}

bool Window::Init(int argc, char * argv[] )
{
	// Inicializace SDL
	bool b = g->Init();
	settings = new Setting();

	if(main_menu)
		return b;
	background = IMG_Load(DEFAULT_BACKGROUND);
	if (background == NULL) 
	{
		TEST("Background image  not found!");
		return false;
	}
	main_menu = new Main(this, argc, argv);
	add(main_menu);
	return b;
}

void Window::resize()
{
	g->screen = SDL_SetVideoMode(g->event.resize.w, g->event.resize.h, WIN_BPP, WIN_FLAGS);
	SDL_SetClipRect(g->screen, NULL);
	state.top()->resize();
	state.top()->draw();
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
		TEST("Nepodarilo zmenit rozlisenie!")
		SDL_FreeSurface(g->screen);
		return Init(0,NULL); //FIXME inituje sa iba grafika
	}
	return true;
}; //TODO! zatial nepouzite, jelikoz musim este checkovat, ci sa mi to nahodou nezblaznimain_menu = NULL;


void Window::set_background(std::string res)
{
	if (background)
		SDL_FreeSurface(background);
	background = IMG_Load(res.c_str());
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
	SDL_SetClipRect(g->screen, NULL);
	state.push(menu);
	try
	{
		menu->init();
		if(menu == state.top()) //ak som v inite nieco nepridala
			menu->draw();
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		state.top()->clean();
		state.pop();
	}
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
bool Window::empty()
{
	return state.empty();
}
Window::~Window()
{
	if (settings)
		delete settings;
}
