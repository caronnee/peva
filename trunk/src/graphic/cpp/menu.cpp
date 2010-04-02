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
