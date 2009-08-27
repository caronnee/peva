#include "targets.h"

Target::Target()
{
	ok = false; //este nesplnena podmienka
}
bool Target::fullfilled()
{
	return ok;
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
void TargetKillNumber::set(size_t t)
{
	constraint = t;
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
int TargetKillNumberLess::fullfilled()
{
	constraint--;
	if (constraint >0)
		return 1;
	return -1;
}
int TargetKillNumberLessThen::fullfilled()
{
	constraint--;
	if (constraint >= 0 )
		return 1;
	return -1;
}
int TargetKillNumberMore::fullfilled()
{
	constraint--;
	if (constraint >=0)
		return 0;
	return 1;
}
int TargetKillNumberMoreThen::fullfilled()
{
	constraint--;
	if (constraint >0)
		return 0;
	return 1;
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
