#include "../h/body.h"

Body::Body() : Object(NULL)
{
	tasks = false;
	name = "Robot";
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
	toKill = NULL;
}

void Body::addAmmo( Object * o)
{
	ammo.add(o->item);
	o->owner = this;
}
bool Body::addKilled(unsigned i,Operation op, size_t number)
{
	if (toKill !=NULL)
	{
	//	error(i,WarningKillAlreadyDefined);
		return false;
	}
	tasks++;
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
	return true;
}
void Body::addKill(size_t id)
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
		if (targets[i]->tellPosition().overlaps(col)&&
			targets[i]->setOk())
			tasks--;
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
	ammo.add(i); //owner jw spravny
}
void Body::addVisit(std::vector<Position> positions)
{
	for(size_t i =0; i< positions.size(); i++)
	{
		tasks++;
		targets.push_back(new TargetVisit(0));
	}
	for(size_t i = targets.size() - positions.size(); i< positions.size(); i++)
	{
		//nezalezi na poradi
		targets[i]->initPosition(positions[i]);
	}
}
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
	//TODO presunut to do movmentu
	movement.steps = steps * movement.speed;
	skinWork->switch_state(ImageSkinWork::StatePermanent, ActionHit);
	return 0;
}
int Body::step()
{
	step(default_steps);
	return 0;
}
int Body::turnL()
{
	turn(90);
	return 0;
}
int Body::turnR()
{
	std::cout << "Turning right";
	turn(-90);
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
//	getc(stdin);
	if (ammo.empty())
	{
		std::cout << "Prazdne ammo!";
		getc(stdin);
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
	ammo.data->value->movement.steps = 1500;
	ammo.data->value->movement.angle = movement.angle;
	ammo.data->value->hitpoints = 50;
	ammo.data->value->movement.direction = movement.direction;
	std::cout << "PRED:" << ammo.data->value->movement.direction<< " ";
	ammo.data->value->movement.speed = 50;
	ammo.data->value->movement.position_in_map = mP;
	ammo.data->value->movement.realX = 0;
	ammo.data->value->movement.realY = 0;
	o->turn(angle);
	std::cout << "PO:" << ammo.data->value->movement.direction<< " ";
	ammo.moveHead(map->map[mP.x/BOX_WIDTH][mP.y/BOX_HEIGHT].objects);
	std::cout << "shooted!"<<mP<< " "<<ammo.size()<<" "<<o->alive();
//	getc(stdin);
	return 0;
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
