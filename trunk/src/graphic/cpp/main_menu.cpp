#include "../h/main_menu.h"
#include "../h/create_map.h"
#include "../h/other.h"
#include "../../add-ons/h/macros.h"

Main::Main(Window * w_, int argc, char * argv[])
{
	size = 0;	
	for (int i = 1; i< argc; i++)
	{
		std::string s(argv[i]);
		files.push_back(s);
	}
	w = w_; 
	menus = NULL;
}
void Main::resume()
{
	draw();
}
void Main::resize() { }

void Main::process()
{
	if (SDL_WaitEvent(&w->g->event) == 0){w->pop();return;}
	switch (w->g->event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			if (getMenu(menus, size, w->g) > -1)
				w->add(menus[iterator]);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			int itr = getMenu(menus, size, w->g);
			if (itr <0)
				break;
			menus[iterator]->unset();
			update(menus, size, iterator, w->g);
			iterator = itr;
			menus[iterator]->set();
			update(menus, size, iterator, w->g);
			break;
		}
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
					{
						w->pop();
						return;
					}
				case SDLK_RETURN:
					{
						w->add(menus[iterator]);
						break;
					}
				case SDLK_UP:
					{
						menus[iterator]->unset();
						update(menus, size, iterator, w->g);
						iterator--;
						if (iterator<0) 
							iterator = size -1;
						menus[iterator]->set();
						update(menus, size, iterator, w->g);
						break;
					}
				case SDLK_DOWN:
					{
						menus[iterator]->unset();
						update(menus, size, iterator, w->g);
						iterator++;
						iterator%=size;
						menus[iterator]->set();
						update(menus, size, iterator, w->g);
						break;
					}
				default:
					//throw exception
					break;
			}
			break;
		}
	}
}
void Main::clean()
{
	for (int i =0; i < size; i++)
	{
		if (menus[i])
			delete menus[i];
		menus[i] = NULL;
	}
	files.clear();
}

void Main::draw()
{
	SDL_Rect pom;
	SDL_GetClipRect(w->g->screen, &pom);
	w->tapestry(pom);
	
	TTF_SetFontStyle(w->g->g_font, TTF_STYLE_NORMAL);
	SDL_Flip(w->g->screen);
	drawMenu(menus, size, w->g );
}

void Main::init()
{
	//Todo nalodaovat z fajnlu settings;
	menus = new Menu*[NUMBEROFMENUS];
	size = NUMBEROFMENUS;
	iterator = 0;
	menus[0] = new Play(w);
	menus[1] = new Settings(w);
	menus[2] = new Create_map(w);
	menus[0]->set();
} 

Main::~Main()
{
	clean();
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
