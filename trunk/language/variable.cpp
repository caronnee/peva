#include "variable.h"

Variable::Variable(size_t i)
{
	ID = i;
	owner = -1; //nijaky node nevlastni
	objectValue = NULL;	
}
Variable::Variable(std::string name_)
{
	owner = -1;
	objectValue = NULL;
}
/*void Variable::set_variable(Type t)
{
	type = t;
}*/
void Variable::copyValue(Variable *v) //akopiruje aj neinicializovane hodnoty, mozno by bolo lepsie previest na LOAD/STORE, ale takto mi to pride transprantnejsie v XMLku:)
{
	//OWNER sa nemeni!
	//A musia byt rovnakehotypu, co sa arrayov tyka
	integerValue = v->integerValue;
	realValue = v->realValue;
	objectValue = v->objectValue;
	//este sa postarat o arraye
//	std::cout << "element size parametrer:" << v->array.elements.size(); getc(stdin);

//	std::cout << "size function parameter-" << array.elements[0]; getc(stdin);
	std::vector<Variable *> variables_to_copy;
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
