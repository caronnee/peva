#include "../h/scheduller.h"
#include <SDL/SDL.h>

Scheduller::Scheduller()
{
	quantum = 0;
	for (size_t i =0; i< IGroups; i++) //TODO nacitavat zo suboru
	{
		penalties[i] = 1;
	}
}

void Scheduller::penalize(Instruction * i)
{
	quantum=penalties[i->group];
}

SchedulleTime::SchedulleTime() {}

bool SchedulleTime::ready()
{
	size_t ticks = SDL_GetTicks();
	return quantum - ticks;
}

SchedulleRound::SchedulleRound() {}

bool SchedulleRound::ready()
{
	quantum--;
	return quantum <= 0;
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

