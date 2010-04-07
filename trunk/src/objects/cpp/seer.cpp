#include <cmath>
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../h/seer.h"

#define FLOAT_COMP_ZERO -0.1
Seer::Seer()
{
	setEyes(0,0); //slepy :)
}

int Seer::getDegree(Object * o, Position point)
{
	float a = getRadian(o, point);
	return a*180/PI;
}
float Seer::getRadian(Object * o, Position point)
{
	float angle = 0.0;
	point.substractVector(o->get_pos());
	point.x -= o->collisionSize().x + o->collisionSize().width/2;
	point.y -= o->collisionSize().y + o->collisionSize().height/2;
	//FIXME
	//zistime kvadrant, 0,1,2,3, vzhladom na suradnice
	int kvadr = 0;
	if (point.y * point.x < 0)
		kvadr = 1;
	if (point.y < 0)
		kvadr |= 2;
	if (point.y != 0)
		angle =atan((float)point.y/point.x);
	if (kvadr &1)
		angle+=PI/2;
	angle += kvadr*PI/2;
	return angle;
}
void Seer::setEyes(int angle, int visibility)
{
	//prevedieme do radianu
	while (angle < 0)
		angle +=90;
	angle %= 90;
	angleBegin_ = toRadians ( -angle );
	angleEnd_ = toRadians ( angle );
	if (angleBegin_ > angleEnd )
	{
		angleBegin_ -=2*PI;
	}
	size = visibility;
}
void Seer::setEyes(Position eyeDimension)
{
	if (eyeDimension.x < 0)
		eyeDimension.x*=-1;
	if (eyeDimension.y <0)
		eyeDimension.y *=-1;
	size = sqrt(eyeDimension.x*eyeDimension.x+eyeDimension.y+eyeDimension.y);
	float a = tan(eyeDimension.y / eyeDimension.x);
	angleBegin_ = PI/2 - a;
	angleEnd_ = PI/2 + a;
	reset(0.0);
}
void Seer::reset(float angle) 
{
	angleBegin = angle + angleBegin_;
	angleEnd = angle + angleEnd_;	
	while (angleBegin > 2*PI)
		angleBegin -= 2*PI;
	while (angleEnd > 2*PI)
		angleEnd -= 2*PI;
	if(angleBegin > angleEnd)
		angleBegin -= 2*PI;
	visibleObjects.clear();
}

void Seer::output()
{
	TEST("Vidim "<< visibleObjects.size() << "objektov: ")
	for (std::list<ObjectRelation>::iterator i = visibleObjects.begin();
		 i!= visibleObjects.end();
		 i++)
	{
		TEST(i->object->info())
	}
}

void Seer::addToVisible(ObjectRelation& relation)
{
	std::list<ObjectRelation>::iterator iter = visibleObjects.begin();
	while (iter!=visibleObjects.end())	
	{
		Rectangle r = (*iter).rect;
		if (r.y > relation.rect.y)
		{
			visibleObjects.insert(iter,relation);
			break;
		}
		iter++;
	}
	if (iter == visibleObjects.end())
		visibleObjects.push_back(relation);
}

void Seer::fill(Object * o, Object * center) //position = centre
{
	Position position = center->get_pos();
	position.x += center->collisionSize().x + (center->collisionSize().width >> 1);
	position.y += center->collisionSize().y + (center->collisionSize().height >> 1);

	Position objectPosition = o->get_pos();

	objectPosition.x += o->collisionSize().x 
		+ (o->collisionSize().width >>1);
	objectPosition.y += o->collisionSize().y 
		+ (o->collisionSize().height >>1);

	objectPosition.substractVector(position); //hodime to do osy s pociatkom (0,0)
	size_t dist = (size_t) objectPosition.x * objectPosition.x
		+ objectPosition.y * objectPosition.y;
	if ( dist > size*size)
		return; //nie je v kruhu

	ObjectRelation relation;
	relation.object = o;
	relation.angleBegin = angleBegin;
	relation.angleEnd = angleEnd;
	relation.rect.x = o->get_pos().x + o->collisionSize().x;
	relation.rect.y = o->get_pos().y + o->collisionSize().y;
	relation.rect.width = o->collisionSize().width;
	relation.rect.height = o->collisionSize().height;

	float a1 = 100.0 , a2 = -100.0; ///vhodne nekonecno
	objectPosition.x = relation.rect.x;
	objectPosition.y = relation.rect.y;
	//check angles through all corners
	for (int i =0; i<2; i++)
	{
		for (int j = 0; j<2; j++)
		{
			float a = getRadian(center, objectPosition);
			//int u = toDegree(a);
			a1 = min<float> (a1,a);
			a2 = max<float> (a,a2);
			objectPosition.y += relation.rect.height;
		}
		objectPosition.x += relation.rect.width;
		objectPosition.y = relation.rect.y;
	}
	if ((a2 - angleBegin >PI)) //staci nam PI,  ze to presiahlo 90*
	{
		a2 -= 2*PI; //dame do zaporu
	}
	if ( a1 - angleBegin > PI)
	{
		a1 -= 2*PI; //dame do zaporu
	}
	float aa1 = a1, aa2=a2;
	a1=min<float>(aa1,aa2);
	a2=max<float>(aa1,aa2);

	if (((angleBegin <= a1)
		 && (angleEnd >= a1))
	||((angleBegin <= a2) 
		&& (angleEnd >= a2 ))
	|| ((a1 <= angleBegin)
		&& (angleBegin <= a2))) //FIXME fo funkcie
	{
		relation.angleBegin = max<float> (relation.angleBegin, a1);
		relation.angleEnd = min<float> (relation.angleEnd, a2);
		relation.distance = dist;
		std::list<ObjectRelation>::iterator ins = visibleObjects.begin();
		while (ins!=visibleObjects.end())
		{
			if((*ins).distance > dist )
				break;
			ins++;
		}
		visibleObjects.insert(ins, relation);
		for (ins = visibleObjects.begin(); ins!=visibleObjects.end(); ins++)
			TEST(" " << (*ins).distance)
	}
}
int Seer::checkVisibility()
{
	//mame vsetky objekty zoradene podla Y osy
	std::list<ObjectRelation>::iterator iter = visibleObjects.begin();
	//vyhodime vsetky, co su neviditelne
	TEST(visibleObjects.size())
	while(iter!=visibleObjects.end())
	{
		if ((*iter).angleBegin - (*iter).angleEnd > FLOAT_COMP_ZERO) //kvoli nepresnosto floatov
		{
			TEST("mazem")
			iter = visibleObjects.erase(iter);
			continue;
		}
		if (!(*iter).object->is_blocking())
		{
			iter ++;
			continue;
		}

		//checkni, comu vsetkemu brani
		std::list<ObjectRelation>::iterator i = iter;
		i++;
		float beg = (*iter).angleBegin;
		float end = (*iter).angleEnd;
		while (i!=visibleObjects.end())
		{
			if ( ( beg < (*i).angleBegin ) && ( (*i).angleBegin < end ) )
				(*i).angleBegin = end;
			if ( ( beg < (*i).angleEnd ) && ( (*i).angleEnd < end ) )
				(*i).angleEnd = beg;
			i++;
		}
		iter++;
	}
	return visibleObjects.size();
}

Object * Seer::getObject(size_t index)
{
	if (index >= visibleObjects.size())
		return NULL;
	std::list<ObjectRelation>::iterator r = visibleObjects.begin();
	for (size_t i = 0; i<index; i++)
		r++;
	return (*r).object;
}
