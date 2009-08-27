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

class TargetKillNumber : public Target //v okamihu, ked sa mu vrati strela
{
	int constraint;
	public:
	virtual bool fullfilled();	
};

class TargetKillId : public Target
{
	size_t ID;
	public:
	bool fullfilled(size_t id);
};

#endif
