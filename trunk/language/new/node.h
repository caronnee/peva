#ifndef ___NODE____
#define ___NODE____

#include "variable.h"

struct Var
{
	Variable * var;
	int depth;
}
struct Node
{
	NestedType nested;
	std::string name;
	Create_type type_of_variable;
	std::vector<Var> var;
	Node();
	Node(std::string name, Create_type t);
};

#endif
