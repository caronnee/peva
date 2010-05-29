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

/* struct defining parameters of function and iinformation about type (reference, value) */
struct Parameter_entry
{
	std::string name;
	Parameter_type val_type;
	Node * node;
	Parameter_entry(std::string name, Parameter_type pt, Node * n);
	Parameter_entry();
};

/* struct holding all information about defined function */
struct Function
{
	std::string name;
	std::vector<Parameter_entry> parameters;
	size_t begin; 
	size_t end;
	Node * return_var;
	Function(std::string name, std::vector<Parameter_entry>params,Node * n);
	~Function();
};

#endif
