#include "../h/menu.h"

Menu::Menu()
{
	nameHighLight = NULL;
	nameNormal = NULL;
}
SDL_Surface * Menu::get_name()const
{
	return show;
}
void Menu::set()
{
	show = nameHighLight;
}
void Menu::name(Graphic * g, std::string s)
{
	nameHighLight = TTF_RenderText_Solid(g->g_font,s.c_str(), g->light);
	nameNormal = TTF_RenderText_Solid(g->g_font,s.c_str(), g->normal);
	show = nameNormal;
}
void Menu::update(Menu ** menus, int size, int iterator, Graphic * g)
{
	SDL_Rect rect;
	rect.x = (g->screen->w >> 1) - 
		(menus[iterator]->get_name()->w >> 1);
	rect.y = (g->screen->h)/2 - size * (g->font_size) + (iterator* g->font_size << 1);

	rect.h = g->font_size;
	SDL_BlitSurface(menus[iterator]->get_name(), NULL, g->screen, &rect);
	SDL_UpdateRect(g->screen, rect.x, rect.y, menus[iterator]->get_name()->w, rect.h );
		
}
void Menu::drawMenu(Menu ** menus, int size, Graphic * g)
{
	SDL_Rect rect;
	rect.y = (g->screen->h)/2 - size * (g->font_size);// TODO zmenit na lepsie
	for (int i =0; i< size; i++)
	{
		rect.x = (g->screen->w >> 1) - (menus[i]->get_name()->w >> 1);
		rect.h = g->font_size;
		SDL_BlitSurface(menus[i]->get_name(), NULL, g->screen, &rect);
		SDL_UpdateRect(g->screen, rect.x, rect.y, menus[i]->get_name()->w, rect.h );
		rect.y += g->font_size << 1;
	}

} 
void Menu::unset()
{
	show = nameNormal;
}
Menu::~Menu()
{
	if (nameHighLight)
		SDL_FreeSurface(nameHighLight);
	if (nameNormal)
		SDL_FreeSurface(nameNormal);
}
