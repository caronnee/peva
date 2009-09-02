#ifndef ___NODE____
#define ___NODE____

#include "variable.h"

struct Var
{
	Variable * var;
	int depth;
};
struct Node
{
	size_t ID;
	NestedType nested;
	std::string name;
	Create_type * type_of_variable;
	std::vector<Var> var;
	Node();
	Node(std::string name_, Create_type* t, size_t ID_);
};

#endif
