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
	/* ammo, that can be shot */
	Seer seer;
	List ammo;
	size_t tasks;
	size_t eyeAngle;
public:
	/* Constructor */
	Body();
	int default_steps; 

	void dead();
	void bounce(Object *o);
	void killed(Object *o);
	int state() const;
	bool addKilled(unsigned l,Operation op, size_t number);
	void addVisit(std::vector<Position> pos);
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
