#include "../h/scheduller"
#include <SDL/SDL.h>

Scheduller::Scheduller()
{
	quantum = 0;
	r = NULL;
}

void Scheduller::penalize(Instruction i)
{
	quantum+=penalties[i->group];
}

bool SchedulleTime::ready()
{
	size_t ticks = SDL_GetTicks();
	return quantum - ticks;
}

bool SchedulleRound::ready()
{
	quantum--;
	return quantum;
}
Scheduller::~Scheduller()
{
	/* nothing */
}
SchedulleTime::~SchedulleTime()
{
	/* nothing */
}
SchedulleRound::~SchedulleRound()
{
	/* nothing */
}

