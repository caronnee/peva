//TODO ztemplatovat, aby sa to dalo pouzit na vsetky variable
#ifndef ___MEMORY____
#define ___MEMORY____

#include <deque>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <vector>
#include "variable.h"
#include "node.h"
#include "functions.h"

struct Memory_record
{
	Node * node;
	size_t depth;
	Variable * variable;
};

class Memory
{
private:
	/* object representig null or bad access, like dev_null */
	Dummy * dummyObject;

	/* position where to begint o check free space */
	size_t position;

	/* structure to hold assigned variables */
	std::vector<Memory_record> assigned;

	/* structure to hold temporarily assigned variables */
	std::deque<Variable *> temp;

	/* memory structure */
	std::vector<Variable *> memory;

	/* returns nearest possible free variable */
	Variable * next_id(size_t ID);

	/* returns variable with Type t */
	Variable * find_free(Create_type * t, size_t ID);

	/* sets variable v and structures in it as free */
	void set_free(Variable * v);

	/* help function to fill variable element of type t */
	void fill(Variable * &v, 
		  Create_type * &t, 
		  std::stack<Variable *> &variables_to_assign, 
		  std::stack<Create_type *> & types_to_assign,
		  size_t ID);
public:
	/* class constructor */
	Memory( int size = 1 );

	/* returns dummyobject that nothing knows or does */
	Object * dummy()const;
	
	/* frees parameters of function f */
	void freeParameters ( Function * f );

	/* defailt variable */
	Variable * dev_null()const;

	/* returns variable added in depth d */
	void assign(Node *n ,size_t depth);

	/* returns variable  temporarily added */
	Variable * assign_temp(Create_type * t);

	/* frees occupied memory with depth greater or equal to depth */
	void free(size_t depth);

	/* frees temporary variable */
	void free_tmp();

	/* reallocatin memory to new size */
	void realloc(size_t size);

	/* returns random memory point*/
	Variable * random();

	/* destructor */
	~Memory();
};

#endif
