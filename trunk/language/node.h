#ifndef ___NODE____
#define ___NODE____

#include "variable.h"

struct Node
{
	size_t ID;
	bool active;
	NestedType nested;
	std::string name;
	Create_type * type_of_variable;
	std::vector<Variable *> var;
	Node();
	Node(std::string name_, Create_type* t, size_t ID_);
};

#endif
