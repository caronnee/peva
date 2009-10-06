#include "parser_classes.h"

void Element::clear()
{
	ins.clear();
	output.clear();
	temp.clear();
}
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
	output = e;
	ins = i;
}
