#include "objects.h"

Object::Object()
{
	ticks = 100; // TODO
	name =" Object";
}

bool Object::is_blocking()
{
	return false;
}

Position Object::get_pos() const
{
	return movement.position_in_map;
}

SDL_Surface * Object::show()
{
	return image; 
}

void Object::action(Map * m) {}

bool Object::collideWith(Object * o, Position& collisionVector) // pouzitelne iba pre vzajomne walls
{
	Rectangle r1;
	r1.x = movement.position_in_map.x;
	r1.y = movement.position_in_map.y;
	r1.width = image->w;
	r1.height = image->h;
	Rectangle r2;
	r2.x = o->get_pos().x; //TODO vlastna fce overlaps
	r2.y = o->get_pos().y;
	r2.width = o->show()->w;
	r2.height = o->show()->h;
	if (!(r1.x > r2.x + r2.width) //metoda separating axis?
		&& !(r1.x + r1.width < r2.x)
		&& !(r1.y > r2.y + r2.height)
		&& !(r1.y + r1.height < r2.y))	
	{
		//nastala kolizia

		collisionVector = movement.direction; //pre druhy object, tento sa iba odrazi
		
		Position perpVector(movement.old_pos.y - movement.position_in_map.y, movement.position_in_map.x-movement.old_pos.x);//Ax +By = c;
		int c = 0;
		c-=perpVector.x*(movement.old_pos.x+image->w/2) + perpVector.y*(movement.old_pos.y - image->h/2); //priamka cez stred
		Position del;
		if(movement.old_pos.x < movement.position_in_map.x)
		{
			if ( movement.old_pos.y < movement.position_in_map.y) // sikmo hore doprava
			{
				del.x = o->movement.position_in_map.x; //horny roh, ok
				del.y = o->movement.position_in_map.y - o->show()->h;
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazil na bocnu stenu
				{
		//			return false;
//					std::cout << "here!" << std::endl;
					movement.direction.x *= -1; 
					movement.position_in_map.x += del.x - movement.position_in_map.x - image->w;
				}
				else
				{
					movement.direction.y *=-1;
					movement.position_in_map.y = 2* del.y - movement.position_in_map.y;
				}

			}
			else //sikmo dole doprava
			{
				return false;
		/*		del.x = o->movement.position_in_map.x;
				del.y = o->movement.position_in_map.y;
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazila na hornu stenu
				{
					movement.direction.x *=-1;
					movement.position_in_map.x = 2* del.x - movement.position_in_map.x;
				}
				else
				{
					movement.direction.y *=-1;
					movement.position_in_map.y = 2* del.y - movement.position_in_map.y - image->h;
				}
				*/
			}
		}
		else
		{
		/*	if ( movement.old_pos.y < movement.position_in_map.y) // sikmo hore dolava
			{
				del.x = o->movement.position_in_map.x;
				del.y = o->movement.position_in_map.y;
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazil na bocnu stenu
				{	
					movement.direction.x *=-1;
					movement.position_in_map.x = 2* del.x - movement.position_in_map.x - image->w;
				}
				else
				{
					movement.direction.y *=-1;
					movement.position_in_map.y = 2* del.y - movement.position_in_map.y;
				}
			}
			else //sikmo dole dolava
			{
				del.x = o->movement.position_in_map.x;
				del.y = o->movement.position_in_map.y - o->show()->h;
				if (perpVector.x*del.x + perpVector.y*del.y + c < 0 ) //narazila na hornu stenu
				{
					movement.direction.y *=-1;
					movement.position_in_map.y = 2* del.y - movement.position_in_map.y - image->h;
				}
				else
				{
					movement.direction.x *=-1;
					movement.position_in_map.x = 2* del.x - movement.position_in_map.x;
				}
			}*/
			return false;
		}
//		movement.direction.x = (o->movement.direction.x + movement.direction.x)/2;
//		movement.direction.y = (o->movement.direction.y + movement.direction.y)/2;
		return true; //mame tu iba obdlzniky a ziadne kruhy, takze kolizny vektor bude v smere utocnika

	}
	return false;
}
void Object::collision(Position collidedVector)
{
	movement.direction.x = 0;
	movement.direction.y = 0;
}
int Object::IsMoving(){
	return 0;
}
int Object::IsWall()
{
	return 0;
}
int Object::IsPlayer()
{ 
	return 0;
}
int Object::IsMissille()
{
	return 0;
}
int Object::Locate() //TODO bude vraciac position
{
	return 0;
}
int Object::Hit()
{
	return 0;
}
