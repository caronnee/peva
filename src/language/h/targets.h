#ifndef ___TARGETS____
#define ___TARGETS____

#include <vector>
#include "../../add-ons/h/position.h"
#include "../../objects/h/objects.h"

#define TARGET_SPACE 15

/* Abstract class for creating constraints for victory */
class Target
{
protected:
	/* whether the constraint was fulfilled */
	bool ok;

public:
	/* Constructor */
	Target();

	/* tell me your ID */
	virtual int tellId() = 0;

	/* text informatio about state */
	virtual std::string state() = 0;

	/* Tell me what you need */
	virtual Rectangle tellPosition() = 0;
	
	/* Init */
	virtual bool initPosition(Rectangle p) = 0;

	/* condition is fullfilled */
	virtual bool setOk() = 0;

	/* set target to unfullfilled again */
	virtual void reset();

	/* ask, if the condition was fulfilled */
	bool getOk()const;

	/* Destructor */
	virtual ~Target();
};

/* Contraint for visiting place */
class TargetVisit : public Target 
{
protected:
	/* id of the object */
	int targetId;

	/* boux about target position */
	Rectangle boundingBox;

	/* for statistic purposes */
	std::string targetName;
public:

	/* Constructor*/
	TargetVisit(int id);

	/* id of the target, created in contructor, should be unique*/
	int tellId();

	/* text informatio about state */
	virtual std::string state();

	/* change or init position */
	bool initPosition(Rectangle position);

	/* sets place as visited */
	bool setOk();

	/* tells information about position */
	Rectangle tellPosition();

	/* virtual destructor */
	virtual ~TargetVisit();
};

class TargetVisitSequence : public Target
{
	/* internal counter to count number of successes */
	size_t number;

	/* sequence that should be visited */
	std::vector<TargetVisit *> places;

	/* index of place that should be visited now */
	size_t iter;
public:
	/* Constructor */
	TargetVisitSequence(std::vector<TargetVisit*> p);

	/* text informatio about state */
	virtual std::string state();

	/* tells id og last not inited place */
	int tellId();

	/* inits position */
	bool initPosition(Rectangle p);

	/* tells inited position */
	Rectangle tellPosition();

	/* tries to set as done, return true id all places from sequence if fullfilled */
	bool setOk();

	/* sets all as unvisited */
	void reset();

	/* destructor */
	virtual ~TargetVisitSequence();
};
class TargetKill
{
protected:
	/* how many robots were set */
	int constraint;
public:
	/* Contructor */
	TargetKill();
	TargetKill(int i);

	/* text iformation about state of killing spree */
	virtual std::string state() = 0;

	/* checks if appropriate */
	virtual int done();
};

class TargetKillNumber : public TargetKill
{
public:
	/* 0 = not chaged, 1 = cheche & fulfilled, -1 = begin to b unfullfilled */
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumber(int i);
	int done();
	std::string state();
	virtual ~TargetKillNumber();
};

class TargetKillNumberLess : public TargetKillNumber
{
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();

	/* text iformation about state of killing spree */
	virtual std::string state();

	TargetKillNumberLess(int i);
	virtual ~TargetKillNumberLess();
};

class TargetKillNumberLessEqual : public TargetKillNumberLess
{
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	/* text information about state of killing spree */
	virtual std::string state();
	TargetKillNumberLessEqual(int i);
	virtual ~TargetKillNumberLessEqual();
};
class TargetKillNumberMore : public TargetKillNumber
{
protected:
	bool firstSuccess;
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	virtual std::string state();
	TargetKillNumberMore(int i);
	virtual ~TargetKillNumberMore();
};
class TargetKillNumberMoreEqual : public TargetKillNumberMore
{
public:
	virtual std::string state();
	virtual int done();
	TargetKillNumberMoreEqual(int i);
	virtual ~TargetKillNumberMoreEqual();
};
class TargetKillNumberNot : public TargetKillNumberLess
{
protected:
	bool firstAfterZero;
public:
	virtual std::string state();
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberNot(int i);
	virtual int done();
	virtual ~TargetKillNumberNot();
};

#endif
