#ifndef ___NODE____
#define ___NODE____

#include "variable.h"

/* structure to hold variables and name od variable */
struct Node
{
	/* id of node */
	size_t ID;

	/* flag if there was such a name in this context */
	bool active;

	/* not udes, shoiuld be deleted */
	NestedType nested;

	/* name od variable and key to burst tree */
	std::string name;

	/* tyoe of variable */
	Create_type * type_of_variable;

	/* allocated variables in different depths*/
	std::vector<Variable *> var;

	/* constructors */
	Node();
	Node(std::string name_, Create_type* t, size_t ID_);

	/* destructor */
	~Node();
};

#endif
