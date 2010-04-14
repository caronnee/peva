#ifndef ___BODY_INTERFACE____
#define ___BODY_INTERFACE____

#include "objects.h"
#include "seer.h"
#include "../../add-ons/h/position.h"
#include "../../map/h/map.h"
#include "../../language/h/targets.h"
#include "../../language/h/enums.h"

class Body : public Object
{
	int state_;

	std::vector<Target *> targets;
	TargetKillNumber * toKill;
	std::vector<Object *> killTarget;

	/* in which map is an object located */
	Map * map;
public:
	/* class handling visibility issue */
	Seer seer;

	/* ammo, that can be shot */
	List ammo;

	/* number of tasks to be done in order to win */
	size_t tasks;

	/* original eye angle */
	size_t eyeAngle;

	/* number of steps to be done when step() called */
	int default_steps; 
public:
	/* Constructor */
	Body();

	/* sets image to be dead*/
	void dead();
	
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
	virtual void move();
	virtual void hitted(Object * attacker, Position p, int attack);
	virtual void hit(Object * o);

	/* method to add ammo, ammo can be every object, body including */
	void addAmmo(Object * o);
	void addAmmo(Item * o);

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

	/* returns true, becuse it is not transparent */
	virtual bool is_blocking();

	virtual ~Body();
};
#endif
