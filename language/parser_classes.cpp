#include "parser_classes.h"

Constr::Constr()
{
	default_set = false;
	id ="";
}
Constr::Constr(std::string a)
{
	id =a;
	default_set  =false;
}

Constr::Constr(std::string a, Instructions i, Expressions e)
{
	id = a;
	default_set = true;
}

