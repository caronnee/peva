#ifndef ___MEMORY____
#define ___MEMORY____

#include <stack>
#include "variable.h"

struct Memory
{
	int max_size;
	std::stack<int> id_free_vars;
	std::vector<Variable *> memory;
	Variable * assign(Create_type t);
};

#endif
