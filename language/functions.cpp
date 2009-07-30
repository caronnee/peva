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
Function::Function(std::string n, std::vector<Parameter_entry> v, Create_type t)
{
	name =n;
	parameters = v;
	return_type = t; //potom sa priradi, ked bude funkcia zavolana
}

