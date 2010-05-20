#include "../h/targets.h"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"

Target::Target()
{
	ok = false;
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
TargetVisit::TargetVisit(int Id):Target()
{
	ok = false;
	targetId = Id;
	if (Id <0)
		targetName = " user defined place";
	else
		targetName = " place with number " + deconvert<int>(Id);
}
bool TargetVisit::setOk()
{
	ok = true;
	return ok;
}

std::string TargetVisit::state()
{
	if (ok)
		return "Success visiting " + targetName;
	return "\tFailed to visit" + targetName;
}

int TargetVisit::tellId()
{
	return targetId;
}
bool TargetVisit::initPosition(Rectangle p)
{
	boundingBox = p;
	if (targetId < 0)
		targetName += "["+deconvert<int>(p.x + p.width/2)+","
			+deconvert<int>(p.y + p.height/2)+"]";
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
std::string TargetVisitSequence::state()
{
	std::string out;
	for (size_t i =0; i< places.size(); i++)
	{
		out += "\t"+places[i]->state();
	}
	return out;
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

int TargetKill::done()
{
	if (constraint == 0)
		return 0;//uz splnene
	return 1;
}

TargetKill::TargetKill(){} 

TargetKill::TargetKill(int i) 
{
	constraint = i;
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
std::string TargetKillNumber::state()
{
	if (constraint)
		return "\tFailed to kill " + deconvert<int>(constraint) 
			+ " more robots";
	return "Success";
}
TargetKillNumber::~TargetKillNumber()
{
	/*
	   Nothing to destroy yet
	*/
}

std::string TargetKillNumberLess::state()
{
	if (constraint)
		return "Success";
	return "\tFailed. Killed " + deconvert<int>(constraint) 
			+ " more robots";
}
TargetKillNumberLess::TargetKillNumberLess(int i) : TargetKillNumber(i)
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
	return done();

/*	if (constraint == 0)
		return first-1;
	if (first)
	{
		first = 0;
		return 1; //bude stale splnene, az kym sa to neprehupne na druhu stranu
	}
	return 0;*/
}
TargetKillNumberLessThen::~TargetKillNumberLessThen()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetKillNumberLess::~TargetKillNumberLess()
{
	/*
	   Nothing to destroy yet
	*/
}

TargetKillNumberLessThen::TargetKillNumberLessThen(int i) : TargetKillNumberLess(i)
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
	return done();
/*	if (constraint == -1 )
		return first-1;
	if (first)
	{
		first = 0;
		return 1; //prave sa splnilo, prave jeden krat
	}
	return 0;*/
}

std::string TargetKillNumberLessThen::state()
{
	if (done())
		return "Success";
	return "\tFailed. Killed " + deconvert<int>(-1*constraint+1) + "more robots";	
}

TargetKillNumberMore::TargetKillNumberMore(int i) : TargetKillNumber(i)
{
	constraint = i;
}
std::string TargetKillNumberMore::state()
{
	if (done())
		return "Success";
	return "\tFailed. Killed " + deconvert<int>(-1*constraint) + "less robots";	
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
std::string TargetKillNumberMoreThen::state()
{
	if (done())
		return "Success";
	return "\tFailed. Killed " + deconvert<int>(-1*constraint+1) + "less robots";	
}
TargetKillNumberMoreThen::TargetKillNumberMoreThen(int i) : TargetKillNumber(i)
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
TargetKillNumberNot::TargetKillNumberNot(int i) : TargetKillNumberLess(i)
{
	first = 1;
	firstAfterZero =false;
	constraint = i;
}
std::string TargetKillNumberNot::state()
{
	if (done())
		return "Success";
	return "\tFailed. Killed wrong number of robots";	
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
