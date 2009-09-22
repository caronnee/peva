#ifndef ___MEMORY____
#define ___MEMORY____

#include <stack>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "variable.h"

struct Memory_record
{
	size_t depth;
	Variable * variable;
};

class Memory
{
	/* Position where to begint o check free space */
	size_t position;

	/* number of units that is possible to allocate */
	size_t memory_size;

	/* structure to hold assigned variables */
	std::vector<Memory_record> assigned;

	/* structure to hold temporarily assigned variables */
	std::stack<Variable *> temp;

	/* memory structure */
	Variable ** memory;

	/* returns nearest possible free variable */
	Variable * next_id(size_t ID);

	/* returns variable with Type t */
	Variable * find_free(Create_type t, size_t ID);

	/* sets variable v and structures in it as free */
	void set_free(Variable * v);

public:
	/* class constructor */
	Memory(int size = 100);

	/* returns variable added in depth d */
	Variable * assign(Create_type t, size_t ID,size_t depth);

	/* returns variable  temporarily added */
	Variable * assign_temp(Create_type t);

	/* frees occupied memory with depth greater or equal to depth */
	void free(size_t depth);

	/* frees temporary variable */
	void free_tmp();

	/* reallocatin memory to new size */
	void realloc(int size);
};

#endif