#include "variable.h"

Variable::Variable()
{
	owner = 0; //nijaky node nevlastni
	name = "hlp";
	type = TypeUndefined;
	array = new Array();
}
Variable::Variable(std::string name_, Type t)
{
	owner = 0;
	array = new Array();
	name = name_;
	type = t;
}
void Variable::set_variable(Type t)
{
	type = t;
}
