#ifndef ___MEMORY____
#define ___MEMORY____

#include <stack>
#include "variable.h"

struct Memory_record
{
	int depth;
	Variable * variable;
	int id;
};
struct Memory
{
	int memory_size;
	std::stack<int> id_free_vars;
	std::vector<Memory_record> assigned;
	std::vector<Variable *> memory;
	void free(int depth);
	Variable * assign(Create_type t,int depth);
};

#endif
