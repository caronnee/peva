#ifndef __SCHEDULLER_____
#define __SCHEDULLER____

#include "../../language/h/instructions.h"

class Scheduller
{
	size_t penalties[100]; //spravit dynamicky, neviem ,kolko bude instrukcii
	size_t quantum;
	public:
	void penalize(Instruction i);
	virtual int ready() = 0;
	virtual ~Scheduller();

};
class SchedulleTime: public Scheduller
{
	public:
	virtual int ready();
	~SchedulleTime();
};
class SchedulleRound: public Scheduller
{
	public:
	virtual int ready();
	~SchedulleRound();
};
#endif
