#ifndef ___MEMORY____
#define ___MEMORY____

#include <stack>
#include "variable.h"

struct Memory_record
{
	size_t owner, depth;
	Variable * variable;
	size_t id;
};
struct Memory
{
	int memory_size;
	std::stack<int> id_free_vars;
	std::vector<Memory_record> assigned;
	Variable ** memory;
	void free(size_t depth);
	Variable * assign(Create_type t,size_t id, size_t siz);
	Memory(int size = 100);
};

#endif
