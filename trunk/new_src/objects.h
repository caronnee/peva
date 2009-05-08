#include <SDL/SDL.h>
#include "board.h"

struct Type
{
	int sigth, attack, defense, misille, exit; //kolko toho vidi, aku ma obranu, aku zbran, kde je jeho exit, sila utoku
}
struct Position
{
	int x, int y;
}

class Object // abstraktna klassa, ktora je predkom botov, strely aj Walls 
{
protected:
	SDL_Surface * show;
	Position position;
	int hit_points,interval; //zdravie a interval, po jakom sa naplanuje dalsia akcia
public:
	Object();
	virtual void damage(Object sender) = 0;
	virtual void action(Walls *** game) = 0;
};

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
