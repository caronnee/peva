#include "../h/objects.h"
#include "../../add-ons/h/macros.h"
#include "../../add-ons/h/help_functions.h"

void ObjectMovement::clean()
{
	realX = 0;
	realY = 0;
	speed = 30;
	old_pos = position_in_map = direction = Position (0,0);
	angle = 0;
	steps = 0;
}

int Object::getAngle()const
{
	return movement.angle;
}

Object::Object(Skin * s, List * abyss)
{
	last_attack = NULL;
	abyss_ = abyss;
	type = Nothing;
	name =" Object";
	skinWork = NULL;

	objectSaveId = SaveDummy;
	numberOfKilled = 0;
	substance = Solid;
	owner = NULL;

	hitpoints = 100; 
	defense = 0;
	attack = 0;

	movement.clean();

	if (s != NULL)
		skinWork = new ImageSkinWork(s);
}

void Object::setPosition(Position p, int angle)
{
	movement.position_in_map = p;
	movement.old_pos = p;
	movement.angle = angle;
	absoluteTurn(angle);
}
bool Object::hasSkin()
{
	return skinWork != NULL;
}
bool Object::changed()
{
	return skinWork->processing();
}
void Object::setSkin(Skin * s)
{
	if (skinWork)
		delete skinWork;
	skinWork = new ImageSkinWork(s);
}
bool Object::alive()
{
	return hitpoints > 0;
}
void Object::dead()
{
	if(abyss_ != NULL)
		abyss_->push_back(this);
	skinWork->switch_state(ImageSkinWork::StatePermanent, ActionDeadStill);
	skinWork->switch_state(ImageSkinWork::StateTemporarily, ActionDead);
	movement.steps = 0;
	substance = Miss;
}

std::string Object::info() const
{
	return name;
}
//TODO zmenit na float, aby aj pre male steps to fungovalo
//TODO da sa aj krajsie?

void Object::move(size_t fps)
{
	movement.old_pos = movement.position_in_map;

	movement.realX+=(float)movement.direction.x/fps;
	movement.realY+=(float)movement.direction.y/fps;
	TEST(fps);

	Position passed(movement.realX,movement.realY);
	movement.realX-=passed.x;
	movement.realY-=passed.y;
	int stepsPass = passed.x*passed.x + passed.y*passed.y;
	if ( stepsPass >= movement.steps )
	{
		endMove();
		stepsPass = movement.steps;
		passed.x = movement.steps*movement.direction.x/MAX_PX_PER_SECOND;
		passed.y = movement.steps*movement.direction.y/MAX_PX_PER_SECOND;
	}
	movement.steps -= stepsPass;
	movement.position_in_map.x += passed.x;
	movement.position_in_map.y += passed.y;
}
void Object::endMove()
{
	skinWork->removeState();
	owner = this;
}
bool Object::is_blocking()
{
	return true;
}

SDL_Rect Object::get_rect()
{
	return skinWork->get_rect();
}

SDL_Surface * Object::show()
{
	return skinWork->get_image(); 
}
Position Object::get_size()
{
	return skinWork->getSkin()->get_size();
}
Position Object::get_pos() const
{
	return movement.position_in_map;
}
Position Object::get_old_pos() const
{
	return movement.old_pos;
}
size_t Object::width()
{
	return get_size().x;
}
size_t Object::height()
{
	return get_size().y;
}
int Object::absoluteTurn(int angle, size_t size)
{
	movement.angle = angle;
	while (movement.angle < 0)
		movement.angle+=360;
	while (movement.angle > 360)
		movement.angle-=360;
	skinWork->turn(movement.angle);  //TODO potom skontrolovat, keby to bolo pocaa chodenia
	movement.direction.turn(movement.angle, size);
	return 0;
}
int Object::turn(int angle)
{
	movement.angle+=angle;
	absoluteTurn(movement.angle);
	return 0;
}
void Object::killed(Object * o)
{
	if (owner && (owner!=this))
		owner->killed(o);
	numberOfKilled++;
}
Rectangle Object::collisionSize() const
{
	return skinWork->getCollissionRectagle();
}
void Object::hitted(Object * o, Position p, int attack)
{
	TEST("HITTED")
	skinWork->switch_state(ImageSkinWork::StateTemporarily, ActionHit);
	owner = o;
}
void Object::bounce(Object * attacked) //od koho s ma odrazit
{
	Position p(1,1);
	Position xy;
	intersection(attacked, xy, p);
	if (xy.y < xy.x)
	{
		movement.direction.y *=-1;
		movement.position_in_map.y -= p.y*xy.y * 2 - 1;
	}
	else 
	{
		movement.direction.x *=-1;
		movement.position_in_map.x -= p.x*xy.x * 2 - 1;
	}
}
void Object::hit(Object * attacked)
{
	TEST("HIT")
	attacked->hitted (this, movement.direction, attack);
}

bool Object::intersection(Object * attacked, Position &distances, Position& p)
{
	Rectangle r1 = collisionSize();
	r1.x += movement.position_in_map.x;
	r1.y += movement.position_in_map.y;

	distances.x = r1.width * r1.width;
	distances.y = r1.height * r1.height;

	Rectangle r2 = attacked->collisionSize();
	r2.x += attacked->movement.position_in_map.x;
	r2.y += attacked->movement.position_in_map.y;
	
	if (movement.direction.y > 0) // checkneme, ci sme narazili na nieco dole
	{
		p.y =1;
		int yAxis = r1.y + r1.height; //ta os, ktora nas zaujima, musi byt medzi
		if (( r2.y < yAxis ) && ( yAxis < r2.y + r2.height ))
			distances.y = yAxis - r2.y;
	}
	if (movement.direction.y < 0) //smerujeme dole
	{
		p.y = -1;
		int yAxis = r1.y; //ta os, ktora nas zaujima, musi byt medzi
		if ( ( r2.y < yAxis ) && (yAxis  < r2.y + r2.height ) )
			distances.y = r2.y + r2.height - yAxis;
	}
	if (movement.direction.x > 0) // doprava
	{
		p.x =1;
		int xAxis = r1.x + r1.width; //ta os, ktora nas zaujima, musi byt medzi
		if ((r2.x < xAxis)&&(xAxis < r2.x + r2.width))
			distances.x = xAxis - r2.x;
	}
	if (movement.direction.x <0)
	{
		p.x = -1;
		int xAxis = r1.x; //ta os, ktora nas zaujima, musi byt medzi
		if ((r2.x < xAxis)&&(xAxis < r2.x + r2.width))
			distances.x = r2.x + r2.width - xAxis;
	}
	return true; //FIXME
}

bool Object::isMoving()
{
	return movement.steps;
}
int Object::typeObject()const
{
	return type;
}
bool Object::blocksMove()
{
	return !isMoving() || skinWork->processing();
}

int Object::Hit()const
{
	return hitpoints;
}

Dummy::Dummy() : Object(NULL, NULL)
{
	type =~0;
}

int Dummy::Hit() const
{
	return random()%100;
}

bool Dummy::isMoving()
{
	return random()%2;
}

Position Dummy::get_pos() const
{
	return Position (random(),random());
}
