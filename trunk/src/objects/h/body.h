#ifndef ___BODY_INTERFACE____
#define ___BODY_INTERFACE____

#include <list>
#include "objects.h"
#include "seer.h"
#include "../../add-ons/h/position.h"
#include "../../map/h/map.h"
#include "../../language/h/targets.h"
#include "../../language/h/enums.h"

#define MININUM_SECTION 50
#define MAX_EYE_ANGLE 90

struct FirstSection
{
	enum Sections
	{
		SectionHitpoints,
		SectionMemorySize,
		SectionAngle,
		NumberOfSections
	};
	int sections[FirstSection::NumberOfSections];
	FirstSection();
};

struct SecondSection
{
	enum Sections
	{
		SectionMissilles,
		SectionMissilleAttack,
		SectionMissilleHitpoints,
		SectionSteps,
		SectionDefense,
		SectionAttack,
		NumberOfSections
	};
	SecondSection();
	int sections[SecondSection::NumberOfSections];
};

struct GamePoints
{
	enum check{
		DO_NOT_CHECK = 49
	};
	int total_[2];
	FirstSection firstSection;
	SecondSection secondSection;
	GamePoints(int total = 100, int total2 = 100 );
	void check();
};

class Body : public Object
{
private:
	/* missiles skin */
	MissilleSkin * ms;

	/* result of last action taken */
	int state_;

	/* condition according to number of killed robots */
	TargetKillNumber * toKill;

	/* robots that need to be destroye, recognized by name */
	std::vector<Object *> killTarget;

	/* in which map is an object located */
	Map * map;
public:
	/* class handling visibility issue */
	Seer seer;

	/* returns used skin */
	Skin * getSkin()const;

	/* place targt that need to be fullfilled */
	std::vector<Target *> targets;

	/* determines of object needs to be redrawed */
	bool changed();

	/* ammo, that can be shot */
	std::list<Object *> ammo;

	/* number of tasks to be done in order to win */
	size_t tasks;

	/* original eye angle */
	size_t eyeAngle;

	/* cleaning when death occured */
	void dead();

	/* number of steps to be done when step() called */
	int default_steps; 

	/* gamepoints holding ini informations */
	GamePoints points;
public:
	/* Constructor */
	Body();

	/* initialize robot according to gamePoints */
	void init(GamePoints g, int visibility);
	
	/* assuming that robot is settled in map */
	std::string initTargetPlaces();

	/* virtal method, nothing to do actually*/
	void bounce(Object *o);
	void killed(Object *o);
	int state() const;
	bool addKilled(unsigned l,Operation op, size_t number);
	void addVisit(TargetVisit * pos);
	void addVisitSeq(std::vector<TargetVisit *> ids);
	void addVisitSeq(std::vector<Position> pos);
	void addKill(Object * object);
	void move(size_t fps);
	virtual void hitted(Object * attacker, Position p, int attack);
	virtual void hit(Object * o);

	/* method to add ammo, ammo can be every object, body including */
	void addAmmo(Object * o);

	/* return number of objects, that can robot see */
	int see();
	
	/* return object that can robot see at index position */
	Object * eye(int index);

	/* Return an indication, whether robot can be moved steps steps */
	int step(int steps);

	/* sets information about map */
	void place(Map * m, Position p, int angle = 0);

	/* set movement to default steps */
	int step();
	
	/* for later use */
	int wait(int x = 0);
	
	/* Shoots a missille in the direction dir, if any left */
	int shoot(int angle);
	
	/* turns left*/
	int turnL();
	
	/* turns right*/
	int turnR();

	/* how manu rounds robot have to wait */
	int waits;
	/* returns true, becuse it is not transparent */
	virtual bool is_blocking();

	/* destructor */
	virtual ~Body();
};
#endif
