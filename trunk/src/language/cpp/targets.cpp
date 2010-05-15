#include "../h/targets.h"
#include "../../add-ons/h/macros.h"

Target::Target()
{
	ok = false; //este nesplnena podmienka
	//TODO objects features
}
bool Target::getOk()const
{
	return ok;
}
void Target::reset() { }

Target::~Target() 
{
	/*
	   Nothing so far, nothing to destroy
	*/
}
TargetVisit::TargetVisit(size_t Id):Target()
{
	ok = false;
	targetId = Id;
}
bool TargetVisit::setOk()
{
	ok = true;
	return ok;
}
int TargetVisit::tellId()
{
	return targetId;
}
bool TargetVisit::initPosition(Rectangle p)
{
	boundingBox = p;
	targetId =-8; //FIXME aby sa to dalo resetovat
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

TargetVisitSequence::TargetVisitSequence(std::vector<TargetVisit *> p)
{
	number = p.size();
	iter = 0;
	places = p;
}
int TargetVisitSequence::tellId()
{
	while ((iter < places.size()) && (places[iter]->tellId() < 0))
		iter++; //to nearest not set
	if (iter >= places.size())
		return -1;
	return places[iter]->tellId();
}
bool TargetVisitSequence::initPosition(Rectangle p)
{
	places[iter]->initPosition(p);
	iter++;
	if (iter >= places.size())
	{
		iter = places.size()-1;
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
	if (places[iter]->setOk())
		number--;;
	while((iter < places.size())&&(places[iter]->getOk()))
		iter++;
	ok = number == 0;
	return ok;
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

TargetKill::TargetKill()
{}

int TargetKill::done()
{
	if (constraint == 0)
		return 0;//uz splnene
	return 1;
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
	if (constraint == -1) //stalo sa nesplnitelnym
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
	first = 2;
	constraint = i;
}
int TargetKillNumberLess::done()
{
	if (constraint > 0)
		return 0;
	return 1;
}
int TargetKillNumberLess::fullfilled()
{
	constraint--;
	if (constraint == 0)
		return first-1;
	if (first)
	{
		first = 0;
		return 1; //bude stale splnene, az kym sa to neprehupne na druhu stranu
	}
	return 0;
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
	first = 2;
	constraint = i;
}

int TargetKillNumberLessThen::done()
{
	if (constraint >=0)
		return 0;
	return 1;
}
int TargetKillNumberLessThen::fullfilled()
{
	constraint--;
	if (constraint == -1 )
		return first-1;
	if (first)
	{
		first = 0;
		return 1; //prave sa splnilo, prave jeden krat
	}
	return 0;
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
int TargetKillNumberMore::done()
{
	if (constraint < 0)
		return 0;
	return 1;
}
int TargetKillNumberMore::fullfilled()
{
	constraint--;
	if (constraint ==-1)
		return 1; //nemoze sa to pokazit, nevraciame -1
	return 0;
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
int TargetKillNumberMoreThen::done()
{
	if (constraint <= 0)
		return 0;
	return 1;
}
int TargetKillNumberMoreThen::fullfilled()
{
	constraint--;
	if (constraint == 0)
		return 1;
	return 0;
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
	first = 1;
	firstAfterZero =false;
	constraint = i;
}
int TargetKillNumberNot::done()
{
	if (constraint == 0)
		return 1;
	return 0;
}
int TargetKillNumberNot::fullfilled()
{
	constraint--;
	if (constraint == 0)
	{
		firstAfterZero = true;
		return first-1; //ak si po prvy krat, vrat nulu, aby sa to neodcitalo, bo sa splnenie a nesplnenie rusi
	}
	if (firstAfterZero||first) //prvy krat od predchadzajuceho returnu
	{
		first = 0;
		firstAfterZero =false;
		return -1;
	}
	return 0;
}
TargetKillNumberNot::~TargetKillNumberNot()
{
	/*
	   Nothing to destroy yet
	*/
}
