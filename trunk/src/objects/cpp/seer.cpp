#include <cmath>
#include "../../add-ons/h/help_functions.h"
#include "../../add-ons/h/macros.h"
#include "../h/seer.h"

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
	angleBegin_ = toRadians ( 90 - angle );
	angleEnd_ = toRadians ( 90 + angle );
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
	visibleObjects.clear();
}

void Seer::output()
{
	std::cout << "Vidim "<< visibleObjects.size() << "objektov: " <<std::endl;
	for (std::list<ObjectRelation>::iterator i = visibleObjects.begin();
		 i!= visibleObjects.end();
		 i++)
	{
		std::cout << i->object->info();
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
	position.x += center->collisionSize().x + center->collisionSize().width >> 1;
	position.y += center->collisionSize().y + center->collisionSize().height >> 1;

	Position objectPosition = o->get_pos();

	objectPosition.x += o->collisionSize().x 
		+ o->collisionSize().width >>1;
	objectPosition.y += o->collisionSize().y 
		+ o->collisionSize().height >>1;

	objectPosition.substractVector(position); //hodime to do osy s pociatkom (0,0)
	if (objectPosition.x * objectPosition.x
		+ objectPosition.y * objectPosition.y
		> size*size)
		return; //nie je v kruhu

	ObjectRelation relation;
	relation.object = o;
	relation.invisible = 0;
//	relation.rect.x = objectPosition.x;
//	relation.rect.y = objectPosition.y;
//	relation.rect.widto;
	relation.invisible = 0;
//	relation.rect.x = h = o->collisionSize().width;
//	relation.rect.height = o->collisionSize().height;
	relation.angleBegin = angleBegin;
	relation.angleEnd = angleEnd;
	relation.rect.x = o->get_pos().x + o->collisionSize().x;
	relation.rect.y = o->get_pos().y + o->collisionSize().y;
	relation.rect.width = o->collisionSize().width;
	relation.rect.height = o->collisionSize().height;

	float a1 = relation.angleEnd,a2 = relation.angleBegin;
	objectPosition.x = relation.rect.x;
	objectPosition.y = relation.rect.y;
	//check angles through all corners
	for (int i =0; i<2; i++)
	{
		for (int j =0; j<2; j++)
		{
			float a = getRadian(center, objectPosition);
			int u = toDegree(a);
			a1 = min<float> (a1,a);
			a2 = max<float> (a,a2);
			objectPosition.y += relation.rect.height;
		}
		objectPosition.x += relation.rect.width;
		objectPosition.y = relation.rect.y;
	}
	relation.angleBegin = max<float> (relation.angleBegin, a1);
	relation.angleEnd = min<float> (relation.angleEnd, a2);
	if ((relation.angleBegin >= angleBegin)
		&& (relation.angleEnd <= angleEnd))
		visibleObjects.push_back(relation);
}
int Seer::checkVisibility()
{
	return 3;
	//mame vsetky objekty zoradene podla Y osy
	std::list<ObjectRelation>::iterator iter = visibleObjects.begin();
	//vyhodime vsetky, co su neviditelne
	while(iter!=visibleObjects.end())
	{
		Rectangle oRelPos = (*iter).rect;
		if ((*iter).invisible&3)
		{
			iter = visibleObjects.erase(iter);
			continue;
		}
		if (!(*iter).object->is_blocking())
		{
			iter ++;
			continue;
		}

		//checkni uhol

		double tgLeft = oRelPos.x/(oRelPos.y + oRelPos.height);
		double tgRight = (oRelPos.x + oRelPos.width)/oRelPos.y;
		std::list<ObjectRelation>::iterator i = iter;
		i++;
		while (i!=visibleObjects.end())
		{
			Rectangle r = (*i).rect;
			double oTgLeft = r.x/(r.y +r.height);
			double oTgRight = (r.x + r.width)/r.y; //r.y nebude niky nulove
			if ((tgLeft < oTgLeft) && (oTgLeft < tgRight))
				(*i).invisible|=1;
			if ((tgLeft < oTgRight) && (oTgRight < tgRight))
				(*i).invisible|=2;
			i++;
		}
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
