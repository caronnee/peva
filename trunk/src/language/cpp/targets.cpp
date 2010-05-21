#include "../h/targets.h"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"

#define SUCCESS 1
#define FAIL -1
#define NOCHANGE 0

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
		return "\tSuccess visiting " + targetName;
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
		return SUCCESS;
	return NOCHANGE;
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
int TargetKillNumber::done()
{
	if (constraint == 0)
		return SUCCESS;
	if (constraint == -1) //stalo sa nesplnitelnym
		return FAIL;
	return NOCHANGE;
}
int TargetKillNumber::fullfilled()
{
	constraint--;
	return done();
}
std::string TargetKillNumber::state()
{
	if (constraint == 0)
		return "\tSuccess in killin exact number of robots";
	return "\tFailed to kill " + deconvert<int>(constraint) 
		+ " more robots";
}
TargetKillNumber::~TargetKillNumber()
{
	/*
	   Nothing to destroy yet
	*/
}

std::string TargetKillNumberLess::state()
{
	if (constraint > 0)
		return "\tSuccess in killing number of enemies";
	return "\tFailed. Killed " + deconvert<int>(constraint+1) 
			+ " more robots";
}
TargetKillNumberLess::TargetKillNumberLess(int i) : TargetKillNumber(i)
{
	constraint = i;
}
int TargetKillNumberLess::done()
{
	if (constraint > 0)
		return NOCHANGE;
	return FAIL;
}
int TargetKillNumberLess::fullfilled()
{
	constraint--;
	return done();
}
TargetKillNumberLessEqual::~TargetKillNumberLessEqual()
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

TargetKillNumberLessEqual::TargetKillNumberLessEqual(int i) : TargetKillNumberLess(i)
{
	constraint = i;
}

int TargetKillNumberLessEqual::done()
{
	if (constraint >=0)
		return NOCHANGE;
	return FAIL;
}
int TargetKillNumberLessEqual::fullfilled()
{
	constraint--;
	return done();
}

std::string TargetKillNumberLessEqual::state()
{
	if (constraint <= 0)
		return "\tFailed. Killed " + deconvert<int>(-1*constraint+1) + "more robots";	
	return "\tSuccess in killing number of enemies";
}

TargetKillNumberMore::TargetKillNumberMore(int i) : TargetKillNumber(i)
{
	firstSuccess = false;
	constraint = i;
}
std::string TargetKillNumberMore::state()
{
	if (done())
		return "\tSuccess in killing enough enemies";
	return "\tFailed. Killed " + deconvert<int>(-1*constraint) + "less robots";	
}
int TargetKillNumberMore::done()
{
	if (constraint <= 0)
		return NOCHANGE;
	if (firstSuccess)
		return SUCCESS;
	return NOCHANGE;
}
int TargetKillNumberMore::fullfilled()
{
	constraint--;
	firstSuccess = false;
	return done();
}

TargetKillNumberMore::~TargetKillNumberMore()
{
	/*
	   Nothing to destroy yet
	*/
}
std::string TargetKillNumberMoreEqual::state()
{
	if (done())
		return "\tSuccess in killing enough robots";
	return "\tFailed. Killed " + deconvert<int>(-1*constraint+1) + "less robots";	
}
TargetKillNumberMoreEqual::TargetKillNumberMoreEqual(int i) : TargetKillNumberMore(i)
{
	constraint = i;
}
int TargetKillNumberMoreEqual::done()
{
	if (constraint == 0)
		return NOCHANGE;
	return TargetKillNumberMore::done();	
}
TargetKillNumberMoreEqual::~TargetKillNumberMoreEqual()
{
	/*
	   Nothing to destroy yet
	*/
}
TargetKillNumberNot::TargetKillNumberNot(int i) : TargetKillNumberLess(i)
{
	firstAfterZero =false;
	constraint = i;
}
std::string TargetKillNumberNot::state()
{
	if (done())
		return "\tSuccess in killing exact number of enemies";
	return "\tFailed. Killed wrong number of robots";	
}
int TargetKillNumberNot::done()
{
	if (constraint == 0)
		return FAIL;
	if (firstAfterZero)
		return SUCCESS;
	return NOCHANGE;
}
int TargetKillNumberNot::fullfilled()
{
	constraint--;
	firstAfterZero = constraint == 0;
	return done();
}
TargetKillNumberNot::~TargetKillNumberNot()
{
	/*
	   Nothing to destroy yet
	*/
}
