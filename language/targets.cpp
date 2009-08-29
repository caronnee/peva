#include "targets.h"

Target::Target()
{
	ok = false; //este nesplnena podmienka
}
bool Target::fullfilled()
{
	return ok;
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
TargetVisitSequence::TargetVisitSequence()
{
	positions.clear();
}
TargetVisitSequence::TargetVisitSequence(std::vector<Position> p)
{
	positions = p;
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
bool TargetKillId::fullfilled(size_t id)
{
	if (id == ID)
		ok = true;
	return true;
}
