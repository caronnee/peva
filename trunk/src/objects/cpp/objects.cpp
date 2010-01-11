#include "../h/objects.h"
#include <cmath>

#define MAX_PX_PER_SECOND 300
#define PI 3.14159265

Object::Object()
{
	owner = NULL;
	assistance = this;
	item = new Item(this);
	hitpoints = 100; //TODO zmenit
	/* item containing this object */
	Item * item;
	name =" Object";
	skinWork = NULL;
	movement.position_in_map.x = 0;
	movement.position_in_map.y = 0;
	movement.old_pos = movement.position_in_map = Position (0,0);
	movement.direction.x = 0;
	movement.direction.y = 0;
	movement.angle = 0;
	movement.speed = 30;
	movement.fps = 200;
	movement.steps = 0;
}

void Object::setPosition(Position p, int angle)
{
	movement.position_in_map = p;
	movement.old_pos = p;
	movement.angle = 0;
	turn(angle);
}
bool Object::hasSkin()
{
	return skinWork != NULL;
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
	/* set skin to die
	skinWork->removeState();
	*/
}
//TODO zmenit na float, aby aj pre male steps to fungovalo
//TODO da sa aj krajsie
void Object::move()
{
	movement.old_pos = movement.position_in_map;
	
	Position passed(movement.direction.x/movement.fps,movement.direction.y/movement.fps);
	int stepsPass = passed.x*passed.x + passed.y*passed.y;
	if (stepsPass >= movement.steps) //ak skonci, potom zrus chodiaci imidz
	{
		std::cout << "removing state after finishong movement";
	//	getc(stdin);
		skinWork->removeState();
		stepsPass = movement.steps;
		passed.x = movement.steps*movement.direction.x/MAX_PX_PER_SECOND;
		passed.y = movement.steps*movement.direction.y/MAX_PX_PER_SECOND;
	}
	movement.steps -= stepsPass;
	movement.position_in_map.x += passed.x;
	movement.position_in_map.y += passed.y;
}

bool Object::is_blocking()
{
	return false;
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
	return skinWork->get_size();
}
Position Object::get_pos() const
{
	return movement.position_in_map;
}
size_t Object::width()
{
	return skinWork->width();
}
size_t Object::height()
{
	return skinWork->height();
}
int Object::turn(int angle)
{
	movement.angle+=angle;
	while (movement.angle < 0)
		movement.angle+=360;
	while (movement.angle > 360)
		movement.angle-=360;
	skinWork->turn(movement.angle);  //potom skontrolovat, keby to blo pocat chodenia
	movement.direction.x = sin(movement.angle*PI/180)*MAX_PX_PER_SECOND ;
	movement.direction.y = -cos(movement.angle*PI/180)*MAX_PX_PER_SECOND;
	return 0;
}
bool Object::collideWith(Object * o, Position& collisionVector) // pouzitelne iba pre vzajomne walls, zatial
{
	return false;
	Rectangle r1;
	r1.x = movement.position_in_map.x;
	r1.y = movement.position_in_map.y;
	r1.width = skinWork->width();
	r1.height = skinWork->height();
	Rectangle r2;
	r2.x = o->get_pos().x; //TODO vlastna fce overlaps
	r2.y = o->get_pos().y;
	r2.width = o->get_size().x;
	r2.height = o->get_size().y;
	if (!(r1.x >= r2.x + r2.width) //metoda separating axis?
		&& !(r1.x + r1.width <= r2.x)
		&& !(r1.y >= r2.y + r2.height)
		&& !(r1.y + r1.height <= r2.y))	
	{
		//nastala kolizia

		collisionVector = movement.direction; //pre druhy object, tento sa iba odrazi
		
		Position perpVector(movement.old_pos.y - movement.position_in_map.y, movement.position_in_map.x-movement.old_pos.x);//Ax +By = c;
		int c = 0;
//		c-=perpVector.x*(movement.old_pos.x+image->w/2) + perpVector.y*(movement.old_pos.y - image->h/2); //priamka cez stred
		Position del;
		if(movement.old_pos.x < movement.position_in_map.x)
		{
		//	return false;
			if ( movement.old_pos.y < movement.position_in_map.y) // sikmo dole doprava
			{
				c-=perpVector.x*(movement.old_pos.x+skinWork->width() + perpVector.y*(movement.old_pos.y + skinWork->height())); //priamka pravy dolny roh
				del.x = o->movement.position_in_map.x; //lavy horny roh, ok
				del.y = o->movement.position_in_map.y;
			//	std::cout << perpVector << " c:" << c << std::endl;
			//	std::cout << del << std::endl;
			//	std::cout << perpVector.x*(movement.position_in_map.x+image->w) + perpVector.y*(movement.position_in_map.y - image->h);
				if (perpVector.x*del.x + perpVector.y*del.y + c > 0 ) //narazil na hornu stenu
				{
					std::cout << "I horna stena" << std::endl;
					movement.direction.y *=-1;
				//	std::cout << "Menim poziciu o:" <<movement.position_in_map.y + image->h - del.y  << std::endl;
					movement.position_in_map.y -= movement.position_in_map.y + skinWork->height() - del.y;
				//	std::cout << "PO: direction:" << movement.direction << std::endl;
				}
				else
				{
					std::cout << "I bocna stena" << std::endl; //narazil na lavu bocnu stenu
				//	return false;
					movement.direction.x *= -1; 
					movement.position_in_map.x -= del.x - movement.position_in_map.x - skinWork->width();
				//	std::cout << "here:" << movement.position_in_map << ", direction:" << movement.direction << " o:" << o->movement.position_in_map << "direction"<< o->movement.direction << std::endl;
				}

			}
			else //sikmo hore doprava
			{
		//		return false;
			//	std::cout << "id:" << this << ", kolidujuca pozicia: " << movement.position_in_map << std::endl;
				del.x = o->movement.position_in_map.x;
				del.y = o->movement.position_in_map.y + o->height(); 
				c-=perpVector.x*(movement.old_pos.x + skinWork->width()) + perpVector.y*(movement.old_pos.y); //priamka pravy horny roh
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazila na dolnu stenu
				{
					std::cout << "II vrch" << std::endl;
					movement.direction.y *=-1;
					movement.position_in_map.y = 2*del.y - movement.position_in_map.y; //TODO check
				}
				else
				{
					//return false;
					std::cout << "II bok" << std::endl;
					movement.direction.x *=-1;
					movement.position_in_map.x += del.x - movement.position_in_map.x - skinWork->width();
				}	
			}
		}
		else
		{
			if ( movement.old_pos.y < movement.position_in_map.y) // sikmo dole dolava
			{
			//	return false;
				del.x = o->movement.position_in_map.x+o->width();
				del.y = o->movement.position_in_map.y;
				c-=perpVector.x*(movement.old_pos.x) + perpVector.y*(movement.old_pos.y + skinWork->height()); //priamka pravy horny roh
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazil na bocnu stenu
				{	
					std::cout << "III vrch" << std::endl;
					movement.direction.y *=-1;
					movement.position_in_map.y -= movement.position_in_map.y + skinWork->height() - del.y;
				}
				else
				{
					std::cout << "III bok" << std::endl;
					movement.direction.x *=-1;
					movement.position_in_map.x = 2*del.x - movement.position_in_map.x;
				}
			}
			else //sikmo dole dolava
			{
			//	return false;
				//TESTED
				c-=perpVector.x*(movement.old_pos.x) + perpVector.y*(movement.old_pos.y); //priamka pravy horny roh
				del.x = o->movement.position_in_map.x + o->width();
				del.y = o->movement.position_in_map.y + o->height();
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazila na hornu stenu
				{
					std::cout << "IV bok" << std::endl;
				//	std::cout << "uch! bocna stena" << std::endl;
					movement.direction.x *=-1;
					movement.position_in_map.x += del.x - movement.position_in_map.x ;
				}
				else
				{
					std::cout << "IV vrch" << std::endl;
					movement.direction.y *=-1;
					movement.position_in_map.y = 2*del.y - movement.position_in_map.y;
				}
			}
		}
//		movement.direction.x = (o->movement.direction.x + movement.direction.x)/2;
//		movement.direction.y = (o->movement.direction.y + movement.direction.y)/2;
		std::cout << "id:" << this << ", zmenena pozicia: " << movement.position_in_map << "\t";
		std::cout << "colid id:" << o << ", pozicia: " << o->get_pos() << std::endl;
		return true; //mame tu iba obdlzniky a ziadne kruhy, takze kolizny vektor bude v smere utocnika

	}
	return false;
}
void Object::collision(Position collidedVector)
{
	movement.direction.x = 0;
	movement.direction.y = 0;
;}
bool Object::isMoving(){
	return movement.steps;
}
int Object::isWall()
{
	return 0;
}
int Object::isPlayer()
{ 
	return 0;
}
bool Object::blocksMove()
{
	return !isMoving() || skinWork->processing();
}

int Object::isMissille()
{
	return 0;
}
Position Object::Locate() //TODO bude vraciac position
{
	return get_pos();
}
int Object::Hit()
{
	return 0;
}
