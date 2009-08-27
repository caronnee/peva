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
bool TargetKillNumber::fullfilled()
{
	if (ok)
		return ok;
	constraint--;
	if (constraint == 0)
		ok = true;
	return ok;
}
bool TargetKillId::fullfilled(size_t id)
{
	if (id == ID)
		ok = true;
	return true;
}
