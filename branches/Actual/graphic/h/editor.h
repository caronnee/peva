#ifndef ___EDITOR____
#define ___EDITOR____

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

struct Letter
{
	SDL_Surface * surface;
	char letter;
	Letter(); //font a letter
};

struct Line
{
	Letter letter;
	line * next_letter;
}

class Editor
{
	Window * g;
	int ID;
	int process(SDL_Event event); //on key write key, on enter try to compile
	std::vector<Letter *> line;		
	void save(std::string name);
	void load(std::string name);
}

#endif
