#ifndef ___MEMORY____
#define ___MEMORY____

#include <stack>
#include "variable.h"

struct Memory
{
	std::stack<int> id_free_vars;
	std::vector<Variable *> memory;
};

#endif
