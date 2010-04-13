#ifndef ___TARGETS____
#define ___TARGETS____

#include <vector>
#include "../../add-ons/h/position.h"
#include "../../objects/h/objects.h"

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
	virtual size_t tellId() = 0;

	/* Tell me what you need */
	virtual Rectangle tellPosition() = 0;
	
	/* Init */
	virtual bool initPosition(Position p) = 0;

	/* condition is fullfilled */
	virtual bool setOk() = 0;

	/* set target to unfullfilled again */
	virtual void reset();

	/* ask, if the condition was fulfilled */
	bool fullfilled();

	/* Destructor */
	virtual ~Target();
};

/* Contraint for visiting place */
class TargetVisit : public Target 
{
protected:
	/* id of the object */
	size_t targetId;

	/* boux about target position */
	Rectangle boundingBox;
public:
	/* Consturctor*/
	TargetVisit(size_t id);

	/* id of the target, created in contructor, should be unique*/
	size_t tellId();

	/* change or init position */
	bool initPosition(Position position);

	/* sets place as visited */
	bool setOk();

	/* tells information about position */
	Rectangle tellPosition();

	/* virtual destructor */
	virtual ~TargetVisit();
};

class TargetVisitSequence : public Target
{
	/* sequence that should be visited */
	std::vector<TargetVisit *> places;

	/* index of place that should be visited now */
	size_t iter;
public:
	
	TargetVisitSequence(std::vector<TargetVisit*> p);
	size_t tellId();
	bool initPosition(Position p);
	Rectangle tellPosition();
	bool setOk();
	void reset();
	virtual ~TargetVisitSequence();
};
class TargetKill
{
protected:
	int constraint;
public:
	virtual int done();
	TargetKill();
};

class TargetKillNumber : public TargetKill
{
public:
	/* 0 = not chaged, 1 = cheche & fulfilled, -1 = begin to b unfuillfilled */
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumber();
	TargetKillNumber(int i);
	virtual ~TargetKillNumber();
};

class TargetKillNumberLess : public TargetKillNumber
{
protected:
	int first;
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	TargetKillNumberLess();
	TargetKillNumberLess(int i);
	virtual ~TargetKillNumberLess();
};

class TargetKillNumberLessThen : public TargetKillNumberLess
{
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	TargetKillNumberLessThen();
	TargetKillNumberLessThen(int i);
	virtual ~TargetKillNumberLessThen();
};
class TargetKillNumberMore : public TargetKillNumber
{
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	TargetKillNumberMore();
	TargetKillNumberMore(int i);
	virtual ~TargetKillNumberMore();
};
class TargetKillNumberMoreThen : public TargetKillNumber
{
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	virtual int done();
	TargetKillNumberMoreThen();
	TargetKillNumberMoreThen(int i);
	virtual ~TargetKillNumberMoreThen();
};
class TargetKillNumberNot : public TargetKillNumberLess
{
protected:
	bool firstAfterZero;
public:
	virtual int fullfilled();	//0-cont, Fullfill, -1 = lost
	TargetKillNumberNot();
	TargetKillNumberNot(int i);
	virtual int done();
	virtual ~TargetKillNumberNot();
};

#endif
