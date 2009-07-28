#ifndef __FUNCTIONS_____
#define __FUNCTIONS_____

#include <vector>
enum Parameter_type
{
	PARAMETER_BY_REFERENCE,
	PARAMETER_BY_VALUE
};

struct Parameter_entry
{
	std::string name;
	Parameter_type val_type;
	Create_type type;
	Parameter_entry(std::string name, Parameter_type pt, Create_type type);
	Parameter_entry();
};

struct Function
{
	std::string name;
	std::vector<Parameter_entry> parameters;
	int begin; //kde to zacina v stacku
	int end;
	Create_type return_type;
	std::vector<Variable *> return_var;
	Function(std::string name, std::vector<Parameter_entry>, Create_type t);
};

#endif
