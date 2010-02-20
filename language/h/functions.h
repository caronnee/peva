#ifndef __FUNCTIONS_____
#define __FUNCTIONS_____

#include <vector>
#include <cstdio>
#include "node.h"

enum Parameter_type
{
	PARAMETER_BY_REFERENCE,
	PARAMETER_BY_VALUE
};

struct Parameter_entry
{
	std::string name;
	Parameter_type val_type;
	Node * node; //mkde sa skryva dotycne meno
	Parameter_entry(std::string name, Parameter_type pt, Node * n);
	Parameter_entry();
};

struct Function
{
	std::string name;
	std::vector<Parameter_entry> parameters;
	size_t begin; //kde to zacina v stacku
	size_t end;
	Node * return_var;
	Function(std::string name, std::vector<Parameter_entry>params,Node * n);
	~Function();
};

#endif
