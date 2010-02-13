#include "../h/targets.h"

Target::Target()
{
	ok = false; //este nesplnena podmienka
	//TODO objects features
}
bool Target::fullfilled()
{
	return ok;
}
void Target::reset()
{
	ok = false;
}
Target::~Target() 
{
	/*
	   Nothing so far, nothing to destroy
	*/
}
TargetVisit::TargetVisit(size_t Id):Target()
{
	targetId = Id;
}
bool TargetVisit::setOk()
{
	ok = true;
	return ok;
}
size_t TargetVisit::tellId()
{
	return targetId;
}
bool TargetVisit::initPosition(Position p)
{
	boundingBox.x = p.x;
	boundingBox.y = p.y;
	boundingBox.width = 10;//TODO makra
	boundingBox.height = 10;
	return true;
}
Rectangle TargetVisit::tellPosition()
{
	return boundingBox;
}
TargetVisit::~TargetVisit()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetVisitSequence::TargetVisitSequence()
{
	places.clear();
	iter = 0;
}

TargetVisitSequence::TargetVisitSequence(std::vector<TargetVisit *> p)
{
	places = p;
}
TargetVisitSequence::TargetVisitSequence(std::vector<Position> p)
{
	for (size_t i = 0; i< p.size(); i++)
	{
		TargetVisit* t =new TargetVisit(0);
		t->initPosition(p[i]);
		places.push_back(t);
	}
}
size_t TargetVisitSequence::tellId()
{
	return places[iter]->tellId();
}
bool TargetVisitSequence::initPosition(Position p)
{
	places[iter]->initPosition(p);
	iter++;
	if (iter >= places.size())
	{
		iter = 0;
		return true;
	}
	return false;
}
Rectangle TargetVisitSequence::tellPosition()
{
	return places[iter]->tellPosition();
}
bool TargetVisitSequence::setOk()
{
	places[iter]->setOk();
	iter++;
	if (iter < places.size())
		return false;
	ok = true;
	return true;
}
void TargetVisitSequence::reset()
{
	Target::reset();
	iter = 0;
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
