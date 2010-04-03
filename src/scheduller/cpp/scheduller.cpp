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

Scheduller::~Scheduller()
{
	/* nothing */
}

/*------------SchedulleTime--------*/
SchedulleTime::SchedulleTime(int rJ)
{
	roundTime = rJ;
}

bool SchedulleTime::ready()
{
	if (quantum > time)
	{
		quantum += roundTime;
		return false;
	}
	time -= quantum;
	return true;
}

SchedulleTime::~SchedulleTime()
{
	/* nothing */
}

/*------------SchedulleRound--------*/
SchedulleRound::SchedulleRound() {}

bool SchedulleRound::ready()
{
	quantum--;
	return quantum < 0;
}

SchedulleRound::~SchedulleRound()
{
	/* nothing */
}

