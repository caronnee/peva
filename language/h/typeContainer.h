#ifndef ___TYPECONTAINER____
#define ___TYPECONTAINER____

#include <vector>
#include "types.h"

class TypeContainer
{
	std::vector< Create_type * > defined_types;
public:
	void add(Create_type * t);
	Create_type * find_type(Type t);
	Create_type * find_array_type(size_t i, Create_type * t);
	~TypeContainer();
};
#endif
