#include "functions.h"

Parameter_entry::Parameter_entry()
{
	name = "Not_defined";
}
Parameter_entry::Parameter_entry(std::string s, Parameter_type pt, Node * n)
{
	name = s;
	val_type = pt;
	node = n;
}
Function::Function(std::string s, Node * n)
{
	name = s;
	return_var = n; //potom sa priradi, ked bude funkcia zavolana
}

