#include "../h/scheduller.h"
#include "../../add-ons/h/help_functions.h"
#include <SDL/SDL.h>

Scheduller::Scheduller()
{
	quantum = 0;
	for (size_t i =0; i< IGroups; i++) //TODO nacitavat zo suboru
		penalties[i] = 1;
}


void Scheduller::penalize(Instruction * i)
{
	quantum=penalties[i->group];
}
void Scheduller::reset()
{
	quantum = 0;
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

SchedulleTime::SchedulleTime(int roundTime_, const std::vector<int> & penals)
{
	roundTime = roundTime_;
	quantum = 0;
	size_t size = min<size_t>(penals.size(), IGroups);
	for (size_t i =0; i< size; i++)
		penalties[i] = penals[i];
	for (size_t i = size; i< IGroups; i++)
		penalties[i] = 1;
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
SchedulleRound::SchedulleRound()
{
	//the same as ancestor
}

SchedulleRound::SchedulleRound(const std::vector<int> & penals)
{
	size_t size = min<size_t>(penals.size(), IGroups);
	for (size_t i =0; i< size; i++)
		penalties[i] = penals[i];
	for (size_t i = size; i< IGroups; i++)
		penalties[i] = 1; //FIXME mozno do funkcie
}

bool SchedulleRound::ready()
{
	quantum--;
	return quantum < 0;
}

SchedulleRound::~SchedulleRound()
{
	/* nothing */
}

