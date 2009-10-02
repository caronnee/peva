//TODO ztemplatovat, aby sa to dalo pouzit na vsetky variable
#ifndef ___MEMORY____
#define ___MEMORY____

#include <queue>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <vector>
#include "variable.h"

struct Memory_record
{
	size_t depth;
	Variable * variable;
};

class Memory
{
private:
	/* position where to begint o check free space */
	size_t position;

	/* number of units that is possible to allocate */
	size_t memory_size;

	/* structure to hold assigned variables */
	std::vector<Memory_record> assigned;

	/* structure to hold temporarily assigned variables */
	std::queue<Variable *> temp;

	/* memory structure */
	Variable ** memory;

	/* returns nearest possible free variable */
	Variable * next_id(size_t ID);

	/* returns variable with Type t */
	Variable * find_free(Create_type t, size_t ID);

	/* sets variable v and structures in it as free */
	void set_free(Variable * v);

	/* help function to fill variable element of type t */
	void fill(Variable * &v, 
		  Create_type & t, 
		  std::stack<Variable *> &variables_to_assign, 
		  std::stack<Create_type> & types_to_assign,
		  size_t ID);
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

	/* returns actual mmory size*/
	Variable * random();
};

#endif
