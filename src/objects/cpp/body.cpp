#include <cmath>
#include "../h/body.h"
#include "../h/missille.h"
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"

GamePoints::GamePoints(int total)
{
	for(size_t i =0; i< NumberOfSections; i++)
	{
		sections[i] = 0;
	}
	name[SectionMissilleHitpoints] ="mHealth ";
	name[SectionAttack] = "Attack ";
	name[SectionMissilleAttack] ="mAttack ";
	name[SectionMemorySize] = "Memory: ";
	name[SectionAngle] = "Angle ";
	name[SectionHitpoints] = "Hitpoints ";
	name[SectionMissilles] = "Missilles ";
	name[SectionSteps] = "Speed ";
	total_ =  total;
}

void GamePoints::check() //budeme kontrolovat len ak to presvihlo pocet, FIXME dalsia volba, aby to doplnovalo
{
	sections[GamePoints::SectionAngle] = min<int>(MAX_EYE_ANGLE,sections[GamePoints::SectionAngle]);

	int todo = 0;

	for(size_t i =0; i< NumberOfSections; i++)
	{
		todo += sections[i];
	}
	for(size_t i =0; i< NumberOfSections; i++)
	{
		sections[i]* (total_/todo);
	}
}

Body::Body() : Object(NULL,NULL)
{
	type = Player;
	waits = 0;
	state_ = 0;
	ms = NULL;
	tasks = 0;
	name = "Robot";
	movement.old_pos.x = 30;
	movement.old_pos.y = 130;
	movement.position_in_map = movement.old_pos;
	movement.speed = 30;
	movement.angle = 0;
	movement.direction.x = 50;
	toKill = NULL;
	map = NULL;
}
Skin * Body::getSkin()const
{
	return skinWork->getSkin();
}
std::string Body::info()
{
	std::string output;
	//hitpoints
	if (hitpoints > 0)
		output += "\tHitpoints :" + deconvert<int> (hitpoints);
	else 
		output+= "\tDead.";
	if (toKill)
		output += toKill->state();
	for (size_t i =0; i < targets.size(); i++)
		output += targets[i]->state();
	return output+"\n";
}
void Body::init(GamePoints g, int v)
{
	points = g;
	turn(0);
	/* information from firt section */
	seer.setEyes(g.sections[GamePoints::SectionAngle],v);
	hitpoints = g.sections[GamePoints::SectionHitpoints];
	movement.speed = g.sections[GamePoints::SectionSteps]%100;


	/* second section information */
	if(!hasSkin())
		throw "Robot body is not skined!";
	if (!ms)
		ms = new MissilleSkin(skinWork->getSkin()->nameOfSet);
	for (int i =0; i< g.sections[GamePoints::SectionMissilles]; i++ )
		addAmmo(new Missille(ms,&ammo));
	attack =g.sections[GamePoints::SectionAttack];
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
		tasks += toKill->check();
		delete toKill;
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
			toKill = new TargetKillNumberLessEqual(number);
			break;
		case OperationGreater:
			toKill = new TargetKillNumberMore(number);
			break;
		case OperationGreaterEqual:
			toKill = new TargetKillNumberMoreEqual(number);
			break;
		default:
			toKill = new TargetKillNumber(number);
			break;	
	}
	tasks -= toKill->check();
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
	if (map == NULL)
		return 0;
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

	size_t y= seer.checkVisibility();
	seer.output();
	return y;
}
Object * Body::eye(int index)
{
	TEST("Getting object from fills")
	Object * o = seer.getObject(index);
	return o;
}
void Body::place (Map * m, Position p, int angle)
{
	Object::setPosition(p, angle);
	map = m;
}
int Body::getTasks()const
{
	return tasks;
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
			if (id < 0) //not on map
				break;
			if (targets[i]->getOk()) //not found on map
				break;

			bool set = false, done;
			for ( std::list<Place>::iterator k = map->places.begin(); k != map->places.end(); k++)
			{
				if (k->id != id)
					continue;
				set = true;
				done = targets[i]->initPosition(k->r);
				break;
			}
			if (!set)
			{
				if(targets[i]->setOk()) 
					tasks--;
				warning += "There is no number " + deconvert<int>(id) + "defined in this map, ignoring\n";
			}
			if (done)
				break;
		}
		while (true);
		targets[i]->reset();
		i++;
	}
	tasks = 0;
	for (size_t i =0; i< targets.size(); i++)
	{
		if (!targets[i]->getOk())
			tasks++;
	}
	tasks+= killTarget.size();
	if (toKill!=NULL)
		tasks+=toKill->check();
	if ((tasks == 0 )&& (toKill == NULL))
		tasks = 1;
	return warning;
}
int Body::step(int steps)
{
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
	state_ = 0;
	TEST("Waiting " << x << "times" )
	waits = x;
	return 0;
}
int Body::shoot(int angle)
{
	TEST("Shooting at angle " << angle)
	if (ammo.empty())
	{
		TEST("Empty ammo!")
		return 0;
	}
	skinWork->switch_state(ImageSkinWork::StateTemporarily, ActionAttack);
	Position mP = this->get_pos();
	

	Object * o= *ammo.begin();

	Position p = skinWork->head();
	mP.x += p.x;
	if (movement.direction.x < 0)
		mP.x -= o->width();
	
	mP.y += p.y;
	if (movement.direction.y < 0)
		mP.y -= o->height();
	
	o->hitpoints = o->movement.steps = points.sections[GamePoints::SectionMissilleHitpoints];
	o->attack = points.sections[GamePoints::SectionMissilleAttack];
	o->defense = 0;
	o->movement.angle = movement.angle;
	o->movement.direction.x = movement.direction.x;
	o->movement.direction.y = movement.direction.y;
	o->movement.speed = 100;
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
			tasks--;
			break;
		}
	}
	if ((toKill!=NULL)&&(o->typeObject()&Player))
		tasks -= toKill->fullfilled();
}
void Body::hitted(Object * attacker, Position p, int attack)
{
	state_ = movement.steps + waits; //kolko mu este chybalo spravit
	waits = 0;
	Object::hitted(attacker,p,attack);
	int hpLost = (attacker->attack > defense) ? attack-defense:1;
	hitpoints -= hpLost;
	if (hitpoints <= 0)
	{
		substance = Miss;
		attacker->killed(this);
		Object::dead();
	}
}
void Body::dead()
{
	//daj ako spracovane a moc sa tym nezatazuj
	Position p = get_pos();
	p.x /= BOX_WIDTH;
	p.y /= BOX_HEIGHT;
	map->map[p.x][p.y].objects[1-map->processing].push_back(this);
}
void Body::hit(Object * o)
{
	Position p(-11111,-11111),t(-11111,-11111);
	intersection(o,p,t);

	ObjectMovement th = movement;
	ObjectMovement obj = o->movement;
	Object::hit(o);
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
		throw "New position after collision is not counted properly. Please, report the bug :)";
	}
}
int Body::getDirection(Position position)
{
	Position p = position;
	p.substractVector(get_pos());

	p.x -= getSkin()->get_shift().x/2;
	p.y -= getSkin()->get_shift().y/2;
	
	Position t(movement.direction);
	float f;

	int dotProd = sqrt((double)p.x * p.x + p.y*p.y)*sqrt((double)t.x*t.x+t.y*t.y);
	if (dotProd == 0)
		return 0;

	f = (p.x*t.x + t.y*p.y) / (float)dotProd;
	int res = toDegree(acos(f));
	if ( p.y*t.x - p.x*t.y < 0) //ak na druhej strane zorneho pola
		res = 360 - res; //pretoze sa otazam v mere divnom
	return res;
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
