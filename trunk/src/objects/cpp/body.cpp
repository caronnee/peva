#include <cmath>
#include "../h/body.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

Body::Body() : Object(NULL)
{
	type = Player;
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
void Body::bounce(Object * from)
{
	//no bouncing
}
void Body::addAmmo( Object * o)
{
	ammo.add(o->item);
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
void Body::move()
{
	Rectangle col = collisionSize();
	col.x += movement.position_in_map.x;
	col.y += movement.position_in_map.y;
	for(size_t i =0; i<targets.size(); i++)
	{
		if (targets[i]->fullfilled())
			continue;
		if (targets[i]->tellPosition().overlaps(col) //spolieham sa na skratene vyhodnocovanie
			&& targets[i]->setOk())
			{
				tasks--;
			}
	}
	Object::move();
}

void Body::addVisit(TargetVisit * target)
{
	tasks++;
	targets.push_back(target);
}
void Body::addVisitSeq(std::vector<Position> positions)
{
	tasks++;
	targets.push_back(new TargetVisitSequence(positions));
}
void Body::addVisitSeq(std::vector<TargetVisit *> ids)
{
	tasks++;
	targets.push_back(new TargetVisitSequence(ids));
}
void Body::addAmmo( Item * i)
{
	ammo.add(i); //owner je spravny
}
void Body::addVisit(std::vector<Position> positions)
{
	for(size_t i =0; i< positions.size(); i++)
	{
		tasks++;
		targets.push_back(new TargetVisit(0));
	}
	for(size_t i = targets.size()-1;  !positions.empty(); i--)
	{
		//nezalezi na poradi
		targets[i]->initPosition(positions.back());
		positions.pop_back();
	}
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
			map->map[i][j].objects.reset();
			Object * o =map->map[i][j].objects.read();
			while (o!=NULL)
			{
				if ( o == this )
				{
					o = map->map[i][j].objects.read();
					continue;
				}
				seer.fill(o, this);
				o = map->map[i][j].objects.read();
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
	if (ammo.data->value == NULL)
		ammo.next();
	mP.x += p.x;
	mP.y += p.y;

	Object * o= ammo.data->value;
	ammo.data->value->movement.steps = 150;
	ammo.data->value->movement.angle = movement.angle;
	ammo.data->value->hitpoints = 50;
	ammo.data->value->movement.direction = movement.direction;
	ammo.data->value->movement.speed = 50;
	ammo.data->value->movement.position_in_map = mP;
	ammo.data->value->movement.realX = 0;
	ammo.data->value->movement.realY = 0;
	ammo.data->value->owner = this;
	o->turn(angle);

	if (map->checkCollision(ammo.data->value))
	{
		TEST("moc blizko steny!")
		return 0; //ak to mieni kychnut na stenu
	}
	ammo.moveHead(map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects);
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
		attacker->killed(this);
		Object::dead();// prasaaaaaarna
	}
	TEST("Aktualne hitpoints" << hitpoints)
}
void Body::dead()
{
	map->add(this);
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
