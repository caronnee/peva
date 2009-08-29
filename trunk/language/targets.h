#ifndef ___TARGETS____
#define ___TARGETS____

#include <vector>
#include "position.h"

class Target
{
	protected:
	bool ok;
	public:
		Target();
		virtual bool fullfilled();
};

class TargetVisit : public Target //skontroluje sa po kazdej move action, po kazdej fps
{
	Position positionToVisit;
	public:
	virtual bool visited(Rectangle r);
	TargetVisit();
	TargetVisit(Position p);
};

class TargetVisitSequence : public TargetVisit
{
	std::vector<Position> positions;
	public:
	virtual bool visited(Rectangle r);
	TargetVisitSequence();
	TargetVisitSequence(std::vector<Position> p);
};

class TargetKillNumber//v okamihu, ked sa mu vrati strela
{
	protected:
	int constraint;
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumber();
	TargetKillNumber(int i);
};

class TargetKillNumberLess : public TargetKillNumber
{
	protected:
	int constraint;
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberLess();
	TargetKillNumberLess(int i);
};

class TargetKillNumberLessThen : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberLessThen();
	TargetKillNumberLessThen(int i);
};
class TargetKillNumberMore : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberMore();
	TargetKillNumberMore(int i);
};
class TargetKillNumberMoreThen : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberMoreThen();
	TargetKillNumberMoreThen(int i);
};
class TargetKillNumberNot : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberNot();
	TargetKillNumberNot(int i);
};
class TargetKillId : public Target
{
	size_t ID;
	public:
	bool fullfilled(size_t id);
	TargetKillId(int i);
};

#endif
