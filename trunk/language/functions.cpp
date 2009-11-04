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
Function::Function(std::string s,std::vector<Parameter_entry>params, Node * n)
{
	name = s;
	parameters = params;
	return_var = n; //potom sa priradi, ked bude funkcia zavolana
}

