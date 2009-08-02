#include "variable.h"

Variable::Variable()
{
	owner = 0; //nijaky node nevlastni
	type = TypeUndefined;
	array = new Array();
}
Variable::Variable(std::string name_, Type t)
{
	owner = 0;
	array = new Array();
	type = t;
}
void Variable::set_variable(Type t)
{
	type = t;
}
