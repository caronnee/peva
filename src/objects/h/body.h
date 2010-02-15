#ifndef ___BODY_INTERFACE____
#define ___BODY_INTERFACE____

#include "../../objects/h/objects.h"
#include "../../add-ons/h/position.h"
#include "../../map/h/map.h"
#include "../../language/h/targets.h"
#include "../../language/h/enums.h"

class Body : public Object
{
	int default_steps; //settings?

	std::vector<Target *> targets;
	TargetKillNumber * toKill;
	std::vector<size_t> killTarget;

	/* in which map is an object located */
	Map * map;
public:
	/* ammo, that can be shot */
	List ammo;
	size_t tasks;
public:
	/* Constructor */
	Body();

	bool addKilled(unsigned l,Operation op, size_t number);
	void addVisit(std::vector<Position> pos);
	void addVisit(TargetVisit * pos);
	void addVisitSeq(std::vector<TargetVisit *> ids);
	void addVisitSeq(std::vector<Position> pos);
	void addKill(size_t id);
	virtual void move();
//	virtual void hitted(Object * attacker, Position p, int attack);

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
