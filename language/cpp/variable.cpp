#include <cstdio>
#include "../h/variable.h"
#include "../../add-ons/h/macros.h"

Variable::Variable(size_t i)
{
	reset();
	ID = i;
}
Variable::Variable(std::string name_)
{
	reset();	
}
void Variable::reset()
{
	ID =-1;
	owner = -1;
	last_access = 0;
	integerValue = 1986;
	realValue = 18.05;
	array.range = -1;
	objectValue = NULL;
	array.elements.clear();
}
void Variable::copyValue(Variable *v) //akopiruje aj neinicializovane hodnoty, mozno by bolo lepsie previest na LOAD/STORE, ale takto mi to pride transprantnejsie v XMLku:)
{
	//OWNER sa nemeni!
	//A musia byt rovnakehotypu, co sa arrayov tyka
	if (v == NULL )
	{
		TEST("Error  - Copying NULL variable");
		return;
	}
	if (array.elements.size() != v->array.elements.size() )
	{
		TEST("Error : variable " << v << "tries to copy to " << this << "Not same range")
		return;
	}
	std::cout << "Integer value change from: " << integerValue << "(id = " << ID << ") to " << v->integerValue << "(id ="<< v->ID <<")" << std::endl;
	integerValue = v->integerValue;
	realValue = v->realValue;
	objectValue = v->objectValue;
	for ( size_t i = 0; i< v->array.elements.size(); i++)
	{
		array.elements[i]->copyValue(v->array.elements[i]);
	}//FIXME zauvazovat ad tym, ci by nemozlo rozumnejse ist cez store/load, poripade bez rekurzie
}
void Variable::swapValue(Variable * v)
{
	/* swapping integer */
	int i = v->integerValue;
	v->integerValue = integerValue;
	integerValue = i;

	/* swapping real */
	float f = v->realValue;
	v->realValue = realValue;
	realValue = f;

	/* swapping Object */
	Object * o = v->objectValue;
	v->objectValue = objectValue;
	objectValue = o;

	/* swapping arrays */
	size_t min = array.elements.size();
	if (min > v->array.elements.size())
		min = v->array.elements.size();
	for(size_t i =0; i<min; i++) 
	{
		Variable * hlp = array.elements[i];
		array.elements[i] = v->array.elements[i];
		v->array.elements[i] = hlp;
	}
}
Variable::~Variable()
{
	/* nothing to dealocate, structure to hold somthing created elsewhere */
	array.elements.clear();
	array.range = -1;
}
