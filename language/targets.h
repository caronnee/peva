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
};

class TargetVisitSequence : public TargetVisit
{
	std::vector<Position> positions;
	public:
	virtual bool visited(Rectangle r);
};

class TargetKillNumber//v okamihu, ked sa mu vrati strela
{
	protected:
	int constraint;
	public:
	void set(size_t t);
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
};

class TargetKillNumberLess : public TargetKillNumber
{
	int constraint;
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
};

class TargetKillNumberLessThen : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberLessThen();
};
class TargetKillNumberMore : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberMore();
};
class TargetKillNumberMoreThen : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberMoreThen();
};
class TargetKillNumberNot : public TargetKillNumber
{
	public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberNot();
};
class TargetKillId : public Target
{
	size_t ID;
	public:
	bool fullfilled(size_t id);
};

#endif
