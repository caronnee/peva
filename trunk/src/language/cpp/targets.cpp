#include "../h/targets.h"

Target::Target()
{
	ok = false; //este nesplnena podmienka
}
bool Target::fullfilled()
{
	return ok;
}
Target::~Target() 
{
	/*
	   Nothing so far, nothing to destroy
	*/
}
TargetVisit::TargetVisit(Position p)
{
	positionToVisit = p;
}
TargetVisit::TargetVisit()
{
	positionToVisit.x = -1;
	positionToVisit.y = -1;
}

bool TargetVisit::visited(Rectangle r)
{
	//TODO zlepsit, co ak sa to odrazi alebo tak nejak
	//ak je bod vnutri, potom OK
	if ((positionToVisit.x < r.x + r.width)
	&& (positionToVisit.x > r.x)
	&& (positionToVisit.y < r.y + r.height)
	&& (positionToVisit.y > r.y ))
		ok = true;
	return ok;
}

TargetVisit::~TargetVisit()
{
	/*
	   Nothing to destroy yet
	*/
}

TargetVisitSequence::TargetVisitSequence()
{
	positions.clear();
}

TargetVisitSequence::TargetVisitSequence(std::vector<Position> p)
{
	positions = p;
}

//TODO spravit rectangle IsInside
bool TargetVisitSequence::visited(Rectangle r)
{
	if (positions.empty())
		return true; //splnene
	Position p = positions.back();
	if ((p.x < r.x + r.width)
	&& (p.x > r.x)
	&& (p.y < r.y + r.height)
	&& (p.y > r.y ))
		positions.pop_back();
	if (positions.empty())
		ok = true; //splnene
	return ok;
}

TargetVisitSequence::~TargetVisitSequence()
{
	/*
	   Nothing to destroy yet
	*/
}

TargetKillNumber::TargetKillNumber()
{
	constraint = 0;
}
TargetKillNumber::TargetKillNumber(int i)
{
	constraint = i;
}

int TargetKillNumber::fullfilled()
{
	constraint--;
	if (constraint == 0)
		return 1;
	if (constraint <0)
		return -1;
	return 0;
}

TargetKillNumber::~TargetKillNumber()
{
	/*
	   Nothing to destroy yet
	*/
}

TargetKillNumberLess::TargetKillNumberLess()
{
	constraint = 0;
}

TargetKillNumberLess::TargetKillNumberLess(int i)
{
	constraint = i;
}

int TargetKillNumberLess::fullfilled()
{
	constraint--;
	if (constraint >0)
		return 1;
	return -1;
}

TargetKillNumberLess::~TargetKillNumberLess()
{
	/*
	   Nothing to destroy yet
	*/
}

TargetKillNumberLessThen::TargetKillNumberLessThen()
{
	constraint = 0;
}

TargetKillNumberLessThen::TargetKillNumberLessThen(int i)
{
	constraint = i;
}

int TargetKillNumberLessThen::fullfilled()
{
	constraint--;
	if (constraint >= 0 )
		return 1;
	return -1;
}

TargetKillNumberLessThen::~TargetKillNumberLessThen()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetKillNumberMore::TargetKillNumberMore()
{
	constraint = 0;
}
TargetKillNumberMore::TargetKillNumberMore(int i)
{
	constraint = i;
}
int TargetKillNumberMore::fullfilled()
{
	constraint--;
	if (constraint >=0)
		return 0;
	return 1;
}
TargetKillNumberMore::~TargetKillNumberMore()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetKillNumberMoreThen::TargetKillNumberMoreThen()
{
	constraint = 0;
}
TargetKillNumberMoreThen::TargetKillNumberMoreThen(int i)
{
	constraint = i;
}
int TargetKillNumberMoreThen::fullfilled()
{
	constraint--;
	if (constraint >0)
		return 0;
	return 1;
}
TargetKillNumberMoreThen::~TargetKillNumberMoreThen()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetKillNumberNot::TargetKillNumberNot()
{
	constraint = 0;
}
TargetKillNumberNot::TargetKillNumberNot(int i)
{
	constraint = i;
}
int TargetKillNumberNot::fullfilled()
{
	constraint--;
	if (constraint == 0)
		return 0;
	return 1;
}
TargetKillNumberNot::~TargetKillNumberNot()
{
	/*
	   Nothing to destroy yet
	*/
}
