#include "../h/body.h"
#include "../../add-ons/h/macros.h"

Body::Body() : Object(NULL)
{
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
	std::cout << "Filling in object see area";
	return 0;
}
Object * Body::eye(int index)
{
	std::cout << "Getting object from fills";
	return this;
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
	std::cout << "Turning right";
	turn(90);
	return 0;
}
int Body::wait(int x)
{
	std::cout << "Waiting " << x << "times" ;
	return 0;
}
int Body::shoot(int angle)
{
	std::cout << "Shooting at angle [ " << angle <<std::endl;
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
	Object::hit(o);
	Rectangle r1 = collisionSize();
	r1.x += get_pos().x;
	r1.y += get_pos().y;

	Rectangle r2 = o->collisionSize();
	r2.x += o->get_pos().x;
	r2.y += o->get_pos().y;

	//vrat to do najblizsej normalnej pozicii
	//normalizujem
	Position hlpDir = movement.direction;
	if (hlpDir.x!=0)
		hlpDir.x/hlpDir.x;
	if (hlpDir.y!=0)
		hlpDir.y/hlpDir.y;

	if (movement.direction.x != 0)
	{
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
