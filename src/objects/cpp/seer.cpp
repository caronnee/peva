#include <cmath>
#include "../../add-ons/h/macros.h"
#include "../h/seer.h"

Seer::Seer()
{
	setEyes(0,0); //slepy :)
}

void Seer::setEyes(int angle, int defaultVisibility)
{
	eyeDimension.turn(angle,defaultVisibility);
	eyeDimension.absolute();
	size = defaultVisibility;
	angle_ = angle;
	reset();
}
void Seer::setEyes(Position eyeDimension_)
{
	eyeDimension = eyeDimension_;
	//we need to have positive numbers
	if (eyeDimension.x < 0)
		eyeDimension.x*=-1;
	if (eyeDimension.y <0)
		eyeDimension.y *=-1;
	size = sqrt(eyeDimension.x*eyeDimension.x+eyeDimension.y+eyeDimension.y);
	angle_ = asin(eyeDimension.y/eyeDimension.y)*PI/180; //TODO check
	reset();
}
void Seer::reset() 
{
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

void Seer::fill(Object * o, Position position)
{
	Position objectPosition = o->get_pos();
	objectPosition.substractVector(position); //hodime to do osy s pociatkom (0,0)
	if (sqrt(objectPosition.x*objectPosition.x
		+ objectPosition.y * objectPosition.y)
		> size)
		return; //nie je v kruhu

	ObjectRelation relation;
	relation.object = o;
	relation.dirty = 0;
	relation.rect.x = objectPosition.x;
	relation.rect.y = objectPosition.y;
	relation.rect.width = o->collisionSize().width;
	relation.rect.height = o->collisionSize().height;
	
	//check angles through all corners
	for (int i =0; i<2; i++)
	{
		for (int j =0; j<2; j++)
		{
			//because of SDL, turning to 180 degrees
			Position p = objectPosition.turn(180,size); //malo by byt jedno size a bez size, overit!
			float a = 90;
			if (p.x !=0)
				a = asin(p.y/p.x) * PI /180 ;

			if ( (a > (90-angle_))&&(a < (90+angle_)))
			{
				//je vnutru vysecu
				addToVisible(relation);
				return;
			}
			objectPosition.y += relation.rect.height;
		}
		objectPosition.x += relation.rect.width;
		objectPosition.y = relation.rect.y;
	}
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
		if ((*iter).dirty&3)
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
				(*i).dirty|=1;
			if ((tgLeft < oTgRight) && (oTgRight < tgRight))
				(*i).dirty|=2;
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
