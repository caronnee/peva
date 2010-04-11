#ifndef __SCHEDULLER_____
#define __SCHEDULLER____

#include "../../language/h/instructions.h"

class Scheduller
{
	protected:
	size_t penalties[IGroups]; //FIXME spravit dynamicky, neviem ,kolko bude instrukcii
	int quantum;
	public:
	Scheduller();
	void reset();
	void penalize(Instruction * i);
	virtual bool ready() = 0;
	virtual ~Scheduller();

};

/*
 * Scheduller that permits more instruction per round according to cost. 
 * The higher is roundTime the more instructions can be executed 
 * */
class SchedulleTime: public Scheduller
{
	/* constant, how manu unit is worth every round */
	int roundTime;

	/* actual reserve */
	int time;

public:
	/* default constructor */
	SchedulleTime(int roundTime_);

	/* Constuction with penal initialization */
	SchedulleTime(int roundTime_, const std::vector<int> & penals);

	/* return robots availability */
	virtual bool ready();

	/* virtual destructor */
	virtual ~SchedulleTime();
};

/* Scheduller that permits maximum one instruction per time.
 * If the cost of the instruction id more than one. Negative 
 * or zero cost instructions behave the same as instructions 
 * with one cost */
class SchedulleRound: public Scheduller
{
public:
	/* default constructor */
	SchedulleRound();

	/* constructor with inicialization*/
	SchedulleRound(const std::vector<int> & penals);

	/* return robots availability */
	virtual bool ready();

	/* virtual destructor */
	virtual ~SchedulleRound();
};
#endif
