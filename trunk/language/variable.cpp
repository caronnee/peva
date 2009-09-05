#include "variable.h"

Variable::Variable()
{
	owner = 0; //nijaky node nevlastni
	type = TypeUndefined;
	objectValue = NULL;	
}
Variable::Variable(std::string name_, Type t)
{
	owner = 0;
	type = t;
	objectValue = NULL;
}
void Variable::set_variable(Type t)
{
	type = t;
}
void Variable::copyValue(Variable *v) //akopiruje aj neinicializovane hodnoty, mozno by bolo lepsie previest na LOAD/STORE, ale takto mi to pride transprantnejsie v XMLku:)
{
	//OWNER sa nemeni!
	//A musia byt rovnakehotypu, co sa arrayov tyka
	integerValue = v->integerValue;
	realValue = v->realValue;
	objectValue = v->objectValue;
	//este sa postarat o arraye
	std::vector<Variable *> variables_to_copy;
	for ( size_t i = 0; i< array.elements.size(); i++)
	{
		array.elements[i]->copyValue(v->array.elements[i]);
	}//FIXME zauvazovat ad tym, ci by nemozlo rozumnejse ist cez store/load, poripade bez rekurzie
}
	
