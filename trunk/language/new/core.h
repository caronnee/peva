#ifndef ___CORE____
#define ___CORE____

#include "memory.h"
#include "variable.h"

struct Value
{
	Variable hlp;
	Variable * loaded;
};

struct Core
{
	size_t PC;
	int depth;
//	Robot * R; //periferie, stav robota, interakcia s mapou
//	Map * map;
	Memory memory;
	std::vector<Value> values;	
};
#endif
