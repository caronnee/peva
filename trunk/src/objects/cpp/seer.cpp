#include "../../add-ons/h/macros.h"
#include "../h/seer.h"

Seer::Seer ()
{
	setEyes(0,0);//slepy :)
}

void Seer::setEyes(int angle, int defaultVisibility)
{
	eyeDimension.turn(angle,defaultVisibility);
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
	reset();
}
void Seer::reset()
{
	visibleObjects.clear();
	//rovnica, v tvare 0 = Ax + By + C pre jednu aj pre druhu stranu
	int xn = eyeDimension.x, yn = eyeDimension.y;
	aLeft = yn; 
	bLeft = xn;
	cLeft = 0;
	aRight = -yn;
	bRight = xn;
	cRight = 0;
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

void Seer::fill(Object * o, Position position)
{
	Position objectPosition = o->get_pos();
	objectPosition.substractVector(position);
	objectPosition.x -= o->collisionSize().x;
	objectPosition.y -= o->collisionSize().y;

	objectPosition.turn(180); 
	if (objectPosition.y > eyeDimension.y)
		return;
	if(aRight * objectPosition.x + bLeft * objectPosition.y < 0)
		return; //mimo  oblast
	objectPosition.x +=o->collisionSize().width;
	if(aLeft * objectPosition.x + bLeft * objectPosition.y > 0)
		return; //mimo oblast

	//zpat do povodneho stavu
	objectPosition.x -=o->collisionSize().width;
	ObjectRelation relation;
	relation.object = o;
	relation.dirty = 0;
	relation.rect.x = objectPosition.x;
	relation.rect.y = objectPosition.y;
	relation.rect.width = o->collisionSize().width;
	relation.rect.height = o->collisionSize().height;

	//zorad do pola zotriedene podla y-ovej osy
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
int Seer::checkVisibility()
{
	return 3;
//mame vsetky objekty zoradene podla Y osy
	std::list<ObjectRelation>::iterator iter = visibleObjects.begin();
	//vyhodime vsetky, co su neviditelne
	while(iter!=visibleObjects.end())
	{
		Rectangle oRelPos = (*iter).rect;
		if (!(*iter).object->is_blocking())
		{
			iter ++;
			continue;
		}
		if ((*iter).dirty&3)
		{
			iter = visibleObjects.erase(iter);
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
