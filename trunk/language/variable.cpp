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
