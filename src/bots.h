#include <SDL/SDL.h>
#include "board.h"
#include "object.h""

struct Type_bot
{
	int sigth, angle, defense, misille; //kolko toho vidi, aku ma obranu, aku zbran, kde je jeho exit, sila utoku
}
struct Type_missille
{
	int attack, hitpoints; //a tak podobne, TODO!
}

class Bot : Object
{
	SDL_Surface ** show_phases ;
	Type type;
	Table defs;
	Stack Num;
	Stack instruction;
public:
	Bot(Type b);
	void damage(Object sender);
	void action(Walls *** board);
};
class Misille : Object
{
	int feature;
public:
	Misille();
	void damage(Object sender);
	void action(Walls *** board);
};
