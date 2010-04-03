#ifndef __SCHEDULLER_____
#define __SCHEDULLER____

#include "../../language/h/instructions.h"

class Scheduller
{
	protected:
	size_t penalties[IGroups]; //spravit dynamicky, neviem ,kolko bude instrukcii
	int quantum;
	public:
	Scheduller();
	void penalize(Instruction * i);
	virtual bool ready() = 0;
	virtual ~Scheduller();

};
class SchedulleTime: public Scheduller
{
	int roundTime;
	int time;
	public:
	SchedulleTime(int roundTime_);
	virtual bool ready();
	virtual ~SchedulleTime();
};
class SchedulleRound: public Scheduller
{
	public:
	SchedulleRound();
	virtual bool ready();
	virtual ~SchedulleRound();
};
#endif
