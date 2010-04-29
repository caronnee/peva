#include <cmath>
#include "../h/body.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

Body::Body() : Object(NULL)
{
	mHealth = mAttack = 0;
	state_ = 0;
	tasks = 0;
	name = "Robot";
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
	toKill = NULL;
}
bool Body::changed()
{
	return true;
}
void Body::bounce(Object * from)
{
	//no bouncing
}
void Body::addAmmo( Object * o)
{
	ammo.push_back(o);
	o->owner = this;
}
int Body::state() const
{
	return state_;
}
bool Body::addKilled(unsigned i,Operation op, size_t number)
{
	if (toKill !=NULL)
	{
	//	error(i,WarningKillAlreadyDefined);
		return false;
	}
	switch (op)
	{
		case OperationNotEqual:
			toKill = new TargetKillNumberNot(number);
			break;
		case OperationLess:
			toKill = new TargetKillNumberLess(number);
			break;
		case OperationLessEqual:
			toKill = new TargetKillNumberLessThen(number);
			break;
		case OperationGreater:
			toKill = new TargetKillNumberMore(number);
			break;
		case OperationGreaterEqual:
			toKill = new TargetKillNumberMoreThen(number);
			break;
		default:
			toKill = new TargetKillNumber(number);
			break;	
	}
	tasks += toKill->done();
	return true;
}
void Body::addKill(Object * id)
{
	tasks++;
	killTarget.push_back(id);
}
void Body::move(size_t fps)
{
	Rectangle col = collisionSize();
	col.x += movement.position_in_map.x;
	col.y += movement.position_in_map.y;
	for(size_t i =0; i<targets.size(); i++)
	{
		if (targets[i]->getOk())
			continue;
		if (targets[i]->tellPosition().overlaps(col) //spolieham sa na skratene vyhodnocovanie
			&& targets[i]->setOk())
			{
				tasks--;
			}
	}
	Object::move(fps);
}

void Body::addVisit(TargetVisit * target)
{
	tasks++;
	targets.push_back(target);
}
void Body::addVisitSeq(std::vector<TargetVisit *> ids)
{
	tasks++;
	targets.push_back(new TargetVisitSequence(ids));
}

//TODO is blocking cez premennu aby som nemusela pretazovat funkciu

bool Body::is_blocking()
{
	return true;
}
int Body::see()
{
	//robime to drsne, ziadna heuristika
	//TODO zamysliet sa nad tm, ci je to vhodne upravit
	
	seer.reset( toRadians( movement.angle ) );
	 
	Position diff(seer.size, seer.size);
	Position up = get_pos();
	up+= diff;

	Position down = get_pos().substractVector(diff);

	up.x/=BOX_WIDTH;
	up.y/=BOX_HEIGHT;
	down.x/=BOX_WIDTH;
	down.y/=BOX_HEIGHT;
	
	if(up.x > map->boxesInRow)
		up.x = map->boxesInRow;
	if(up.y > map->boxesInColumn)
		up.y = map->boxesInColumn;
	if (down.x <0)
		down.x = 0;
	if (down.y < 0)
		down.y = 0;
	for (int i = down.x; i<=up.x; i++)
		for (int j = down.y; j <= up.y; j++)
		{
			for (std::list<Object *>::iterator iter = map->map[i][j].objects[0].begin();
					iter != map->map[i][j].objects[0].end(); iter++)
			{
				if ( *iter == this )
					continue;
				seer.fill(*iter, this);
			}
			for (std::list<Object *>::iterator iter = map->map[i][j].objects[1].begin();
					iter != map->map[i][j].objects[1].end(); iter++)
			{
				if ( *iter == this )
					continue;
				seer.fill(*iter, this);
			}
		}

	return seer.checkVisibility();
}
Object * Body::eye(int index)
{
	TEST("Getting object from fills")
	Object * o = seer.getObject(index);
	if (!o)
		return this; //TODO dummy object
	return o;
}
void Body::place (Map * m, Position p, int angle)
{
	Object::setPosition(p, angle);
	map = m;
}
std::string Body::initTargetPlaces()
{
	size_t i = 0;
	std::string warning;
	while (i < targets.size())
	{
		do
		{
			int id = targets[i]->tellId();
			if (id < 0)
				break;
			bool set = false;
			for ( std::list<Place>::iterator k = map->places.begin(); k != map->places.end(); k++)
			{
				if (k->id != id)
					continue;
				set = true;
				targets[i]->initPosition(k->r);
				break;
			}
			if (!set)
			{
				targets[i]->setOk(); //TODO check, whether it works!
				warning += "There is no number " + deconvert<int>(id) + "defined in this map, ignoring";
			}
		}
		while (true);
		targets[i]->reset();
		i++;
	}
	return warning;
}
int Body::step(int steps)
{
	//TODO presunut to do movementu
	movement.steps = steps * movement.speed;
	state_ = 0;
	skinWork->switch_state(ImageSkinWork::StatePermanent, ActionWalk);
	return 0;
}
int Body::step()
{
	step(default_steps);
	return 0;
}
int Body::turnL()
{
	turn(-90);
	return 0;
}
int Body::turnR()
{
	TEST("Turning right")
	turn(90);
	return 0;
}
int Body::wait(int x)
{
	TEST("Waiting " << x << "times" )
	return 0;
}
int Body::shoot(int angle)
{
	TEST("Shooting at angle [ " << angle)
	if (ammo.empty())
	{
		TEST("Prazdne ammo!")
		return 0;
	}
	skinWork->switch_state(ImageSkinWork::StateTemporarily, ActionAttack);
	Position mP = this->get_pos();
	
	Position p = skinWork->head();
	mP.x += p.x;
	mP.y += p.y;

	Object * o= *ammo.begin();
	o->hitpoints = o->movement.steps = mHealth;
	o->movement.angle = movement.angle;
	o->movement.direction = movement.direction;
	o->movement.speed = 50;
	o->movement.position_in_map = mP;
	o->movement.realX = 0;
	o->movement.realY = 0;
	o->owner = this;
	o->turn(angle);

	if (map->checkCollision(o))
	{
		TEST("moc blizko steny!")
		return 0; //ak to mieni kychnut na stenu
	}
	map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects[0].splice(
	map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects[0].begin(),ammo,ammo.begin());
	return 1;
}
void Body::killed(Object * o)
{
	for (size_t i = 0; i< killTarget.size(); i++)
	{
		if (killTarget[i] == o)
		{
			killTarget[i] = killTarget.back();
			killTarget.pop_back();
			break;
		}
	}
	if (toKill!=NULL)
		tasks -= toKill->fullfilled();
}
void Body::hitted(Object * attacker, Position p, int attack)
{
	TEST("zasiahnuty!")
	state_ = movement.steps; //kolko mu este chybalo spravit
	Object::hitted(attacker,p,attack);
	int hpLost = (attack > defense) ? attack-defense:1;
	hitpoints -= hpLost;
	if (hitpoints <= 0)
	{
		hitpoints =1;
		attacker->killed(this);
		Object::dead();// prasaaaaaarna
	}
	TEST("Aktualne hitpoints" << hitpoints)
}
void Body::dead()
{
	//daj ako spracovane a moc sa tym nezatazuj
}
void Body::hit(Object * o)
{
	Position p,t;
	intersection(o,p,t);

	if (p.x < p.y)
	{
		movement.position_in_map.x -= p.x*t.x;
	}
	else
		movement.position_in_map.y -= p.y*t.y;
	if (map->collideWith(this,o))
	{
		TEST("Stale to koliduje podla mna")
		TEST(movement.position_in_map << " " )
		exit(3);
	}
}
Body::~Body()
{
	delete toKill;
	for (std::vector<Target *>::iterator i = targets.begin(); 
		i!= targets.end(); i++)
	{
		delete (*i);
	}
	targets.clear();
}
